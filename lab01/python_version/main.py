#######################################################################
# CSCI203 - Exercise 1
# main.py - main() for exercise 1 execution
# Dinh Che | dbac496 | Last modified 2018.07.29
# Author: codeninja55
#######################################################################
import os

# Stack Implementation
_STACK = []
_CTR = 0


def read_file():
    # Change the directory back one where the text file is
    os.chdir("../")

    # file = input("Input file to read: ")
    # TODO: TESTING
    file = "Ex1.txt"

    with open(file, "r") as fin:
        if fin.closed:
            print("[DEBUG] Error opening file.")
            exit(1)
        raw_input = fin.read().split()
        for line in raw_input:
            push(line)

    fin.close()

    for word in _STACK:
        print("{}".format(word))

    print("\n|===== POPPING WORDS =====|")
    while not isempty():
        print("Popping top word: {}".format(pop()))


def push(elem):
    global _CTR
    _CTR += 1
    _STACK.append(elem)


def top():
    return _STACK[_CTR - 1]


def isempty():
    return _CTR == 0


def pop():
    global _CTR
    if isempty():
        return None
    else:
        _CTR -= 1
        return _STACK[_CTR]


if __name__ == "__main__":
    read_file()
