#!/usr/bin/python3.7

# Bridge data between API and TCP service

import socket
from GetData import *

serverHostname = "192.168.192.6" 
serverPort = 9999

baseHostname = "192.168.192.110"
baseUrl = "http://" + baseHostname + "/api/v1/"
smartmeterUrl = "" + baseUrl + "smartmeter?limit=1"

def SendData(hostname, port, data):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((hostname, port))
    s.sendall(data.encode())
    s.close()

def main():
    SendData(serverHostname, serverPort, GetData(smartmeterUrl))

if __name__ == "__main__":
    main()