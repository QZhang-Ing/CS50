import csv
from sys import exit, argv
import cs50

# check input argument if exist
if len(argv) != 2:
    print("Usage: import.py filename.csv")
    exit(1)

# creat database using cs50.SQL
db = cs50.SQL("sqlite:///students.db")

# open csv file
with open(argv[1]) as file:

    # csv reader
    reader = csv.DictReader(file)

    # iterate over csv file
    for row in reader:
        #insert
        # parse name and split it
        fullname = row["name"].split()

        if len(fullname) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)",
                        fullname[0], fullname[1], fullname[2], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)",
                        fullname[0], None, fullname[1], row["house"], row["birth"])

