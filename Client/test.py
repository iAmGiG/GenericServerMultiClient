import unittest
from unittest.mock import patch
import Client


class TestClient(unittest.TestCase):
    @patch('client.socket.socket')
    def test_send_receive_message(self, mock_socket):
        mock_socket_instance = mock_socket.return_value
        mock_socket_instance.recv.return_value = b'olleH'

        sock = Client.connect_to_server('localhost', 8080)
        Client.send_message(sock, 'Hello')
        response = Client.receive_message(sock)

        self.assertEqual(response, 'olleH')


if __name__ == '__main__':
    unittest.main()
