import unittest
from unittest.mock import patch, MagicMock
import random
import string
import Client

def random_word(length):
    """Generate a random word of given length."""
    letters = string.ascii_letters  # Include both uppercase and lowercase
    return ''.join(random.choice(letters) for i in range(length))

class TestClient(unittest.TestCase):
    @patch('client.socket.socket')
    def test_send_receive_messages(self, mock_socket):
        # Mock socket instance to simulate server behavior
        mock_socket_instance = mock_socket.return_value
        
        # Generate test cases: a list of random words
        test_cases = [random_word(random.randint(5, 10)) for _ in range(10)]
        
        # Mock the server's response for each test case
        for word in test_cases:
            mock_socket_instance.recv.return_value = word[::-1].encode()

            with patch('Client.connect_to_server', return_value=mock_socket_instance), \
                 patch('Client.send_message', return_value=None), \
                 patch('Client.receive_message', return_value=word[::-1]), \
                 patch('Client.close_connection', return_value=None):

                # Simulate client sending the word
                Client.connect_to_server('localhost', 8080)
                Client.send_message(mock_socket_instance, word)
                response = Client.receive_message(mock_socket_instance)
                
                # Assert that the response is the reversed word
                self.assertEqual(response, word[::-1])

if __name__ == '__main__':
    unittest.main()
