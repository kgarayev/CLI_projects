# prompt user for input

while True:
    num_string = input("Number: ")
    if num_string.isdigit():
        break
    else:
        continue

num_int = int(num_string)

# add the checksums
sum1 = 0
sum2 = 0

for i in range(0, len(num_string), 2):
    sum2 += num_int % 10
    num_int = num_int // 10

    temp = (num_int % 10) * 2
    if temp < 10:
        sum1 += temp
    else:
        sum1 += (temp % 10) + (temp // 10)

    num_int = num_int // 10


final_sum = sum1 + sum2

# check the validity

if final_sum % 10 == 0:
    if len(num_string) == 15 and num_string[0] == '3' and (num_string[1] == '4' or num_string[1] == '7'):
        print("AMEX")
    elif len(num_string) == 16 and int(num_string[0]) == 5 and (int(num_string[1]) >= 1 and int(num_string[1]) <= 5):
        print("MASTERCARD")
    elif (len(num_string) == 16 or len(num_string) == 13) and int(num_string[0]) == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")