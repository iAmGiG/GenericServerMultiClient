# GenericServerMultiClient

This project is a personal journey into the world of sockets, ip, C based server and the headache that comes with all of that. The goal is to have a C based server, and test out various functions within C, then use various different languages to make unit-test.

* now I know, the win local machine I'm running on isn't the most "productive" but it was all done at a convenise level.
* future project could be a server side prime number generator or prime num caculator.

## We build the client in Py

This client side in py, at least to start, should prove a general working element of the server, as the client side won't particually matter.

* Import the socket module in Python.
* Use socket.socket(socket.AF_INET, socket.SOCK_STREAM) to create a socket object.
* Connect to the server using socket.connect((server_ip, port)), where server_ip is the IP address or hostname of the machine where the reverse echo server is running, and port is the port number provided as a command-line argument.
