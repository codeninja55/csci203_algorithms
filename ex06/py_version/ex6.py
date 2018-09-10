#######################################################################
# Title: CSCI203 - Exercise 6
# File: ex6.py - main() for exercise 6 execution
# Author: Dinh Che (codeninja55) | andrew at codeninja55.me
# UOW Details: dbac496 | 5721970 | dbac496 at uowmail.edu.au
# Last modified: 2018.09.03
#######################################################################
import os
import sys
from argparse import ArgumentParser
from pathlib import Path


def read_file(filename):
    """
    Reads the file with the passed in filename and completes the implementation of karp_rabin_search().
    :param filename: char array[] string, filename of the file to read.
    """
    if filename:
        with open(filename, 'r') as fin:
            if fin.closed:
                sys.exit(1)

            # Complete implementation below
            pass


def parse_args():
    """
    Wrapper function for argparse module to define the arguments for this script.
    :return: a parser with the arguments.
    """
    parser = ArgumentParser(prog='CN55 Exercise 6')
    parser.add_argument('filename', help='Enter file name to read from...')
    parser.add_argument('-f', '--filename', required=False, dest='filename')
    return parser.parse_args()


if __name__ == '__main__':
    print(os.getcwd())
    args = parse_args()
    if args.filename:
            file_path = Path(os.getcwd()) / args.filename
            read_file(filename=file_path)
