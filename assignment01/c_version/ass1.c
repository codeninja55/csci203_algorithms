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
#include <assert.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type"
#define BUFFER_SZ 200
#define SIZE 10000
#define WORD_SZ 15

/* Struct Definitions */
typedef struct {
    int start_idx;
    int length;
    int count;
} Word;

typedef struct Node {
    char key[WORD_SZ];
    Word *word;
    struct Node *left, *right;
    int height;
} Node;

/* Global Vars */
char POOL[SIZE * WORD_SZ];
int NEXT_CHAR = 0;
Word WORDS[SIZE];
int WORDS_CTR = 0;
Node *WORD_TREE = NULL;

/* Function prototypes */
char * preprocess_word(char * str);

// QuickSort Prototypes
void quicksort(Word arr[], int low, int high);
int partition(Word arr[], int low, int high);

// AVL Tree Prototypes
Node * insert(Node * node, Word *word, char * key);
Node * rotate_right(Node * n2);
Node * rotate_left(Node * n2);
Node * double_rotate_right(Node * n3);
Node * double_rotate_left(Node * n3);
Node * search(Node *root, char *key);
void in_order_sort(Node * root);
void reverse_in_order_sort(Node * root);
int height(Node * n);
int get_balance(Node * n);
int max(int a, int b);

// Helper Utility Funcs Prototypes
int str_cmp (const char *str1, const char *str2);
void swap(Word *v1, Word *v2);
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

    // int word_idx = 0;
    char new_str[WORD_SZ];

    // 2. Read in a text file, not all at once. (This can be line by line, word by word, or char by char).
    /* Implementation: */
    while ( fscanf(fd, "%s", new_str) == 1 ) {
        if (ferror(fd)) break;

        // 3. The file content must be converted to a sequence of words, discarding punctuation and
        // folding all letters into lower case
        char *new_word = preprocess_word(new_str);

        // 4. Store the unique words and maintain a count of each different word.
        /* Implementation: */

        /*Word *word_struct_ptr = (Word *) ec_malloc(sizeof(Word));
        word_struct_ptr->start_idx = NEXT_CHAR;
        word_struct_ptr->count = 1;
        word_struct_ptr->length = 0;

        while ( word_struct_ptr->length < strlen(new_word) )
            POOL[NEXT_CHAR++] = new_word[word_struct_ptr->length++];*/
        Node *ret = search(WORD_TREE, new_word);
        if ( ret != NULL ) {
            ret->word->count++;
        } else {
            Word word_struct = {.start_idx = NEXT_CHAR, .count = 1, .length = 0};
            while (word_struct.length < strlen(new_word))
                POOL[NEXT_CHAR++] = new_word[word_struct.length++];

            WORDS[WORDS_CTR] = word_struct;
            WORD_TREE = insert(WORD_TREE, &WORDS[WORDS_CTR], new_word);
            WORDS_CTR++;
        }
    }

    fclose(fd);

    printf("BINARY TREE SORT word_tree\n");
    in_order_sort(WORD_TREE);
    printf("\n");
    // reverse_in_order_sort(word_tree);

    int n = WORDS_CTR - 1;
    // printf("WORDS[] before Sort \n");
    // for (int l=0; l < n; l ++ ) printf("%d ", WORDS[l].start_idx);
    quicksort(WORDS, 0, n);
    // printf("\nQUICKSORT WORDS[] \n");
    /*for ( int j=0; j < n; j++ ) {
        printf("%d [ %d ] : ", WORDS[j].start_idx, WORDS[j].count);
        for ( int k=0; k < WORDS[j].length; k++ ) printf("%c", POOL[(WORDS[j].start_idx)++]);
        printf("\n");
    }*/

    // TODO: Testing String Pool and Word Struct Array
    // for ( int i=0; i < strlen(POOL); i++ ) printf("%c", POOL[i]);
    // printf("\n");
    // for ( int m=0; m < next_word; m++ )
    //     printf("start: %d : length: %d \n", WORDS[m].start_idx, WORDS[m].length);

    printf("\nTOP 10 WORDS[] \n");
    for ( int m=n; m > (n - 10); m-- ) {
        printf("%d [ %d ] : ", WORDS[m].start_idx, WORDS[m].count);
        for ( int k=0; k < WORDS[m].length; k++ ) printf("%c", POOL[(WORDS[m].start_idx)++]);
        printf("\n");
    }

    printf("\nBOTTOM 10 WORDS[] \n");
    for ( int n=0; n < 10; n++ ) {
        printf("%d [ %d ] : ", WORDS[n].start_idx, WORDS[n].count);
        for ( int k=0; k < WORDS[n].length; k++ ) printf("%c", POOL[(WORDS[n].start_idx)++]);
        printf("\n");
    }
}

/* PRIVATE FUNCTIONS */
/* Pre-process the word removing all non-alphanumeric chars and returning the pointer to the processed char array. */
char *preprocess_word(char * str)
{
    int i, j, n = (int) strlen(str);
    for ( i=0, j=0; i < n; i++ )
        if ( isalpha(str[i]) ) str[j++] = (char) tolower(str[i]);
    str[j] = '\0';
    return str;
}

/****************| QUICKSORT IMPLEMENTATION |****************/
/* The main function that implements quicksort
 * arr[] --> array to be sorted.
 * low --> starting index.
 * high --> ending index.
 * */
void quicksort(Word arr[], int low, int high)
{
    if ( low < high ) {
        // Partitioning index, arr[p] is now at the right place
        int partition_idx = partition(arr, low, high);

        quicksort(arr, low, partition_idx - 1);  // Before partition_idx
        quicksort(arr, partition_idx + 1, high);  // After partition_idx
    }
}

/* This function takes last element as pivot, places the pivot element at its correct
 * position in sorted array, and places all smaller (smaller than pivot) to left of
 * pivot and all greater elements to right of pivot
 * */
int partition(Word arr[], int low, int high)
{
    // pivot (element to be placed at right position)
    int pivot = arr[high].count;

    int i = (low - 1);  // Index of smaller element

    for ( int j = low; j <= high - 1; j++ ) {
        // If the current element is smaller than or equal to pivot
        if ( arr[j].count <= pivot ) {
            i++;
            swap(&arr[i], &arr[j]);  // increment index of smaller element ++i
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


/****************| AVL TREE IMPLEMENTATION |****************/
// Recursively insert a node into the tree and then fix it's balance by rotations
Node* insert(Node *node, Word *word, char *key)
{
    if ( node == NULL ) {  // Root of tree OR at a NULL left or right pointer where node is meant to be
        Node *new_node = (Node *) ec_malloc(sizeof(Node));
        strcpy(new_node->key, key);
        new_node->word = word;
        new_node->left = new_node->right = NULL;
        new_node->height = 0;
        return new_node;
    } else if ( strcmp(key, node->key) == 0 )
        return node;
    else if ( strcmp(key, node->key) < 0 )  // Insert in the left side
        node->left = insert(node->left, word, key);
    else if ( strcmp(key, node->key) > 0 )  // Insert in the right side
        node->right = insert(node->right, word, key);

    // Update the height of the node
    node->height = 1 + max(height(node->left), height(node->right));

    // Checking the imbalance and balancing the BST.
    int balance = get_balance(node);

    /* CASE 1 - left left case */
    // key < (node->left)->key
    if ( balance > 1 && strcmp(key, (node->left)->key) < 0 )
        return rotate_right(node);

    /* CASE 2 - right right case */
    // key > (node->right)->key
    if ( balance < -1 && strcmp(key, (node->right)->key) > 0 )
        return rotate_left(node);

    /* CASE 3 - left right case */
    // key > (node->left)->key
    if ( balance > 1 && strcmp(key, (node->left)->key) > 0 )
        return double_rotate_right(node);

    /* CASE 4 - right left case */
    // key < (node->key)->key
    if ( balance < -1 && strcmp(key, (node->right)->key) < 0 )
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
        printf("%s [ %d ]\n", root->key, root->word->count);
        in_order_sort(root->right);
    }
}

// Traverse and sort the BST with reverse in-order
/*void reverse_in_order_sort(Node *root)
{
    if ( root != NULL ) {
        in_order_sort(root->right);
        printf("%s [ %d ]\n", root->key, root->word->count);
        in_order_sort(root->left);
    }
}*/

// Traverse the tree to search for a node based on key
Node *search(Node *root, char *key)
{
    if ( root == NULL )
        return NULL;

    if ( str_cmp(key, root->key) == 0 )
        return root;

    if ( str_cmp(key, root->key) < 0 )
        search(root->left, key );
    else
        search(root->right, key);
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
// Custom strcmp method using pointers
int str_cmp (const char *str1, const char *str2)
{
    while ( *str1 || *str2 ) {
        if ( *str1 != *str2 ) return *str1 - *str2;
        ++str1;
        ++str2;
    }
    return 0;
}

// Swap the Word struct
void swap(Word *v1, Word *v2)
{
    Word temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

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

#pragma clang diagnostic pop