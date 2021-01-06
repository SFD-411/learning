#!/usr/bin/python

import threading
import socket
import optparse


def scanconnect(hostmach, port):
    try:
        suck = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        suck.connect((hostmach, port))
        print('|- %d/tcp open' % port)
    except Exception:
        global nono
    finally:
        suck.close()


def scanport(hostmach, portset):
    try:
        hostip = socket.gethostbyname(hostmach)
    except Exception:
        print(" ~!~ unresolved ip for %s" % hostmach)
    try:
        hostname = socket.gethostbyaddr(hostip)
        print("/- Scan Results for " + hostname[0] + " @ " + hostip)
    except Exception:
        print(" ~!~ unresolved hostname for %s" % hostmach)
        print("/- Scan Results for " + hostip[0])
    socket.setdefaulttimeout(1)
    for port in portset:
        t = threading.Thread(target=scanconnect, args=(hostmach, int(port)))
        t.start()


def main():
    parser = optparse.OptionParser('Usage: ' + '-s <host> -p <ports>')
    parser.add_option("-s", dest='hostmach', type='string', help='host')
    parser.add_option("-p", dest='portset', type='string', help='ports')
    (options, args) = parser.parse_args()
    hostmach = options.hostmach
    portset = str(options.portset).split(',')
    if (hostmach is None) | (portset[0] is None):
        print(parser.usage)
        exit(0)
    scanport(hostmach, portset)


if __name__ == '__main__':
    main()
