userfn = input("Enter your first name: ")
userln = input("Enter your last name: ")

message = "Hello %s %s" % (userfn, userln)     #python 2 through 3.5
message = f"Hello {userfn} {userln}"       #python 3.6 and later 
print(message)
