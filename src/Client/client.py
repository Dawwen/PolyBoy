#!/usr/bin/env python

import socket


TCP_IP = '127.0.0.1'
TCP_PORT = 1236
BUFFER_SIZE = 1024
MESSAGE = "Hello, World!".encode()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.send(MESSAGE)
print("Sys >> BEGIN")
data = s.recv(BUFFER_SIZE)
print("Sys >> END")
s.close()

print("received data:", data)
