import socket

# server constants
HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)

MAZE_CAM = b"Maze block check"
MAZE_DONE = b"Maze done"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send(MAZE_CAM)
msg = s.recv(1024)
print(msg)
s.close()
