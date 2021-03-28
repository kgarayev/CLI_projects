# prompt user for input

text = input("Text: ")

# count words letters and sentences

words = text.count(" ") + 1
sentences = text.count(".") + text.count("?") + text.count("!")
letters = 0

for i in text:
    if i.isalpha() == True:
        letters += 1
    else:
        continue

S = 100 * sentences / words
L = 100 * letters / words

# calculate index

index = int(round(0.0588 * L - 0.296 * S - 15.8))

if index > 0 and index < 17:
    print(f"Grade {index}")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade 16+")
