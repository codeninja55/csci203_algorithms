#######################################################################
# CSCI203 - Exercise 1
# main.py - main() for exercise 1 execution
# Dinh Che | dbac496 | Last modified 2018.07.29
# Author: codeninja55
#######################################################################
import os

# Stack Implementation
_STACK = []


def read_file():
    # Change the directory back one where the text file is
    os.chdir("../")
    file = input("Input file to read: ")

    with open(file, "r") as fin:
        if fin.closed:
            print("[DEBUG] Error opening file.")
            exit(1)
        raw_input = fin.read().split()
        for line in raw_input:
            push(line)
    fin.close()


def push(elem):
    _STACK.append(elem)


def top():
    return _STACK[len(_STACK) - 1]


def isempty():
    return len(_STACK) == 0


def pop():
    return _STACK.pop() if not isempty() else None


if __name__ == "__main__":
    read_file()
    print("\n|===== POPPING WORDS =====|")
    while not isempty():
        print("{} ".format(pop()))
