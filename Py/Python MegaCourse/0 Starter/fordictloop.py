grades = {"Mary": 99.9, "Sam": 83.7, "David": 73.3}

for grade in grades.items(): #prints out tuples
    print(grade)

for grade in grades:
    print(grade,grades[grade])
