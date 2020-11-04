import difflib
from difflib import get_close_matches
import mysql.connector
con = mysql.connector.connect(
user = "ardit700_student",
password = "ardit700_student",
host = "108.167.140.122",
database = "ardit700_pm1database"
)

cursor = con.cursor()

while True:
    userin = input("Define: ")
    if userin.lower() != '\end':
        query = cursor.execute("SELECT * FROM Dictionary WHERE Expression = '%s' " % userin)
        results = cursor.fetchall()
        if results:
            for item in results:
                print(" - ",item[1])
        else:
            print("%s was not found" % userin )
    else:
        break
