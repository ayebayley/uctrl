#!/bin/python3

import serial
import time
import configparser

CONF    = '/srv/http/cgi-bin/datagram.conf'
SET_ON  = '1'
SET_OFF = '0'
BRIDGE  = 'bridge'
SET     = 'set'
SD      = 'speed_dial'
SD_CAL  = '1'
SD_ON   = '2'
SD_OFF  = '3'
SD_TOG  = '4'
SD_RGD  = '5'

def hexstr(n, pad):
    hex_n=('%0.'+str(pad)+'x')%n
    return hex_n

def sendCommand(device, cmd):
    print("Sending command " + cmd + "...")
    device.write(bytes(cmd, encoding='utf-8'))
    time.sleep(2)

def getChecksum(cmd):
    ck=0
    for b in cmd:
        ck+=ord(b)
    ck%=16
    return hexstr(ck, 1)

def getCommand(cmd, rw, reg, data):
    command=hexstr(cmd, 2)+hexstr(rw, 1)+hexstr(reg, 4)+hexstr(data, 4)
    command+=getChecksum(command)
    return command

def resetConf(config, cmd_type):
    config[BRIDGE][SET] = SET_OFF
    config[SD][SET] = SET_OFF
    if cmd_type == 0:
        config[BRIDGE]['rw']   = SET_OFF
        config[BRIDGE]['reg']  = SET_OFF
        config[BRIDGE]['data'] = SET_OFF
    elif cmd_type == 5:
        config[SD][SD_RGD] = '0000 0'
    else:
        config[SD][str(cmd_type)] = '0000'        
    with open(CONF, 'w') as updated_conf:
        config.write(updated_conf, space_around_delimiters=False)
        
def main():
    device = serial.Serial('/dev/ttyACM1')
    config = configparser.ConfigParser()
    while True:
        config.read(CONF)
        if config[BRIDGE][SET] == SET_ON: # Bridge activated
            if config[BRIDGE]['rw'] == '0': # Bridge read
                cmd = getCommand(10, 0, int(config[BRIDGE]['reg']),
                                 int(config[BRIDGE]['data'], base=2))
            else:
                cmd = getCommand(10, int(config[BRIDGE]['rw']), int(config[BRIDGE]['reg']),
                                 int(config[BRIDGE]['data']))
            sendCommand(device, cmd)
            resetConf(config, 0)
        elif config[SD][SET] != SET_OFF:
            if config[SD][SET] == SD_CAL:
                cmd = getCommand(1, 0, 0, int(config[SD][SD_CAL], base=2))
                sendCommand(device, cmd)
                resetConf(config, 1)
            elif config[SD][SET] == SD_ON:
                cmd = getCommand(2, 0, 0, int(config[SD][SD_ON], base=2))
                sendCommand(device, cmd)
                resetConf(config, 2)
            elif config[SD][SET] == SD_OFF:
                cmd = getCommand(3, 0, 0, int(config[SD][SD_OFF], base=2))
                sendCommand(device, cmd)
                resetConf(config, 3)
            elif config[SD][SET] == SD_TOG:
                cmd = getCommand(4, 0, 0, int(config[SD][SD_TOG], base=2))
                sendCommand(device, cmd)
                resetConf(config, 4)
            elif config[SD][SET] == SD_RGD:
                bits = config[SD][SD_RGD].split(' ')[0]
                cycles = config[SD][SD_RGD].split(' ')[1]
                cmd = getCommand(5, 0, int(cycles), int(bits, base=2))
                sendCommand(device, cmd)
                resetConf(config, 5)                
        time.sleep(1)
        
main()
