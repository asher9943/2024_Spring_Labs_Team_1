import socket

# server constants
HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)

DUAL_FATES_LEFT = b"Dual fates left"
DUAL_FATES_RIGHT = b"Dual fates right"
DUAL_FATES_RESULT = b"Dual fates result"
DUAL_FATES_DONE = b"Duel fates done"

for i in range(11):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    if i % 3 == 0:
        s.send(DUAL_FATES_LEFT)
    if i % 3 == 1:
        s.send(DUAL_FATES_RIGHT)
    if i % 3 == 2:
        s.send(DUAL_FATES_RESULT)
    s.close()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send(DUAL_FATES_DONE)
s.close()
