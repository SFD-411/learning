import pandas

intervals = ["P1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7"]
magic = ["0", "1", "0", "1", "0", "0", "1", "0", "1", "0", "1", "0"]
majors = []
keylist = []
scalepos = []

for interval in intervals:
    if magic[intervals.index(interval)] == "0":
        majors.append(interval)
    else:
        majors.append("")

keys = pandas.DataFrame(
columns=["C", "#/b", "D", "#/b", "E", "F", "#/b", "G", "#/b", "A", "#/b", "B"], 
index=["C", "G", "D", "A", "E", "B", "F#/Gb", "Db", "Ab", "Eb", "Bb", "F"])

def keymatrix(keys, majors, magic, intervals):
    # for int in intervals:
    for interval in intervals:
        keys[intervals.index(interval)] = majors[intervals.index(interval)]
    return keys

keymatrix(keys, majors, magic, intervals)

print(keys)
