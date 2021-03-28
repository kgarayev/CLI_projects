# prompt user for input
#exitreject if not integer

while True:
    height = input("Height: ")
    try:
        height = int(height)
    except ValueError:
        continue

    if height >= 1 and height <= 8:
        break

row = height

# print the pyramids

for i in range(height):

    for j in range(row - 1):
        print(" ", end='')

    for k in range(i + 1):
        print("#", end='')

    print("  ", end='')

    for l in range(i + 1):
        print("#", end='')

    print("")

    row -= 1
