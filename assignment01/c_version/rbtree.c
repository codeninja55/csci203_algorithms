//
// Created by codeninja on 27/08/18.
//

#include <stddef.h>
#include <stdlib.h>
#include <malloc.h>
#include "rbtree.h"


/****************| RED BLACK TREE IMPLEMENTATION |****************/

int compare_keys(Word *w1, Word *w2)
{
    if ( w1->count < w2->count ) {
        return -1;
    } else if ( w1->count > w2->count ) {
        return 1;
    } else {
        return word_str_cmp(w1, w2);
    }
}

// A utility function to insert a new node with given key in BST
RBNode * bst_insert(RBNode * root, RBNode * ptr)
{
    if ( root == NULL )
        return ptr;

    // Otherwise, recur down the tree
    if ( word_str_cmp(&WORDS[ptr->key], &WORDS[root->key]) < 0 ) {
        root->left = bst_insert(root->left, ptr);
        root->left->parent = root;
    } else if ( word_str_cmp(&WORDS[ptr->key], &WORDS[root->key]) > 0 ) {
        root->right = bst_insert(root->right, ptr);
        root->right->parent = root;
    }

    // return the (unchanged) node pointer
    return root;
}


RBNode *rb_insert(RBNode *rb_root, int key)
{
    RBNode *ptr = ec_malloc(sizeof(RBNode));
    ptr->key = key;
    ptr->parent = ptr->right = ptr->left = NULL;

    // Do normal BST insert
    rb_root = bst_insert(rb_root, ptr);

    // fix Red Black Tree violations
    fix_violations(rb_root, ptr);

    return rb_root;
}

void rb_rotate_left(RBNode *root, RBNode *ptr)
{
    RBNode *ptr_right = ptr->right;
    ptr->right = ptr_right->left;

    if ( ptr->right != NULL )
        ptr->right->parent = ptr;

    ptr_right->parent = ptr->parent;

    if ( ptr->parent == NULL )
        root = ptr_right;
    else if ( ptr == ptr->parent->left )
        ptr->parent->left = ptr_right;
    else
        ptr->parent->right = ptr_right;

    ptr_right->left = ptr;
    ptr->parent = ptr_right;
}

void rb_rotate_right(RBNode *root, RBNode *ptr)
{
    RBNode *ptr_left = ptr->left;
    ptr->left = ptr_left->right;

    if ( ptr->left != NULL )
        ptr->left->parent = ptr;

    ptr_left->parent = ptr->parent;

    if ( ptr->parent == NULL )
        root = ptr_left;
    else if ( ptr == ptr->parent->left )
        ptr->parent->left = ptr_left;
    else
        ptr->parent->right = ptr_left;

    ptr_left->right = ptr;
    ptr->parent = ptr_left;
}

void fix_violations(RBNode *root, RBNode *ptr)
{
    RBNode *parent_ptr = NULL;
    RBNode *grand_parent_ptr = NULL;

    while ( (ptr != root ) && (ptr->color != BLACK) && ptr->parent->color == RED) {
        parent_ptr = ptr->parent;
        grand_parent_ptr = ptr->parent->parent;

        /* Case A : Parent of ptr is left child of grand-parent of ptr */
        if ( parent_ptr == grand_parent_ptr->left ) {
            RBNode *uncle_ptr = grand_parent_ptr->right;

            /* Case 1 : the uncle of ptr is also red. Only recolouring require. */
            if ( uncle_ptr != NULL && uncle_ptr->color == RED ) {
                grand_parent_ptr->color = RED;
                parent_ptr->color = BLACK;
                uncle_ptr->color = BLACK;
                ptr = grand_parent_ptr;
            } else {
                /* Case 2 : ptr is a right child of its parent. Left-rotation required. */
                if ( ptr == parent_ptr->right ) {
                    rb_rotate_left(root, parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }

                /* Case 3: ptr is a left child of its parent. Right-rotation required. */
                rb_rotate_right(root, grand_parent_ptr);
                bool_swap(parent_ptr->color, grand_parent_ptr->color);
                ptr = parent_ptr;
            }
        }
            /* Case B: Parent of ptr is right child of grand-parent of ptr. */
        else {
            RBNode *uncle_ptr = grand_parent_ptr->left;
            /* Case 1: the uncle of ptr is also red. Only recolouring required. */
            if ( (uncle_ptr != NULL) && (uncle_ptr->color == RED) ) {
                grand_parent_ptr->color = RED;
                parent_ptr->color = BLACK;
                uncle_ptr->color = BLACK;
                ptr = grand_parent_ptr;
            } else {
                /* Case 2: ptr is left child of its parent. Right rotation required. */
                if ( ptr == parent_ptr->left ) {
                    rb_rotate_right(root, parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }

                /* Case 3: ptr is right child of its parent. Left-rotation required. */
                rb_rotate_left(root, grand_parent_ptr);
                bool_swap(parent_ptr->color, grand_parent_ptr->color);
                ptr = parent_ptr;
            }
        }
    }
    root->color = BLACK;
}

void rb_in_order(RBNode *root)
{
    if ( root == NULL ) return;

    rb_in_order(root->left);
    printf("%d (%s)\n", root->key, root->color == BLACK ? "black" : "red");
    rb_in_order(root->right);
}

void bool_swap(bool color, bool color1)
{
    bool temp = color;
    color = color1;
    color1 = temp;
}

