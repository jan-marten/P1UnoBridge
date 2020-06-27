#!/usr/bin/python3.7

from LoadConfiguration import LoadConfig
from GetData import *
from SendSocketData import *

def main():
    config = LoadConfig()

    pingMonitor = Ping(config.get('P1Monitor', 'Hostname'))
    if (pingMonitor == False):
        raise NameError('P1Monitor.ping failed')

    pingBridge = Ping(config.get('P1UnoBridge', 'Hostname'))
    if (pingBridge == False):
        raise NameError('P1UnoBridge.ping failed')

    baseUrl = "http://" + config.get('P1Monitor', 'Hostname') + "/api/v1/"
    smartmeterUrl = "" + baseUrl + "smartmeter?limit=1"

    data = GetData(smartmeterUrl)
    SendData(config.get('P1UnoBridge', 'Hostname'), config.getint('P1UnoBridge', 'Port'), data)

if __name__ == "__main__":
    main()