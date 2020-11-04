import time
import os

while True:
    if os.path.exists("fruits.txt"):
        with open("fruits.txt") as myfile:
            fruits = myfile.read()
            print(fruits)
    else:
        print("File does not exist")
        
    time.sleep(5)
