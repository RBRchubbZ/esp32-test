import socket

# SET HOST AND PORT
HOST = '192.168.0.75'
PORT = 8080

# server = type of socket
# AF_INET = Address Family = internet -> ip addresses 
# SOCK_STREAM = TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# bind host and port to server as a tuple
server.bind((HOST, PORT))

# start to listen for incoming connection 
server.listen()

# endless listen to any connection
while True:
    # return value of accept = socket of client and address of client
    # communication socket holds clients socket
    # address holds the address of the client 
    communication_socket, address = server.accept()
    print(f"connected to {address} on socket {communication_socket}")

    # get the message form the client
    # recv -> receives client data
    # value as pram is the size of bytes
    # decode the byte stream to utf-8
    message = communication_socket.recv(1024).decode("utf-8")
    print(f"message is {message}")

    # send message back to client 
    # encode the message being sent 
    communication_socket.send(f"got the messsage!!".encode('utf-8'))

    # close the connection 
    communication_socket.close()
    print(f"connection with {address} closed")

# RUN COMMAND = "python server.py"
