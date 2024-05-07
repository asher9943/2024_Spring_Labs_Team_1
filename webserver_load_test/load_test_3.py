import socket

# server constants
HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)

DUAL_FATES = b"Duel fates cross correlation"
DUAL_FATES_DONE = b"Duel fates done"

for i in range(10):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    s.send(DUAL_FATES)
    s.close()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send(DUAL_FATES_DONE)
s.close()
