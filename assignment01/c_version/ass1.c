/*********************************************************************
* CSCI203 - Assignment 1
* assignment01.c - main() driver for assignment 1 implementation
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.08.23
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define BUFFER_SZ 200
#define SIZE 50000
#define WORD_SZ 50
// #define IN 1  /* inside a word */
// #define OUT 0  /* outside a word */

/* Struct Definitions */
typedef struct Node {
    char key[33];
    struct Node *left, *right;
    int height;
} Node;

typedef struct {
  int start_idx;
  int length;
  int count;
} Word;

/* Global Vars */
char POOL[SIZE * 10];
Word WORDS[SIZE];
int next_char = 0;
int next_word = 0;

/* Function prototypes */

Word append_word(char * str);
char * preprocess_word(char * str);

// AVL Tree Prototypes
Node * insert(Node * node, char * key);
Node * rotate_right(Node * n2);
Node * rotate_left(Node * n2);
Node * double_rotate_right(Node * n3);
Node * double_rotate_left(Node * n3);
// Node* search();
void in_order_sort(Node * root);
void reverse_in_order_sort(Node * root);
int height(Node * n);
int get_balance(Node * n);
int max(int a, int b);
// int str_cmp(const char * str1, const char * str2);

// Helper Utility Funcs Prototypes
char * get_current_time();
void fatal(char *message);
void * ec_malloc(unsigned int size);


int main( int argc, const char* argv[] )
{
    printf("CSCI203 Assignment 01\nAuthor: Dinh Che (dbac496)\nRun at: %s\n", get_current_time());

    FILE *fd;
    char buffer[BUFFER_SZ], filename[BUFFER_SZ];

    // 1. Read the name of the text file from the console
    /* Implementation: if console params from console, read into filename.
     * else display a prompt for the file name and print to stdout file to open. */
    if ( argc == 2 )
        strcpy(filename, argv[1]);
    else {
        printf("Input file name: ");
        scanf("%s", buffer);
        strcpy(filename, buffer);
    }

    if ( (fd = fopen(filename, "r")) == NULL )  {
        fprintf(stderr, "[!!] Error: Failed to open file [ %s ]\nExit(1)...\n", strerror(1));
        exit(1);
    }

    int word_idx = 0;
    char new_str[WORD_SZ];
    // TODO:
    Node *word_tree;

    // 2. Read in a text file, not all at once. (This can be line by line, word by word, or char by char).
    while ( (fscanf(fd, "%s", new_str) ) == 1 ) {
        if ( ferror(fd) ) break;

        // 3. The file content must be converted to a sequence of words, discarding punctuation and
        // folding all letters into lower case
        // 4. Store the unique words and maintain a count of each different word.
        /* Implementation: */
        append_word(preprocess_word(new_str));  // TODO: Change the name of this function
        // TODO: Append the Word struct to an AVL Tree sorted by something
        // TODO: Also change the AVL Tree to increase the count of the word if the words are the same.

    }

    fclose(fd);

    // TODO: Testing String Pool and Word Struct Array
    /*for ( int i=0; i < strlen(POOL); i++ ) printf("%c", POOL[i]);
    printf("\n");
    for ( int m=0; m < next_word; m++ )
        printf("start: %d : length: %d \n", WORDS[m].start_idx, WORDS[m].length);

    for ( int j=0; j < next_word; j++ ) {
        int start = WORDS[j].start_idx;
        int end = (int) (((j + 1) < next_word) ? WORDS[j + 1].start_idx : strlen(POOL));
        int len = end - start;

        char * word = (char *) ec_malloc(sizeof(WORDS[j].length) + 1);
        for ( int k=0; k < len; k++ ) word[k] = POOL[start++];
        printf("start: %i end: %i len: %i\n", start, end, len);
        word[end] = '\0';
        printf("%s\n", word);
        free(word);
    }*/

    // 5. The words should be ordered by decreasing count and, if there are multiple words with the same count,
    // alphabetically. (This ordering may be achieved as the words are read in, partially as the words are read,
    // or at the end of all input processing.

    // 6. Output the first ten words in the sorted list, along with their counts.

    // 7. Output the last ten words in the list, along with their counts.

}

/* PRIVATE FUNCTIONS */

// Append each char from the passed string to the string pool and define/init a Word struct to store its
// positional index which is added to the global WORDS array and returned
Word append_word(char *str)
{
    Word new_word = { .start_idx = next_char, .count = 1, .length = 0 };
    while ( new_word.length < strlen(str) )
        POOL[next_char++] = str[new_word.length++];

    WORDS[next_word++] = new_word;
    return new_word;
}

// Pre-process the word removing all non-alphanumeric chars and returning the pointer to the processed char array.
char *preprocess_word(char * str)
{
    int i, j, n = (int) strlen(str);
    for ( i=0, j=0; i < n; i++ )
        if ( isalpha(str[i]) ) str[j++] = (char) tolower(str[i]);
    str[j] = '\0';
    return str;
}


/****************| AVL TREE IMPLEMENTATION |****************/
// Recursively insert a node into the tree and then fix it's balance by rotations
Node* insert(Node *node, char *key)
{
    if ( node == NULL ) {  // Root of tree OR at a NULL left or right pointer where node is meant to be
        Node *new_node = (Node *) ec_malloc(sizeof(Node));
        strcpy(new_node->key, key);
        new_node->left = new_node->right = NULL;
        new_node->height = 0;
        return new_node;
    } else if ( strncmp(key, node->key, 32) < 0 ) {  // Insert in the left side
        node->left = insert(node->left, key);
    } else if ( strncmp(key, node->key, 32) > 0 ) {  // Insert in the right side
        node->right = insert(node->right, key);
    }
    else  // Equal keys not allowed
        return node;

    // Update the height of the node
    node->height = 1 + max(height(node->left), height(node->right));

    // Checking the imbalance and balancing the BST.
    int balance = get_balance(node);

    /* CASE 1 - left left case */
    // key < (node->left)->key
    if ( balance > 1 && strncmp(key, (node->left)->key, 32) < 0 )
        return rotate_right(node);

    /* CASE 2 - right right case */
    // key > (node->right)->key
    if ( balance < -1 && strncmp(key, (node->right)->key, 32) > 0 )
        return rotate_left(node);

    /* CASE 3 - left right case */
    // key > (node->left)->key
    if ( balance > 1 && strncmp(key, (node->left)->key, 32) > 0 )
        return double_rotate_right(node);

    /* CASE 4 - right left case */
    // key < (node->key)->key
    if ( balance < -1 && strncmp(key, (node->right)->key, 32) < 0 )
        return double_rotate_left(node);

    return node;
}

Node* rotate_right(Node *n2)
{
    Node *n1 = n2->left;
    Node *t2 = n1->right;

    n1->right = n2;
    n2->left = t2;
    n2->height = 1 + max(height(n2->left), height(n2->right));
    n1->height = 1 + max(height(n1->left), height(n2));
    return n1;
}

Node* rotate_left(Node *n2)
{
    Node *n1 = n2->right;
    Node *t2 = n1->left;

    n1->left = n2;
    n2->right = t2;

    n2->height = 1 + max(height(n2->left), height(n2->right));
    n1->height = 1 + max(height(n2), height(n1->right));
    return n1;
}

Node* double_rotate_right(Node *n3)
{
    n3->left = rotate_left(n3->left);
    return rotate_right(n3);
}

Node* double_rotate_left(Node *n3)
{
    n3->right = rotate_right(n3->right);
    return rotate_left(n3);
}

// Traverse and sort the BST in-order
void in_order_sort(Node *root)
{
    if ( root != NULL ) {
        in_order_sort(root->left);
        printf("%s\n", root->key);
        in_order_sort(root->right);
    }
}

// Traverse and sort the BST with reverse in-order
void reverse_in_order_sort(Node *root)
{
    if ( root != NULL ) {
        in_order_sort(root->right);
        printf("%s\n", root->key);
        in_order_sort(root->left);
    }
}

// Traverse the tree to search for a node based on key
Node* search(Node *root, char *key)
{
    if ( root == NULL )
        return NULL;

    if ( strncmp(key, root->key, 32) == 0 )
        return root;

    if ( strncmp(key, root->key, 32 ) < 0 )
        return search(root->left, key );
    else
        return search(root->right, key);
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

// Get the max between values a and b
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/****************| HELPER UTILITY FUNC IMPLEMENTATION |****************/

// A function to return the current time
/* Title: localtime reference
 * Author(s):
 * Date:
 * Availability: http://www.cplusplus.com/reference/ctime/localtime/
 * */
char * get_current_time()
{
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return asctime(timeinfo);
}

// A function to display an error message and then exit
void fatal(char * message)
{
    char error_message[200];

    strcpy(error_message, "[!!] Fatal Error: ");
    strncat(error_message, message, 83);
    perror(error_message);
    exit(-1);
}

// An error-checked malloc() wrapper function
void * ec_malloc(unsigned int size)
{
    void *ptr;
    ptr = malloc(size);
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}
