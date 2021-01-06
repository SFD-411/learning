#!/usr/bin/python

import socket
import sys


CURSOR_UP_ONE = '\x1b[1A'
ERASE_LINE = '\x1b[2K'
host = input("_/- Scan IP : ")
count = 0


def portscan(port):
    try:
        sek = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sek.connect((host, port))
        print(" is Open")
    except Exception:
        global count
        count += 1
    finally:
        sek.close()


for port in range(65536):
    sys.stdout.write('\r')
    sys.stdout.write("|- %d" % port)
    sys.stdout.flush()
    if port == 65535:
        print(CURSOR_UP_ONE + ERASE_LINE)
    portscan(port)
    socket.setdefaulttimeout(1)

print("%d inaccessable ports" % count)
