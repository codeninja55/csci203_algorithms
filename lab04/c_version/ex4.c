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
Node* avl_insert(Node*, long int);
Node* avl_rotate_right(Node*);
Node* avl_rotate_left(Node*);
Node* avl_double_rotate_right(Node*);
Node* avl_double_rotate_left(Node*);
int height(Node*);
int get_balance(Node*);
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
    Node *AVL_ROOT = NULL;
    // AVL_ROOT = (Node *) ec_malloc(sizeof(Node));
    long int key;

    while ( fscanf(fd, "%li\n", &key) == 1 ) {
        // printf("[DEBUG]: Read: [ %li ]\n", key);
        // if ( ROOT == NULL ) ROOT = bst_insert_first(key);
        // else bst_insert(ROOT, key);
        AVL_ROOT = avl_insert(AVL_ROOT, key);
    }

    fclose(fd);
    // in_order_sort(ROOT);
    in_order_sort(AVL_ROOT);
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

Node* avl_insert(Node* node, long int key)
{
    if ( node == NULL ) {
        Node *new_node = (Node *) ec_malloc(sizeof(Node));
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        new_node->height = 0;
        return new_node;
    } else if ( key < node->key ) {
        node->left = avl_insert(node->left, key);
    } else if ( key > node->key ) {
        node->right = avl_insert(node->right, key);
    } else return node;  // Equal keys not allowed

    // tree->height = 1 + max((tree->left)->height, (tree->right)->height);
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    // Checking the imbalance and balancing the BST.
    /* CASE 1 - left left case */
    if ( balance > 1 && key < (node->left)->key )
        return avl_rotate_right(node);

    /* CASE 2 - right right case */
    if ( balance < -1 && key > (node->right)->key )
        return avl_rotate_left(node);

    /* CASE 3 - left right case */
    if ( balance > 1 && key > (node->left)->key )
        return avl_double_rotate_right(node);

    /* CASE 4 - right left case */
    if ( balance < -1 && key < (node->right)->key )
        return avl_double_rotate_left(node);

    return node;
}


Node* avl_rotate_right(Node* n2)
{
    Node *n1 = n2->left;
    Node *t2 = n1->right;

    n1->right = n2;
    n2->left = t2;
    n2->height = 1 + max(height(n2->left), height(n2->right));
    n1->height = 1 + max(height(n1->left), height(n2));
    return n1;
}

Node* avl_rotate_left(Node* n2)
{
    Node *n1 = n2->right;
    Node *t2 = n1->left;

    n1->left = n2;
    n2->right = t2;

    n2->height = 1 + max(height(n2->left), height(n2->right));
    n1->height = 1 + max(height(n2), height(n1->right));
    return n1;
}

Node* avl_double_rotate_right(Node* n3)
{
    n3->left = avl_rotate_left(n3->left);
    return avl_rotate_right(n3);
}

Node* avl_double_rotate_left(Node* n3)
{
    n3->right = avl_rotate_right(n3->right);
    return avl_rotate_left(n3);
}

/* HELPER FUNCTIONS */

// A helper function to get the height of the tree
int height(Node *n)
{
    return (n == NULL) ? 0 : n->height;
}

// Get Balance factor of node N
int get_balance(Node *n)
{
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
