import unittest
import random
import string
import Client


def random_word(length):
    """Generate a random word of given length."""
    letters = string.ascii_letters  # Include both uppercase and lowercase
    return ''.join(random.choice(letters) for i in range(length))


class TestClient(unittest.TestCase):
    def test_send_receive_messages(self):
        sock = Client.connect_to_server('localhost', 8080)
        for _ in range(10):
            word = random_word(random.randint(5, 10))
            print(f"Sending message: {word}")
            Client.send_message(sock, word)
            response = Client.receive_message(sock)
            print(f"Received message: {response}")
            # Assuming the server echoes back the sent message
            self.assertEqual(response, word[::-1])

        Client.close_connection(sock)


if __name__ == '__main__':
    unittest.main()
