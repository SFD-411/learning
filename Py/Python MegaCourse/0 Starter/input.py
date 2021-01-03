def weather_condition(temperature):
    if temperature > 7:
        return "Warm"
    else:
        return "Cold"

usein = float(input("What is your temperature? "))

print (weather_condition(usein))
