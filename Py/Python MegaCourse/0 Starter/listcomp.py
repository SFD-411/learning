temps = [221, 234, 340, 230, -9999]

actemps = [temp / 10 for temp in temps if temp > 0]

for act in actemps:
    print(act)
