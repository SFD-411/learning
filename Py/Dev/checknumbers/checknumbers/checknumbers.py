user_in = float(input("Enter a number between 1 and 100: "))
hidden_no = 99

while user_in != hidden_no:
    if user_in >100:
        print("Guess a Number Between 1 and 100!!!")
        user_in = float(input("Enter a number between 1 and 100: "))
    elif user_in < 0:
        print("Guess a Number Between 1 and 100!!!")
        user_in = float(input("Enter a number between 1 and 100: "))
    elif user_in > hidden_no:
        print(TOO HIGH! TRY AGAIN!")
        user_in = float(input("Enter a number between 1 and 100: "))
    elif user_in < hidden_no:
        print("Too Low!!")
        user_in = float(input("Enter a number between 1 and 100: "))
else:
    print("YOU GUESSED IT!! GOOD JOB!")
