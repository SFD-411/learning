from time import sleep
import pyautogui, os, fileinput, subprocess

#os.seteuid(0)
spamfile = open("332", 'r')
spam = spamfile.read()
print("Begin Spam.")
sleep(3)

while True:
    pyautogui.write(spam, 0.015)
    pyautogui.press('enter')
    sleep(0.2)

