import csv
import sys

# main function


def main():

    if len(sys.argv) != 3:
        sys.exit("Error. Usage dna.py FILENAME.csv FILENAME.txt")

    database = []
    counts = {}
    # open and read csv file
    with open(sys.argv[1], "r") as csvfile:
        reader = csv.reader(csvfile)
        header = next(reader)

        for row in reader:

            person = {}

            for i in range(len(header)):
                person[header[i]] = row[i]

            database.append(person)

# open and read text file
    with open(sys.argv[2], "r") as textfile:
        sequence = textfile.read()

    # count consecutive STRs
    for i in range(1, len(header), 1):
        counts[header[i]] = max_str(header[i], sequence)

    match = "No match"

    # compare dictionaries and check the match (if any)
    for j in range(len(database)):
        c = 0
        for key in counts:
            if int(counts[key]) != int(database[j][key]):
                break
            else:
                c += 1
        if c == len(counts):
            match = database[j]["name"]

    print(match)


# count maximum consecutive STRs
def max_str(STR, sequence):

    maximum = 0
    counter = 0

    current_index = sequence.find(STR)

    if current_index == -1:
        return 0

    else:
        counter += 1
        while current_index != -1:

            next_index = sequence.find(STR, current_index + 1, len(sequence))

            if next_index == current_index + len(STR):
                counter += 1
            else:
                counter = 1

            if counter > maximum:
                maximum = counter

            current_index = next_index

    return maximum


if __name__ == "__main__":
    main()