import time

while True:
    with open("fruits.txt") as myfile:
        fruits = myfile.read()
        print(fruits)
        time.sleep(5)
