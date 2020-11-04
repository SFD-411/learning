def sent_maker(phrase):
    interrogatives = ("who", "when", "how", "what", "why")
    capitalized = phrase.capitalize()
    if phrase.startswith(interrogatives):
        return "{}?".format(capitalized)
    else:
        return "{}.".format(capitalized)

with open("texter.txt", "w") as clear:
    clear.write("")

while True:
    user = input("Say something: ")
    if user == "\end":
        with open("texter.txt", "r") as outter:
            print(outter.read())
        break
    else:
        with open("texter.txt", "a") as chatlog:
            chatlog.write(user)
            chatlog.write(" ")
        continue
