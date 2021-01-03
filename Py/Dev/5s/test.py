import pandas

intervals = ["P1","m2","M2","m3","M3","P4","TT","P5","m6","M6","m7","M7"]
magic = ["0","1","0","1","0","0","1","0","1","0","1","0"]
majors = []
keylist = []
scalepos = []

for interval in intervals:
    if magic[intervals.index(interval)] == "0":
        majors.append(interval)
    else:
        majors.append("")

print(majors)

keys = pandas.DataFrame(
columns=["0","1","2","3","4","5","6","7","8","9","10","11"],
index=["0","1","2","3","4","5","6","7","8","9","10","11"])

def keymatrix(keys, majors, magic, intervals):
    # for int in intervals:
    for interval in intervals:
        keys[intervals.index(interval)] = majors[intervals.index(interval)]
    return keys

keymatrix(keys, majors, magic, intervals)

print(keys)
