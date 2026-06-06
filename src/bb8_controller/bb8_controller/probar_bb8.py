import socket

IP = "192.168.10.18"   # cambia por la IP que te muestre la ESP32
PORT = 8888

sock = socket.socket()
sock.connect((IP, PORT))

while True:

    cmd = input("Comando (w,s,a,d,x): ")

    sock.send(cmd.encode())