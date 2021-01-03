from time import sleep
import pyautogui, os, fileinput, subprocess

#os.seteuid(0)
spam = input("Enter Spam Contents:")
print("Begin Spamming :" + spam)
sleep(3)

while True:
    pyautogui.write(spam)
    pyautogui.press('enter')
    sleep(0.2)

