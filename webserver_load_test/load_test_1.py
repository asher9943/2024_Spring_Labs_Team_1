import socket

# server constants
HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)

MAZE_1_CAM = b"Maze 1 color check"
MAZE_1_DONE = b"Maze 1 done"

for i in range(10):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    s.send(MAZE_1_CAM)
    s.close()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send(MAZE_1_DONE)
s.close()
