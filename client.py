import socket

# connect to the Host Servers IP address
HOST = '192.168.0.75'
# same port as Host server
PORT = 8080

# create socket 
# socket of AF_INET 
# socket of TCP -> SOCK_STREAM
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# using connect to connect to the Host server
socket.connect((HOST, PORT))
# connection request is made
# if accepted then the next block is executed

# send message to server
socket.send("Hello server".encode('utf-8'))
# print the data received from the server
print(socket.recv(1024).decode('utf-8'))

# RUN COMMAND = "python client.py"
