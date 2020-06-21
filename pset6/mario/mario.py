from sys import argv, exit
# define main function
def main():
    # ask user input
    maxHeights = input("Height: ")
    # if no input argument
    while len(argv) != 1:
        maxHeights = input("Height: ")
    # if not number like: foo
    while not maxHeights.isdigit():
        maxHeights = input("Height: ")
    maxHeights = int(maxHeights)
    # if input argument not in range of 1 to 8
    while not 1<= maxHeights <= 8:
        maxHeights = int(input("Height: "))
    height = 1
    draw(height, maxHeights)

# define draw function
def draw(height, maxHeights):
    # condition
    if height == maxHeights + 1:
        exit(1)
    # draw pyramin of height
    print(" " * (maxHeights-height) + "#" * height + "  " + "#" * height)
    # recursion to draw the next line
    draw(height + 1, maxHeights)

# call main function to start the programm
main()



