import sys
import subprocess
import os
import discord
import asyncio

from time import sleep
from config import *

client = discord.Client()
toker = 'mfa.FZt-FrcvT2GAVZGe0gRsLB9UhZQJHRve9tgFcFolCJK-J6mXsX8q5FD6pfXNqhXDJV_sxw6c_Fkc0UXQFqIg'
channel = '774007372317458472'

spam = input("Enter Spam: ")

@client.event
async def on_ready():
    print("Spam Begins!")
    while not client.is_closed:
        print(spam)
        await client.send_message(discord.Object(id=channel), spam)
        await asyncio.sleep(0.7)

client.run(toker, bot=False)
