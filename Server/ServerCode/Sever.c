#include <stdio.h>  // Standard input/output definitions
#include <stdlib.h> // Standard library
#include <string.h> // Memory manipulation
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>
#include <windows.h>

#define PORT 8080
#define BACKLOG 5 // How many pending connections queue will hold

// global vars
volatile int serverRunning = 1;

// String reversal function
char *reverse_echo_serve(const char *str)
{
    int len = strlen(str);
    // Allocate space for the reverse string with additoanl space for the null terminator.
    char *reversed_str = malloc(len + 1);

    if (reversed_str == NULL)
    {
        fprintf(stderr, "malloc has failed\n");
        return NULL;
    }

    for (int index = 0; index <= len - 1; ++index)
    {
        reversed_str[index] = str[len - 1 - index];
    }
    // Insert the null terminator at the end of the string
    reversed_str[len] = '\0';

    // Log the conversion
    printf("Converting '%s' to '%s'\n", str, reversed_str);

    return reversed_str;
}

void *handle_client(void *socket)
{
    int sock = *(int *)socket;
    free(socket); // Free the dynamically allocated memory for the socket
    char buffer[1024] = {0};
    DWORD threadID = GetCurrentThreadId(); // Get the current thread ID
    printf("New client handling process has begun. Thread ID: %lu\n", threadID);
    // Receive client data
    int valread = recv(sock, buffer, sizeof(buffer), 0);
    if (valread <= 0)
    {
        fprintf(stderr, "recv failed with error: %d\n", WSAGetLastError());
        closesocket(sock);
        return NULL;
    }

    // Null-terminate the received data to safely use string functions
    buffer[valread] = '\0';

    // Check if the received string is "fin"
    if (strcmp(buffer, "fin") == 0)
    {
        /*
        If "fin" is received, send "nif" back to the client
        This process can take a few moments to finsh, as the win clean up does have to complete first.
         */
        const char *nif = "nif";
        send(sock, nif, strlen(nif), 0);
        serverRunning = 0;
    }
    else
    {
        // Proceed with the original logic if the message is not "fin"
        char *reversed_str = reverse_echo_serve(buffer);
        if (reversed_str == NULL)
        {
            // Handling of the reverse has failed
            closesocket(sock);
            return NULL;
        }

        // Send the reversed string back to the client
        send(sock, reversed_str, strlen(reversed_str), 0);
        free(reversed_str); // Free the dynamically allocated reversed string
    }

    closesocket(sock); // Close the socket after sending the response
    return NULL;
}

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        fprintf(stderr, "WSAStartup Failed - Error: %d\n", WSAGetLastError());
        return 1;
    }
    /*
    fd - file descriptor,
    its a unix/linux refernce,
    as descriptprs are used as a abstraction to access underlying system resources like files,
    sockets and pipes, in this cas e a network communication descriptor.
     */
    int server_fd, new_socket;
    /* Sockets are in the form of ints because of the unix/linux system file desciprots,
    as the int is a index to an array in the kernel where the structs representing the files or socket are stored */
    /* socket address end point, the endpoint address the socket will be bound or connected with, incldues an address family, port number and ip. */
    struct sockaddr_in address;
    /* this is to set options on the socket, passed to set socket opiton funciton, to change the defualt behavior of the socket.*/
    int opt = 1;
    /* size of bytes in the socket address endpoint stucture,
    needed because of different socket functions require the address size as a param to know how much memory to read or write when dealing
    with socket addresses. */
    int addrlen = sizeof(address);

    // Step 1: Creating a TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket crafting failed - Error: %d\n", WSAGetLastError());
        return 1;
    }
    // Step 2: set master socket to allow multiple connections
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        fprintf(stderr, "Setsockopt failed - Error: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    // Step 3: Binding the Socket
    address.sin_family = AF_INET;
    /*
    address.sin_addr.s_addr = INADDR_ANY; This was for testing, now to specifiy the IP on the localhost.
    Listen to any IP address.
     */
    address.sin_port = htons(PORT); // Host TO Network Short byte order
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
    {
        fprintf(stderr, "Invalid address/ Address not supported \n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
    {

        fprintf(stderr, "Bind has failed - Error: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Step 4: Listening for Incoming Connections
    if (listen(server_fd, BACKLOG) == SOCKET_ERROR)
    {
        fprintf(stderr, "Listen has failed - Error: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    char ipStr[INET_ADDRSTRLEN];                                   // Buffer to store the human-readable IP address
    inet_ntop(AF_INET, &address.sin_addr, ipStr, INET_ADDRSTRLEN); // Convert the IP to a string

    printf("Server is listening on IP %s, with port %d\n", ipStr, PORT);

    // Step 5: await connections and listen on the port.
    while (serverRunning)
    {
        printf("awaiting new connection...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) == INVALID_SOCKET)
        {
            fprintf(stderr, "Accept failed with error: %d\n", WSAGetLastError());
            continue;
        }
        else
        {
            if (!serverRunning)
                break; // Exit loop if server is stopping
        }

        int *new_sock = malloc(sizeof(int));
        *new_sock = new_socket;

        unsigned threadID;
        uintptr_t threadHandle = _beginthreadex(NULL, 0, (unsigned(__stdcall *)(void *))handle_client, (void *)new_sock, 0, &threadID);
        if (threadHandle == 0)
        {
            fprintf(stderr, "_beginthreadex failed with error: %d\n", errno);
            closesocket(new_socket);
        }
        else
        {
            CloseHandle((HANDLE)threadHandle);
        }
    }
    closesocket(server_fd);
    WSACleanup();
    printf("Server shut down.\n");
    return 0;
}
