#!/usr/bin/python3.7

import os
import configparser

configFilename = "./Config.ini"

def LoadConfig():
    if (os.path.isfile(configFilename)):
        config = configparser.ConfigParser()
        config.read(configFilename)
        return config
    else:
         raise NameError('Config file not found')

def main():
    Config = LoadConfig()
    print(Config.sections())

if __name__ == "__main__":
    main()