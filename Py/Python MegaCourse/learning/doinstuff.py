python3
dir(somefunction)



#Lists strings and tuples have a positive and negative index system.

#``-- LIST --``

max(somelist()) #- returns maximum value
somelist.count(someitem) #- returns count of someitem
somelist.append(1) #- adds 1 to end of list
somelist.insert(0,1) #- adds 1 to beginning of list
somelist.clear() #- empties list
somelist.remove(4) #- removes the 5th item
somelist[4] #- calls the 5th item
somelist[2:] #- calls items from position 3 to end


# --- list comprehension --
temps = [124, 228, 731]
newtemps = [temp / 10 for temp in temps]
value = sum[for temp in temps] 



#``-- STRING --``

#VV Case Sensitivity VV
string.upper() 
string.lower()
string.title() 


#``-- DICTIONARY --``
#in 
grades = {"mary": 97.1,"john": 68.8,"dave": 87.5}
grades["dave"] #returns 87.5
grades.items() #returns tuples of each paired item.
grades.keys() # returns the first item
grades.values() #returns the second item


#``-- Functions --``
def foo(var):    #- defines a function
    val = var    #- declares a variable and some thing
    return val   #- outputs the variable val

if var == 0 and isinstance(var, int):
    print var   
elif var == 1 or type(var) == float:
    print var
else:
    print none

if 3 > 1: # is the same as
if true:

# functions can take multiple parameters, listed or nonlisted
def volume(a,b,c = 7):
    return a * b * c

# reading files with RW function
with open("filetype", "a+") as variable: # "w" overwrites "r" is readonly
    variable.seek(somevalue)
    contents = variable.read()
    variable.write(content)


name = input("Enter your name: ") #prints message and stores input in name

#the below shows string formatting in python 3
name = "Sim"
experience = 1.5
print("{} has {} years of experience".format(name, experience))



## ---- PANDAS ----

#dataframe
df = pandas.DataFrame([{"key": "item", "index2", "item2"}, {"key": "another", "index2", "item4"}])
