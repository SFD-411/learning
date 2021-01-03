import time
import os
import pandas

while True:
    if os.path.exists("weather.csv"):
        data = pandas.read_csv("weather.csv")
        print(data.mean()["st1"])
    else:
        print("file does not exist.")
    time.sleep(5)
