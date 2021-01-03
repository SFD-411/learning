import json
import difflib
from difflib import get_close_matches

diction = json.load(open("diction.json", "r"))

def translate(word):
    if word.title() in diction:
        return word, diction[word.title()]
    elif word.upper() in diction:
        return word.upper(), diction[word.upper()]
    elif word in diction:
        return word, diction[word]
    elif get_close_matches(word,diction.keys(), cutoff=0.8):
        wrongword = get_close_matches(word, diction.keys(), cutoff=0.8)[0]
        answer = input("\nDid you mean %s? \nYes or No? " % wrongword)
        if answer.upper()[0] == 'Y':
            return wrongword, diction[wrongword]
        elif answer.upper()[0] == 'N' and len(get_close_matches(word, diction.keys(), cutoff=0.8)) > 1:
            wrongword = get_close_matches(word, diction.keys(), cutoff=0.8)[1]
            answer = input("\nDid you mean %s? \nYes or No? " % wrongword)
            if answer.upper()[0] == 'Y':
                return wrongword, diction[wrongword]
            elif answer.upper()[0] == 'N':
                return "\nSorry. I don't think %s is a real word." % word
            else:
                return "\nInvalid Input. Try again."
        elif answer.upper()[0] == 'N':
            return "\nSorry. I don't think %s is a real word." % word
        else:
            return "\nInvalid Input. Try again."
    else:
        return "\nInvalid Word. Try again."

while True:
    userin = input("\nplease enter a word: ")
    userin = userin.lower()
    if userin != '\end':
        definition = translate(userin)
        if type(definition) != str:
            if definition[0] == definition[0].upper():
                print("\n",definition[0])
            else:
                print("\n",definition[0].title())
            for define in definition[1]:
                print(" - ", define)
        else:
            print(definition)
    else:
        print("game over")
        break

