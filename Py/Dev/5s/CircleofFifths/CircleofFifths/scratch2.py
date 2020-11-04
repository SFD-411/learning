notes = ["C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab", "A", "A#/Bb", "B"]

C = notes[:]
Db = notes[1:] + notes[:1]
D = notes[2:] + notes[:2]
Eb = notes[3:] + notes[:3]
E = notes[4:] + notes[:4]
F = notes[5:] + notes[:5]
Gb = notes[6:] + notes[:6]
G = notes[7:] + notes[:7]
Ab = notes[8:] + notes[:8]
A = notes[9:] + notes[:9]
Bb = notes[10:] + notes[:10]
B = notes[11:] + notes[:11]

map(order, (C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B))

root = input("What is the root: ")
pentatonic = order
root = order()

print (root(order))

Major = notes[0], notes[2], notes[4], notes[5], notes[7], notes[9], notes[11]
Minor = notes[0], notes[2], notes[3], notes[5], notes[7], notes[8], notes[10]
Melodic = notes[0], notes[2], notes[3], notes[5], notes[7], notes[9], notes[11]
Harmonic = notes[0], notes[2], notes[3], notes[5], notes[7], notes[8], notes[11]
