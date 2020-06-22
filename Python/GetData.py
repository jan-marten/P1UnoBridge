#!/usr/bin/python3.7

# Get some data from p1 monitor using API
# Requirements; import request
#   Windows: python3 -m pip install requests
#   R-pi:  sudo pip3 install requests

import platform    # For getting the operating system name
import subprocess  # For executing a shell command
import requests    # For getting API data
import json        # For parsing json API data

baseHostname = "192.168.192.110"
baseUrl = "http://" + baseHostname + "/api/v1/"
smartmeterUrl = "" + baseUrl + "smartmeter?limit=1"

def Ping(host):
    # Returns True if host (str) responds to a ping request.
    # Returns True on Windows when Destination Host Unreachable

    # Option for the number of packets as a function of
    param = '-n' if platform.system().lower()=='windows' else '-c'

    # Building the command. Ex: "ping -c 1 google.com"
    command = ['ping', param, '1', host]

    return subprocess.call(command, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL) == 0

def GetData(url):
    response = requests.get(url, timeout=5)

    # print("GetData:" + smartmeterUrl)
    # print("Statuscode:" + str(response.status_code))
    
    if response.status_code == 200: # OK
        return response.content.decode("utf-8")
    else:
        return ""

def ParseJson(data):
    parsedData = json.loads(data)
    return parsedData

def main():
    pingOk = Ping(baseHostname)

    if pingOk:
        print("Ping OK")
        smartmeterData = GetData(smartmeterUrl)
        smartmeterJson = ParseJson(smartmeterData)
        print("JSON-dump:" + json.dumps(smartmeterJson))

    else:
        print("Ping failed, no data available!")

if __name__ == "__main__":
    main()