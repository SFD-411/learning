import time
from datetime import datetime as dati

hoster="hosts"
redirect="127.0.0.1"
weblist=["www.facebook.com","facebook.com"]

while True:
    if dati(dati.now().year, dati.now().month, dati.now().day, 8) < dati.now() < dati(dati.now().year, dati.now().month, dati.now().day, 15):
        with open(hoster,'r+') as file:
            content=file.read()   
            print(content)
            for sites in weblist:
                if sites in content:
                    pass
                else:
                    file.write(redirect + "    " +sites + "\n")
    else:
        with open(hoster, 'r+') as file:
            content=file.readlines()
            file.seek(0)
            print(content) 
            for lines in content:
                if not any(sites in lines for sites in weblist):
                    file.write(lines)
            file.truncate()
    time.sleep(10)
    
