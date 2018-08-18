/*********************************************************************
* Title: CSCI203 - Assignment 1
* File: ex4.c - main() driver for exercise 4 implementation
* Author: Dinh Che (codeninja55) andrew at codeninja.me
* UOW Details: dbac496 | 5721970 | dbac496 at uowmail.edu.au
* Last modified: 2018.08.18
*********************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <helper.h>

typedef struct Node {
    long int key;
    struct Node *left, *right;
    int height;
} Node;

/* GLOBAL VARS */
int COUNTER = 0;

/* FUNCTION PROTOTYPES */
Node* bst_insert_first(long int);
void bst_insert(Node*, long int);
void in_order_sort(Node*);
// void avl_insert(Node*, Node);
// void avl_rotate_right(Node);
// void avl_rotate_left(Node);
// void avl_double_rotate_right(Node);
// void avl_double_rotate_left(Node);
int max(int, int);

int main(int argc, const char* argv[])
{
    char filename[200];
    if (argc == 2) strcpy(filename, argv[1]);
    else {
        printf("[USAGE]: ex4 <filename> | OR \nInput file name: ");
        scanf("%s", filename);
    }

    FILE *fd;
    if ( (fd = fopen(filename, "r")) == NULL ) {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]", strerror(1));
        exit(1);
    }

    Node *ROOT = NULL;
    long int key;

    while ( fscanf(fd, "%li\n", &key) == 1 ) {
        if ( ROOT == NULL ) ROOT = bst_insert_first(key);
        else bst_insert(ROOT, key);
    }

    fclose(fd);
    in_order_sort(ROOT);
    return 0;
}


// Insert the first node into the position of the ROOT pointer
Node* bst_insert_first(long int key)
{
    Node *first_node_ptr = (Node *) ec_malloc(sizeof(Node));
    first_node_ptr->key = key;
    first_node_ptr->height = 0;
    first_node_ptr->left = first_node_ptr->right = NULL;
    return first_node_ptr;
}

// Recursively start at the root node and find the position to insert the next node.
// Non-balanced binary search tree.
void bst_insert(Node* node, long int key)
{
    Node *next = NULL;
    bool left;

    if ( key == node->key )  // Already in the tree
        return;
    else if ( key < node->key ) {  // Go LEFT
        next = node->left;
        left = true;
    } else {  // Go RIGHT
        next = node->right;
        left = false;
    }

    if ( next != NULL ) bst_insert(next, key);  // Traverse down the tree
    else {
        Node *new_node_ptr = (Node *) ec_malloc(sizeof(Node));
        new_node_ptr->key = key;
        new_node_ptr->left = new_node_ptr->right = NULL;
        new_node_ptr->height = 0;
        if ( left ) node->left = new_node_ptr;
        else node->right = new_node_ptr;
    }
}

// Traverse and sort the BST in-order
void in_order_sort(struct Node* tree)
{
    if ( tree != NULL ) {
        if ( tree->left != NULL ) in_order_sort(tree->left);
        if ( COUNTER != 0 && (COUNTER % 10) == 0 ) printf("\n");
        COUNTER++;
        printf("%5ld", tree->key);
        if ( tree->right != NULL ) in_order_sort(tree->right);
    }
}

/*void avl_insert(Node* tree, Node node)
{
    if ( tree == NULL ) {
        tree = (Node *) ec_malloc((sizeof(Node)) * 100);
        *tree = node;
    } else if ( node.key < tree->key ) {
        avl_insert(tree->left, node);

        if ( node.key < (tree->left)->key ) avl_rotate_right(node);  // rotate right
        else avl_double_rotate_right(node);  // rotate right and then left again
    } else if ( node.key > tree->key ) {
        avl_insert(tree->right, node);

        if ( (tree->right)->height - (tree->left)->height == 2 ) {
            if ( node.key < (tree->right)->key ) avl_double_rotate_left(node);
            else avl_rotate_left(node);
        }
    }

    tree->height = max((tree->left)->height, (tree->right)->height) + 1;

}*/


// void avl_rotate_right(Node node)
// {
//
// }
//
// void avl_rotate_left(Node node)
// {
//
// }
//
// void avl_double_rotate_right(Node node)
// {
//
// }
//
// void avl_double_rotate_left(Node node)
// {
//
// }

int max(int a, int b)
{
    return (a > b) ? a : b;
}
