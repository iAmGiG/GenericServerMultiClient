import socket

def connect_to_server(host, port):
    """Establish a connection with the TCP server."""
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((host, port))
    return sock

def send_message(sock, message):
    """Send a message to the TCP server."""
    sock.sendall(message.encode())

def receive_message(sock):
    """Receive a message from the TCP server."""
    return sock.recv(1024).decode()

def close_connection(sock):
    """Close the TCP connection."""
    sock.close()

if __name__ == "__main__":
    server_host = "localhost"
    server_port = 8080
    with connect_to_server(server_host, server_port) as sock:
        try:
            message = input("Enter Text to echo: ")
            send_message(sock, message)
            print("Server Responed with: ", receive_message(sock))
        finally:
            close_connection(sock)