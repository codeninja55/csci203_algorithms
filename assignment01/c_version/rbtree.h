//
// Created by codeninja on 27/08/18.
//

#ifndef ASSIGNMENT01_C_VERSION_RBTREE_H
#define ASSIGNMENT01_C_VERSION_RBTREE_H

#include <stdbool.h>
#include <stdlib.h>

enum Color {RED, BLACK};

typedef struct RBNode {
    int key;
    bool color;
    struct RBNode *left, *right, *parent;
} RBNode;

// Red Black Tree Prototypes
// int compare_keys(Word *w1, Word *w2);
RBNode * bst_insert(RBNode * root, RBNode * ptr);
RBNode * rb_insert(RBNode *rb_root, int key);
void rb_in_order(RBNode *root);
void rb_rotate_left(RBNode *root, RBNode *ptr);
void rb_rotate_right(RBNode *root, RBNode *ptr);
void fix_violations(RBNode *root, RBNode *ptr);
void bool_swap(bool color, bool color1);

#endif //ASSIGNMENT01_C_VERSION_RBTREE_H
