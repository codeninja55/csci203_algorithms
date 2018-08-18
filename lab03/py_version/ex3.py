#######################################################################
# CSCI203 - Exercise 3
# ex3.py - main() for exercise 3 execution
# Dinh Che | dbac496 | Last modified 2018.08.14
# Author: codeninja55
#######################################################################

import array
import os

filename = "Ex3.txt"
DATA = array.array('i', [0 for x in range(100)])
FORWARD = array.array('i', [0 for y in range(100)])
BACKWARD = array.array('i', [0 for z in range(100)])
VALID_COUNT = 0


def check(probe: int) -> bool:
    return 0 < BACKWARD[probe] <= VALID_COUNT and FORWARD[BACKWARD[probe]] == probe


def insert(elem: int, pos: int) -> None:
    global VALID_COUNT
    VALID_COUNT += 1
    DATA[pos] = elem
    FORWARD[VALID_COUNT] = pos
    BACKWARD[pos] = VALID_COUNT


if __name__ == '__main__':
    cwd = os.getcwd()
    print(cwd)

    with open(filename, 'r') as fin:
        if fin.closed:
            exit(1)

        while True:
            line = fin.readline()
            line_arr = line.split()

            if len(line_arr) == 1 and line_arr[0] == '-1' or line == '':
                break

            if len(line_arr) == 2 and line_arr[0] == '-1':
                continue

            if len(line_arr) == 2 and not line_arr[0] == '-1':
                insert(int(line_arr[0]), int(line_arr[1]))

            if len(line_arr) == 1:
                print("{test} : {value}".format(
                    test=("TRUE"
                          if check(probe=int(line_arr[0]))
                          else "FALSE"),
                    value=("Value: " + str(DATA[int(line_arr[0])])
                           if check(probe=int(line_arr[0]))
                           else "Probe: " + line_arr[0])
                ))
