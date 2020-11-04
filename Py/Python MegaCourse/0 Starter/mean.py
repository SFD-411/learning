def mean(mylist):
    if isinstance(mylist, dict):
        the_mean = sum(mylist.values()) / len(mylist)
    else:
        the_mean = sum(mylist) / len(mylist)
    return the_mean

grades = {"Marry": 99.7, "Sam": 87.5, "John": 73.6}
print(mean(grades))

stuffs = [5,1,6,8,13]
print(mean(stuffs)) 
