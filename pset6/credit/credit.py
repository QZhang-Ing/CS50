from cs50 import get_int
import math

number = get_int("Number: ")
count_digits = 0
ans = 0

count_digits = int(math.log10(number)) + 1

# initialize list to store each digits
digits = []
for digit in range (count_digits):
    digits.append(number%10)
    # integer division
    number = number//10
# multiplying by 2 and store them in an new array
index = 0
for digit in digits:
    if index%2 == 0:
        index += 1
        continue
    tmp = digit * 2
    ans += tmp%10 + tmp//10
    index += 1
# add all together
index = 2
for digit in digits:
    if (index%2) != 0:
        index += 1
        continue
    ans = ans + digit
    index += 1

# first two digits
ftd = digits[0]*10 + digits[1]
if ans%10 == 0:
    if digits[0] == 4 and count_digits >= 13 and count_digits <= 16:
        print("VISA")
    elif 51 <= ftd <= 54 and count_digits == 16:
        print("MASTERCARD")
    elif (ftd == 34 or ftd == 37) and count_digits == 15:
        print("AMEX")
else:
    print("INVALID")
