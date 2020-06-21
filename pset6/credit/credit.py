from cs50 import get_int, get_string

number = get_int("Number: ")
cardNum = []
# split number into digits stored in list cardNum
for i in str(number):
    cardNum.append(int(i))
count = len(cardNum)
# or [int(i) for i in str(number)]
ans = 0
for num in cardNum[1::2]:
    ans += (num*2)%10 + (num*2)//10
for num in cardNum[::2]:
    ans += num
# first two digits
ftd = cardNum[0]*10 + cardNum[1]
if ans%10 == 0:
    if cardNum[0] == 4 and count >= 13 and count <= 16:
        print("VISA")
    elif (51 <= ftd <= 54) and count == 16:
        print("MASTERCARD")
    elif (ftd == 34 or ftd == 37) and count == 15:
        print("AMEX")
else:
    print("INVALID")
