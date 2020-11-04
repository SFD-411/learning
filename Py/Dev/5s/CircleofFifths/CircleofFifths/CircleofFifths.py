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

order = [C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B]

root = input("What is your root note? ")

Major = scale[0], scale[2], scale[4], scale[5], scale[7], scale[9], scale[11]
Minor = scale[0], scale[2], scale[3], scale[5], scale[7], scale[8], scale[10]
Melodic = scale[0], scale[2], scale[3], scale[5], scale[7], scale[9], scale[11]
Harmonic = scale[0], scale[2], scale[3], scale[5], scale[7], scale[8], scale[11]

