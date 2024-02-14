# GenericServerMultiClient

This project is a personal journey into the world of sockets, ip, C based server and the headache that comes with all of that. The goal is to have a C based server, and test out various functions within C, then use various different languages to make unit-test.

* now I know, the win local machine I'm running on isn't the most "productive" but it was all done at a convenise level.
* future project could be a server side prime number generator or prime num caculator.

## We build the client in Py

This client side in py, at least to start, should prove a general working element of the server, as the client side won't particually matter.

* Import the socket module in Python.
* Use socket.socket(socket.AF_INET, socket.SOCK_STREAM) to create a socket object.
* Connect to the server using socket.connect((server_ip, port)), where server_ip is the IP address or hostname of the machine where the reverse echo server is running, and port is the port number provided as a command-line argument.

#### additional details

To run the Python client script, use the command line to navigate to the script's directory. Then, execute the script with Python by specifying the server's IP address and the port number as arguments. The command format is python Client.py <Server IP> <Port>. Replace <Server IP> with the server's actual IP address and <Port> with the server's listening port number. This allows the client to connect to the TCP server and perform operations as defined in the script..

# TCP Server Application

This TCP Server application is a simple, multi-threaded server written in C, designed to run on Windows. It demonstrates the fundamentals of socket programming in a Windows environment, handling multiple client connections concurrently. Each client connection is managed in a separate thread, where the server listens for incoming strings, reverses them, and sends the reversed string back to the client.

## Features

* **Multi-threaded Handling**: Uses Windows threads to manage multiple client connections simultaneously.
* **String Reversal Logic**: Demonstrates basic data processing by reversing incoming strings.
* **Dynamic IP and Port Binding**: Configurable to bind to any specified IP address and port.
* **Graceful Shutdown**: Supports shutting down the server through specific client commands.

## Requirements

* **Windows Operating System**: The server is developed and tested on Windows. It utilizes Windows-specific threading and socket APIs.
* **C Compiler**: A C compiler compatible with Windows, such as MinGW or MSVC.
* **Winsock Library**: Utilizes the Winsock2 library for networking, which is typically available in the Windows SDK.

## Getting Started

### Compilation

[Note] the included .vscode .jsons are designed to point to your evnrioment setttings.
otherwise, to compile the server application, navigate to the project directory and use the following command:

```bash
gcc server.c -o server -lws2_32
```

### Stopping the Server

The server listens for a specific shutdown command ("fin") from any connected client. Upon receiving this command, it will respond with "nif", terminate the client connection, and shut down gracefully.

### Development and Testing

For local development and testing, the server can be configured to listen on 127.0.0.1 (localhost) to accept connections only from the same machine. For testing client-server interactions across different machines or networks, configure the server to bind to the appropriate external IP address or use INADDR_ANY to listen on all network interfaces.

### The unfortunate windows comment

oh no

#### Requirements

Windows Operating System: The server is developed and tested on Windows. It utilizes Windows-specific threading and socket APIs.
C Compiler: A C compiler compatible with Windows, such as MinGW or MSVC.
Winsock Library: Utilizes the Winsock2 library for networking, which is typically available in the Windows SDK.

* I wanted to get this on my Linux VM, but time got me to.

## Additional instructions for setup in VScode

1. Open Visual Studio Code.
2. Go to **File > Preferences > Settings** or use the shortcut `Ctrl+,` (Cmd+, on macOS).
3. Search for the relevant setting (e.g., "CMake path").
4. Click on **Edit in settings.json** at the top right of the settings tab.
5. Add or update the necessary configuration. For example, to specify the CMake path:

```json
{
    "cmake.cmakePath": "/path/to/your/cmake"
}
```

Replace "/path/to/your/cmake" with the actual path to your cmake executable.

### Configuring tasks.json and launch.json

To build and debug your project, you may need to create or update the tasks.json and launch.json files in the .vscode directory at the root of your project.

### tasks.json

This file defines tasks for building your project. If your compiler or build tool is located in a non-standard location, specify the path in the command field:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build Project",
            "type": "shell",
            "command": "/path/to/your/compiler",
            "args": [
                "your_build_arguments"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

Replace "/path/to/your/compiler" and "your_build_arguments" with the appropriate values for your project.

### launch.json

This file configures how debugging is handled. If you need to specify a custom debugger path or additional debugging options, update this file accordingly:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug Project",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/path/to/your/executable",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "miDebuggerPath": "/path/to/your/debugger"
        }
    ]
}
```

Ensure you replace "${workspaceFolder}/path/to/your/executable" and "/path/to/your/debugger" with the correct paths for your setup.

### Final Notes

After making these changes, reload Visual Studio Code to apply the new configurations. These steps ensure that your development environment is correctly set up to work with the project, regardless of where your development tools are installed on your system.

* yes I had chatboy, help me with the read me.

* Yes I know the, read me is a bit ... jank.

* enjoy.
