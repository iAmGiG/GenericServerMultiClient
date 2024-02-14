import unittest
import Client


class TestClient(unittest.TestCase):
    def test_send_receive_message(self):
        message = "Hello"
        print(f"Sent message:  {message}")
        sock = Client.connect_to_server('localhost', 8080)
        Client.send_message(sock, message)
        response = Client.receive_message(sock)
        Client.close_connection(sock)

        print(f"Received message: {response}")

        self.assertEqual(response, 'olleH')


if __name__ == '__main__':
    unittest.main()
