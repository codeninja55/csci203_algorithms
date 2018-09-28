#######################################################################
# Title: CSCI203 - Exercise 7
# File: ex7.py - main() for exercise 6 execution
# Author: Dinh Che (codeninja55) | andrew at codeninja55.me
# UOW Details: dbac496 | 5721970 | dbac496 at uowmail.edu.au
# Last modified: 2018.09.24
#######################################################################
import os
import sys
from argparse import ArgumentParser
from pathlib import Path
from typing import List


# Globals
n_size = 0


class Queue:
    """Class Queue to represent an array implementation of a FIFO queue."""

    def __init__(self, capacity):
        self._size = 0
        self._head = -1
        self._tail = -1
        self._capacity = capacity
        self.Q = [None] * capacity  # initialise Q list

    # queue is full when size becomes equal to the capacity
    def is_full(self):
        return self._size == self._capacity

    # queue is empty when size is 0
    def is_empty(self):
        print("Queue is Empty.")
        return self._size == 0

    def enqueue(self, elem):
        if self.is_full():
            print("FULL")
            return

        if self._head is -1:
            self._head = 0
        self._tail += 1
        self.Q[self._tail] = elem
        self._size += 1

    def dequeue(self):
        if not self.is_empty:
            print("EMPTY")
            return

        ret = self.Q[self._head]
        self._head += 1
        if self._head > self._tail:
            self._head = self._tail = -1
        self._size -= 1
        return ret

    def front(self):
        if self.is_empty():
            print("Queue is empty")

        return self.Q[self._head]

    def rear(self):
        if self.is_empty():
            print("Queue is empty")

        return self.Q[self._tail]


class Graph:
    """A simple representation of graph using Adjacency Matrix."""

    def __init__(self, n_vertex):
        self.adj_matrix = [[0] * n_vertex for _ in range(n_vertex)]  # will create adj_matrix[[-1] * n_vertex]
        self._n_vertex = n_vertex
        self.vertices = {}
        self.vertices_list = [0] * n_vertex

    def set_vertex(self, idx):
        self.vertices[idx] = idx
        self.vertices_list[idx] = idx

    def set_edge(self, frm, to):
        frm = self.vertices[frm]
        to = self.vertices[to]
        self.adj_matrix[frm][to] = 1
        self.adj_matrix[to][frm] = 1  # for directed graph do not add this

    def get_vertex(self):
        return self.vertices_list

    def get_edges(self):
        edges = []
        for i in range(self._n_vertex):
            for j in range(self._n_vertex):
                if self.adj_matrix[i][j] is not 0:
                    edges.append((self.vertices_list[i], self.vertices_list[j]))
        return edges

    def get_matrix(self):
        return self.adj_matrix

    def size(self):
        return self._n_vertex


def BFS(s: any, adj: Graph) -> List:
    visited = []  # set of vertices visited
    q = Queue(adj.size())  # queue of vertex

    q.enqueue(s)

    while not q.is_empty():
        current = q.dequeue()
        visited.append(current)

        for v_idx, val in enumerate(adj.get_matrix()[current]):
            if v_idx not in visited and val is 1:
                q.enqueue(v_idx)
                print("Visited: " + str(v_idx))
    return visited


def read_file(filename):
    """
    Reads the file with the passed in filename and completes the implementation of karp_rabin_search().
    :param filename: char array[] string, filename of the file to read.
    """
    global n_size

    if filename:
        with open(filename, 'r') as fin:
            if fin.closed:
                sys.exit(1)

            # complete implementation below
            n_size = fin.readline()
            G = Graph(int(n_size))

            for line in fin.readlines():
                line_ls = line.split()
                v = int(line_ls[0])
                v_to = int(line_ls[1])
                G.set_vertex(v)
                G.set_edge(v, v_to)

            return G


def parse_args():
    """
    Wrapper function for argparse module to define the arguments for this script.
    :return: a parser with the arguments.
    """
    parser = ArgumentParser(prog='CN55 Exercise 7')
    parser.add_argument('filename', help='Enter file name to read from...')
    parser.add_argument('-f', '--filename', required=False, dest='filename')
    return parser.parse_args()


if __name__ == '__main__':
    print(os.getcwd())

    args = parse_args()
    if args.filename:
        file_path = Path(os.getcwd()) / args.filename
        G = read_file(filename=file_path)

    print("Number of Vertices: " + str(G.size()))
    print("Vertices of Graph")
    print(G.get_vertex())
    print("Edges of Graph")
    print(G.get_edges())
    print("Adjacency Matrix of Graph")
    print(G.get_matrix())

    # v = BFS(0, G)
    # print(v)
