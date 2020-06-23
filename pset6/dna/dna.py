from sys import argv, exit
import csv
import re

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # read DNA sequence
    with open(argv[2], "r") as file:
        if file.mode != 'r':
            print(f"database {argv[2]} can not be read")
            exit(1)
        sequence = file.read()

    # read database.csv
    with open(argv[1], newline='') as file:
        if file.mode != 'r':
            print(f"database {argv[1]} can not be read")
            exit(1)
        # get the heading of the csv file in order to obtain STRs
        csv_reader = csv.reader(file)
        headings = next(csv_reader)
        # dictionary to store STRs match result of DNA-sequence
        STR_counter = {}
        for STR in headings[1::]:
            # entry result accounting to the STR keys
            STR_counter[STR] = countSTR(STR, sequence)
    # read csv file as a dictionary
    with open(argv[1], newline='') as file:
        database = csv.DictReader(file)
        for row in database:
            count = 0
            for STR in STR_counter:
                # print("row in database ", row[STR], "STR in STR_counter", STR_counter[STR])
                if int(row[STR]) == int(STR_counter[STR]):
                    count += 1
            if count == len(STR_counter):
                print(row['name'])
                exit(0)
        else:
            print("No match")

# find non-overlapping occurrences of STR in DNA-sequence
def countSTR(STR, sequence):
    count = 0
    maxcount = 0
    # in order to match repeat STR. for example: "('AATG')+" as pattern
    # into re.compile() to match repeat STR
    # rewrite STR to "(STR)+"
    STR = "(" + STR + ")+"
    pattern = re.compile(r'STR')
    # matches should be a iterator object
    matches = pattern.finditer(sequence)
    # go throgh every repeat and find the longest one
    # by match.end() - match.start()
    for match in matches:
        count = match.end() - match.start()
        if count > maxcount:
            maxcount = count
    # return repeat times of the longest repeat
    return maxcount/len(STR)

main()

