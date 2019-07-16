import serial
import time

def hexstr(n, pad):
    hex_n=('0x%0.'+str(pad) + 'x') % n
    return hex_n[2:]

def sendCommand(device, cmd):
    device.write(bytes(cmd, encoding='utf-8'))

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
    
def main():
    device = serial.Serial('/dev/ttyACM0')
    for i in range(1, 22):
        cmd = getCommand(10, 0, 30000+i, 15)
        print(cmd)
        sendCommand(device, cmd)
        time.sleep(2)

main()
