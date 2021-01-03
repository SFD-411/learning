string = input("enter a string: ")

def wordlen(string):
    if type(string) == int:
         return "Sorry, integers don't have length"
    elif type(string) == float:
         return "Sorry, floats don't have length"
    else:
         return len(string)

print(wordlen(string))