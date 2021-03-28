import csv
import sys
from cs50 import SQL

def main():

    # check the correct number of command line arguments

    if len(sys.argv) != 2:
        sys.exit("Error. Usage: import.py FILENAME.csv")


    # open the sql database

    db = SQL("sqlite:///students.db")

    # open the file and then close it automatically

    with open(sys.argv[1], "r") as csvfile:

        reader = csv.DictReader(csvfile)

        # iterate through each row

        for row in reader:

            # split the names

            names = row["name"].split()
            first = names[0]

            # check if middle name is present

            if len(names) == 2:
              middle = None
              last = names[1]
            else:
                middle = names[1]
                last = names[2]

            # insert data into the database

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, row["house"], row["birth"])


if __name__ == "__main__":
    main()