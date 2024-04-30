import socket
import signal

# server constants
HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
PORT = 65432  # Port to listen on (non-privileged ports are > 1023)

# Define the message names
# Putting these up top for documentation since the robots will need to match them
MAZE_1_CAM = b'Maze 1 color check'
MAZE_2_CAM = b'Maze 2 color check'
DUAL_FATES = b'Duel fates cross correlation'

MAZE_1_DONE = b'Maze 1 done'
MAZE_2_DONE = b'Maze 2 done'
DUAL_FATES_DONE = b'Duel fates done'

# Ensures we handle ctrl-c kill gracefully
def handler(signum, frame):
    print('Keyboard interrupt ... exiting')
    exit(0)


def main():
    maze_1_done = False
    maze_2_done = False
    dual_fates_done = False
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()

        # Loop until all 3 robots are done
	# This loops to accept a new connection to the server
        # It expects the robots to be well-behaved about closing connections once they're done
        # And not spamming the server, there's no load balancing here
        while not (maze_1_done and maze_2_done and dual_fates_done):
            # This is a blocking wait, we want to hold until something needs us
            conn, addr = s.accept()

            with conn:
                # This is a blocking wait, we want the code to be reactive to incoming messages so good 
                # 1024 bytes arbitrary max
                msg = socket.recv(1024)
    
                # Decide what to do based on the message    
                # Would be nice to bind some callbacks or something but this whole thing is down and dirty
                if (msg == MAZE_1_CAM):
                    print("MAZE_1_CAM") 
                elif (msg == MAZE_2_CAM):
                    print("MAZE_2_CAM") 
                elif (msg == DUEL_FATES):
                    print("DUEL_FATES") 
                elif (msg == MAZE_1_DONE):
                    maze_1_done = True 
                elif (msg == MAZE_2_DONE):
                    maze_2_done = True 
                elif (msg == DUEL_FATES_DONE):
                    duel_fates_done = True 

                # Implicitly we ignore a message that is invalid or empty (signifying closed connection)
                # Because of the with structure we don't need to close here
                # Also because of nested with structure it expects only one message per new connection
                # This avoids starvation of one robot hogging the server

signal.signal(signal.SIGINT, handler)

if __name__ == "__main__":
    main()

