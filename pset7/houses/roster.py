
import cs50
from sys import exit, argv

# check input argument if exist
if len(argv) != 2:
    print("Usage: roster.py housename")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

# select everything based on house
students = db.execute("SELECT * FROM students WHERE house=(?) ORDER BY last", argv[1])

# print based on if middle name exists
for student in students:
    if student['middle'] != None:
        print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")
    else:
        print(f"{student['first']} {student['last']}, born {student['birth']}")

