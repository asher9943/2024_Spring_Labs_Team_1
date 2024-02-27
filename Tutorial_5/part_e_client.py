import socket               # Import socket module
import time

s = socket.socket()         # Create a socket object
s.connect(('192.168.46.61', 80))
s.sendall(b'Here I am!\n')
time.sleep(5) # so it has time to handle before we close
s.close()                     # Close the socket when done

