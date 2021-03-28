import csv
import sys
from cs50 import SQL

def main():

    # check the correct number of command line arguments

    if len(sys.argv) != 2:
        sys.exit("Error. Usage: import.py HOUSENAME")

    # open the sql database

    db = SQL("sqlite:///students.db")

    # print the required information into a list of dictionaries

    roster = db.execute("SELECT first, middle, last, birth FROM students WHERE (house = ?) ORDER BY last, first", sys.argv[1])

    # iterate the list

    for row in roster:

        # print each person

        if row["middle"] == None:
            print(f'{row["first"]} {row["last"]}, born {row["birth"]}')
        else:
            print(f'{row["first"]} {row["middle"]} {row["last"]}, born {row["birth"]}')


if __name__ == "__main__":
    main()

