def mean(*args):
    return sum(args) / len(args)
print(mean(1,3,4))

def avg(**kwargs):
    return kwargs
print(avg(a=1, b=2, c=5, ae=99))
