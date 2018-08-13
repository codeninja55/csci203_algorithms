#######################################################################
# CSCI203 - Exercise 1
# ex2.c - main() for exercise 2 execution
# Dinh Che | dbac496 | Last modified 2018.08.01
# Author: codeninja55
#######################################################################


# Heap implementation
from math import floor

HEAP = []
N_CTR = 0


def get_parent(i=0):
    return floor(i / 2)


def get_left(i=0):
    return (i * 2) + 1


def get_right(i=0):
    return (i * 2) + 2


def swap(idx1, idx2):
    HEAP[idx1], HEAP[idx2] = HEAP[idx2], HEAP[idx1]


def siftup(t, i=0):
    if i == 0:
        return

    parent = get_parent(i)

    if t[parent] > t[i]:
        return

    while (parent - 1) >= 0:
        if t[i] > t[parent]:
            swap(i, parent)
            parent = get_parent(parent)
        else:
            return


def recursive_siftdown(t, i):
    child = i * 2
    if t[child] < t[(i * 2) + 1]:
        child += 1
    if t[i] < t[child]:
        swap(i, child)
        recursive_siftdown(t, i)


def recursive_siftup(t, i):
    # Move element i up to its correct position
    if i == 0:
        return
    parent = i // 2
    if t[parent] > t[i]:
        return
    else:
        swap(i, parent)
        recursive_siftup(t, parent)


def makeheap():
    i = N_CTR / 2
    while i >= 0:
        recursive_siftdown(HEAP, i)
        i -= 1


def heappush(elem):
    global N_CTR
    HEAP.append(int(elem))
    recursive_siftup(HEAP, N_CTR)
    # siftup(HEAP, N_CTR)
    N_CTR += 1


def read_file(filename="Ex2.txt"):
    if filename:
        with open(filename, "r") as fin:
            if fin.closed:
                print("[DEBUG]: Error opening file.")
                exit(1)
            for line in fin:
                print(line.strip(), end=' ')
                heappush(line.strip())
            print('\n\n')
        fin.close()


if __name__ == "__main__":
    # filename = input("Input file name to read: ")
    read_file()
    for i in range(10):
        print("[{}] {}".format(i, HEAP[i]), end=' ')
