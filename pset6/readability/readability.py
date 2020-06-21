from cs50 import get_string
text = get_string("Text:")
countLetter = 0
countWord = 1
countSen = 0

# count letters
for char in text:
    if char.lower() >= 'a' or char.lower() >= 'z':
        countLetter += 1
# count words
for char in text:
    if char == ' ':
        countWord += 1
# count sentenses
for char in text:
    if char == '.' or char == '?' or char == '!':
        countSen += 1

# calculate the grade
L = countLetter / countWord * 100
S = countSen / countWord * 100
result = round(0.0588 * L - 0.296 * S - 15.8)

# output result
if result < 1:
    print("Before Grade 1")
elif result >= 16:
    print("Grade 16+")
else:
    print(f"Grade {result}")

