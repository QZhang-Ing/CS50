from sys import argv, exit
import csv
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# read database.csv
with open(argv[1], newline='') as file:
    if file.mode != 'r':
        print(f"database {argv[1]} can not be read")
        exit(1)
    database = csv.reader(file)
    for row in database:
        print(row)
# read DNA sequence
with open(argv[2], "r") as file:
    if file.mode != 'r':
        print(f"database {argv[2]} can not be read")
        exit(1)
    sequ = file.read()

print(sequ)
