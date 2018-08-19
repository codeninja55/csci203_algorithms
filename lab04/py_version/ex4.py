#######################################################################
# Title: CSCI203 - Exercise 4
# File: ex4.py - main() for exercise 4 execution
# Author: Dinh Che (codeninja55) | andrew at codeninja55.me
# UOW Details: dbac496 | 5721970 | dbac496 at uowmail.edu.au
# Last modified: 2018.08.14
# REFERENCE: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
#######################################################################

import os
import sys
from argparse import ArgumentParser
from pathlib import Path

COUNTER = 0


class TreeNode(object):
    """
    Generic Tree Node class.
    """

    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1


class AVLTree(object):
    """
    The AVL Tree class which supports all AVL operations.
    """

    def get_height(self, node):
        return 0 if not node else node.height

    def get_balance(self, node):
        return 0 if not node else self.get_height(node.left) - self.get_height(node.right)

    def inorder_sort(self, root):
        global COUNTER
        if root.left:
            self.inorder_sort(root.left)

        if not (COUNTER == 0) and (COUNTER % 10) == 0:
            print('\n', end='')
        COUNTER += 1
        print("{0:5d}".format(root.key), end='')

        if root.right:
            self.inorder_sort(root.right)

    def right_rotate(self, node2):
        node1 = node2.left
        temp2 = node1.right
        # Perform rotation here
        node1.right = node2
        node2.left = temp2
        # Update the new heights
        node2.height = 1 + max(self.get_height(node2.left), self.get_height(node2.right))
        node1.height = 1 + max(self.get_height(node2), self.get_height(node1.right))
        return node1

    def left_rotate(self, node2):
        node1 = node2.right
        temp1 = node1.left
        # Perform rotation here
        node1.left = node2
        node2.right = temp1
        # Update heights
        node2.height = 1 + max(self.get_height(node2.left), self.get_height(node2.right))
        node1.height = 1 + max(self.get_height(node2), self.get_height(node1.right))
        return node1

    def double_right_rotate(self, node3):
        node3.left = self.left_rotate(node3.left)
        return self.right_rotate(node3)

    def double_left_rotate(self, node3):
        node3.right = self.right_rotate(node3.right)
        return self.left_rotate(node3)

    def insert(self, root, key):
        """
        A recursive class function to insert a new node into the tree with rotation balancing.
        :param root: The root node of the tree.
        :param key: The new key to insert.
        :return: The node inserted or the node after rotation.
        """
        # Perform normal BST
        # root = self.bst_insert(root, key)
        if not root:
            return TreeNode(key)
        elif key == root.key:
            return root
        elif key < root.key:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)

        # Update the height of the parent node
        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        # Get the balance factor to use in different cases
        balance = self.get_balance(root)

        # If the node is imbalanced, then try out each of the four cases
        # CASE 1
        if balance > 1 and key < root.left.key:
            return self.right_rotate(root)

        # CASE 2
        if balance < -1 and key > root.right.key:
            return self.left_rotate(root)

        # Case 3
        if balance > 1 and key > root.left.key:
            return self.double_right_rotate(root)

        # Case 4
        if balance < -1 and key < root.right.key:
            return self.double_left_rotate(root)

        # Otherwise if no balancing rotations needed, return the node
        return root


class BinarySearchTree(object):
    def bst_insert(self, root, key):
        """
        A recursive function to insert a new TreeNode into the tree without rotation balancing.
        :param root: The root node of the tree or None.
        :param key: The new key to insert.
        :return: The updated root node or a new TreeNode(key)
        """
        left = False

        if not root:  # No root node so create new one
            return TreeNode(key)

        if key == root.key:  # Already in the tree
            return None
        elif key < root.key:  # Go LEFT
            next_node = root.left
            left = True
        else:
            next_node = root.right
            left = False

        if next_node is not None:  # If next is not set, traverse the tree
            self.bst_insert(next_node, key)
        else:
            if left:
                root.left = TreeNode(key)
            else:
                root.right = TreeNode(key)
        return root


def read_file(filename):
    global AVL_TREE
    global ROOT

    if filename:
        with open(filename, 'r') as fin:
            if fin.closed:
                sys.exit(1)

            for line in fin:
                try:
                    key = int(line)
                    ROOT = AVL_TREE.insert(ROOT, key)
                except ValueError as e:
                    print('[DEBUG]: Cannot convert line to integer [ {} ]\n'
                          .format(e))


def parse_args():
    parser = ArgumentParser(prog='CN55 AVL Tree Implementation',
                            description='''This python script is an implementation
                            of CSCI203 - Algorithms and Data Structures (Spring 2018)
                            AVL Binary Search Trees.''')
    parser.add_argument('filename', help='Enter file name to read from.')
    parser.add_argument('-f', '--filename', required=False, dest='filename',
                        help='Enter file name to read from.')
    return parser.parse_args()


if __name__ == '__main__':
    AVL_TREE = AVLTree()
    ROOT = None

    print(os.getcwd())
    args = parse_args()
    if args.filename:
        file_path = Path(os.getcwd()) / args.filename
        read_file(file_path)
    AVL_TREE.inorder_sort(ROOT)
