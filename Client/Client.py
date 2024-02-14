import argparse
import socket


def parse_arguments():
    parser = argparse.ArgumentParser(
        description='TCP client for connecting to a server.')
    parser.add_argument('server_ip', type=str, help='Server IP address')
    parser.add_argument('port', type=int, help='Server port number')
    return parser.parse_args()


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


def create_tcp_connection(server_ip, port):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((server_ip, port))
        return sock
    except socket.error as e:
        print(f"Error connecting to server: {e}")
        exit(1)


if __name__ == "__main__":
    args = parse_arguments()
    with connect_to_server(args.server_ip, args.port) as sock:
        try:
            message = input("Enter Text to echo: ")
            send_message(sock, message)
            print("Server Responed with: ", receive_message(sock))
        finally:
            close_connection(sock)
    sock.close
