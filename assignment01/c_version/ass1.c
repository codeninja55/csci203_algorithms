/*********************************************************************
* CSCI203 - Assignment 1
* ass1.c - main() driver and data structures for assignment 1 implementation
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.08.27
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )
#define MIN(a,b) ( ((a) < (b)) ? (a) : (b) )
#define BUFFER_SZ 200
#define SIZE 10000
#define WORD_SZ 15

/* Struct Definitions */
typedef struct {
    int start_idx, length, count;
} Word;

typedef struct Node {
    int key, height;
    struct Node *left, *right;
} Node;

/* Global Vars */
char POOL[SIZE * WORD_SZ];  // compactly stores chars from each word
int NEXT_CHAR = 0;  // next index to put the word
Word WORDS[SIZE];  // Array to store the word structs
int WORDS_CTR = 0;  // N counter for the WORDS[] array
Node *WORD_TREE = NULL;  // Root of AVL Tree to store read in words for unique values

/* Function prototypes */
char * preprocess_word(char * str);

// QuickSort Prototypes
void quicksort(Word words[], int low, int high);
int partition(Word words[], int left, int right);
int compare(Word *w1, Word *w2);

// AVL Tree Prototypes
Node * insert(Node * node, int key);
Node * rotate_right(Node * n2);
Node * rotate_left(Node * n2);
Node * double_rotate_right(Node * n3);
Node * double_rotate_left(Node * n3);
Node * search(Node * root, char * word);
void in_order_sort(Node * root);
int height(Node * n);
int get_balance(Node * n);

// Helper Utility Funcs Prototypes
int str_cmp(const Word * str1, const char * str2);
int word_str_cmp(const Word * str1, const Word * str2);
void swap(Word * v1, Word * v2);
char * get_current_time();
void fatal(char *message);
void * ec_malloc(unsigned int size);


int main( int argc, const char* argv[] )
{
    printf("|==========| CSCI203 Assignment 01 |==========|\n"
           "Author: Dinh Che (dbac496)\nRun at: %s", get_current_time());
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
        if ( strlen(buffer) < BUFFER_SZ ) strcpy(filename, buffer);
    }

    if ( (fd = fopen(filename, "r")) == NULL )  {
        fprintf(stderr, "[!!] Error: Failed to open file [ %s ]\nExit(1)...\n", strerror(1));
        exit(1);
    }

    char new_str[WORD_SZ];
    // 2. Read in a text file, not all at once. (This can be line by line, word by word, or char by char).
    /* Implementation: */
    while ( fscanf(fd, "%s", new_str) == 1 ) {
        if ( ferror(fd) ) break;
        // 3. The file content must be converted to a sequence of words, discarding punctuation and
        // folding all letters into lower case
        char *new_word = preprocess_word(new_str);
        // 4. Store the unique words and maintain a count of each different word.
        /* Implementation: Search the WORD_TREE AVL tree for the unique store of the word as key. If the word is
         * already in the tree, increase the count. If it is not, then create a new Word struct, word_struct.
         * Add the new_word char array to the string pool, and add the word_struct to the WORDS[] array.
         * Insert the new word into the AVL tree with the key as the index to the word_struct position in the array. */

        Node *found = search(WORD_TREE, new_word);
        if ( found != NULL ) {
            WORDS[found->key].count += 1;
        } else {
            Word word_struct = { .start_idx = NEXT_CHAR, .count = 1, .length = 0 };
            while ( word_struct.length < strlen(new_word) )
                POOL[NEXT_CHAR++] = new_word[word_struct.length++];

            WORDS[WORDS_CTR] = word_struct;
            WORD_TREE = insert(WORD_TREE, WORDS_CTR);
            WORDS_CTR++;
        }
    }
    fclose(fd);

    // Get the N of WORDS[]
    int n = WORDS_CTR - 1;

    // Quicksort WORDS[] to be in count and alphabetical order.
    quicksort(WORDS, 0, n);

    // Print the output
    printf("\n|===============| OUTPUT |===============|\n");

    // 6. Output the first ten words in the sorted list, along with their counts.
    printf("\n     FIRST 10 WORDS \n");
    printf("-------|-------|--------\n");
    printf(" %5s | %-4s | %-6s \n", "Index", "Count", "Word");
    printf("-------|-------|--------\n");
    for ( int o=0; o < 10; o++ ) {
        printf(" %5d | %-5d | ", WORDS[o].start_idx, WORDS[o].count);
        for ( int k=0; k < WORDS[o].length; k++ ) printf("%c", POOL[(WORDS[o].start_idx) + k]);
        printf("\n");
    }
    printf("-------|-------|--------\n");

    // 7. Output the last ten words in the list, along with their counts.
    printf("\n     LAST 10 WORDS \n");
    printf("-------|-------|--------\n");
    printf(" %5s | %-4s | %-6s \n", "Index", "Count", "Word");
    printf("-------|-------|--------\n");
    for ( int m=n; m > (n - 10); m-- ) {
        printf(" %5d | %-5d | ", WORDS[m].start_idx, WORDS[m].count);
        for ( int k=0; k < WORDS[m].length; k++ ) printf("%1c", POOL[(WORDS[m].start_idx)++]);
        printf(" \n");
    }
    printf("-------|-------|--------\n");
    printf("|===============| END OF ASSIGNMENT 01 |===============|\n");
}

/* PRIVATE FUNCTIONS */
/* Pre-process the word removing all non-alphanumeric chars and returning the pointer
 * to the processed char array. */
char *preprocess_word(char * str)
{
    int i, j, n = (int) strlen(str);
    for ( i=0, j=0; i < n; i++ )
        if ( isalpha(str[i]) )
            str[j++] = (char) tolower(str[i]);
    str[j] = '\0';
    return str;
}

/****************| QUICKSORT IMPLEMENTATION |****************/
// The main function that implements quicksort by partitioning first and then sorting before and after partition.
void quicksort(Word words[], int low, int high)
{
    if ( low < high ) {
        // Partitioning index is now at the right place
        int partition_idx = partition(words, low, high);

        quicksort(words, low, partition_idx - 1);  // Before partition_idx
        quicksort(words, partition_idx + 1, high);  // After partition_idx
    }
}

/* This function takes last element as pivot, places the pivot element at its correct
 * position in sorted array, and places all smaller (smaller than pivot) to left of
 * pivot and all greater elements to right of pivot
 * */
int partition(Word words[], int left, int right)
{
    Word *pivot = &words[right];  // pivot (element to be placed at right position)

    int i = (left - 1);  // Index of smaller element

    for ( int j = left; j <= right - 1; j++ ) {
        // If the current element is smaller than or equal to pivot
        if ( compare(&words[j], pivot) >= 0 ) {
            i++; // increment index of smaller element ++i
            swap(&words[i], &words[j]);  // swap the elements
        }
    }
    swap(&words[i + 1], &words[right]);
    return (i + 1);
}

// This utility function will compare the two param Words by count first and then alphabetical order.
int compare(Word *w1, Word *w2)
{
    if ( w1->count < w2->count )
        return -1;
    else if ( w1->count > w2->count )
        return 1;
    else
        return word_str_cmp(w1, w2);
}

/****************| AVL TREE IMPLEMENTATION |****************/
// Traverse the tree to do binary search for a node based on words from WORDS[] struct array and POOL[] char array.
Node *search(Node *root, char *word)
{
    if ( root == NULL )
        return NULL;

    if ( str_cmp(&WORDS[root->key], word) == 0 )
        return root;
    else if ( str_cmp(&WORDS[root->key], word) < 0 )
        search(root->left, word);
    else
        search(root->right, word);
}

// Recursively insert a node into the tree and then fix it's balance by rotations
Node *insert(Node *node, int key)
{
    if ( node == NULL ) {  // Root of tree OR at a NULL left or right pointer where node is meant to be
        // Dynamic memory to put Node struct on the heap must be used to avoid going out of scope
        Node *new_node = (Node *) ec_malloc(sizeof(Node));
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        new_node->height = 0;
        return new_node;
    }

    if ( word_str_cmp(&WORDS[key], &WORDS[node->key]) == 0 )  // Duplicate keys not allowed
        return node;
    else if ( word_str_cmp(&WORDS[key], &WORDS[node->key]) < 0 )  // Insert in the left side
        node->left = insert(node->left, key);
    else if ( word_str_cmp(&WORDS[key], &WORDS[node->key]) > 0 )  // Insert in the right side
        node->right = insert(node->right, key);

    // Update the height of the node
    node->height = 1 + MAX(height(node->left), height(node->right));

    // Checking the imbalance and balancing the BST.
    int balance = get_balance(node);

    /* CASE 1 - left left case */
    // key < (node->left)->key
    if ( balance > 1 && word_str_cmp(&WORDS[key], &WORDS[(node->left)->key]) < 0 )
        return rotate_right(node);

    /* CASE 2 - right right case */
    // key > (node->right)->key
    if ( balance < -1 && word_str_cmp(&WORDS[key], &WORDS[(node->right)->key]) > 0 )
        return rotate_left(node);

    /* CASE 3 - left right case */
    // key > (node->left)->key
    if ( balance > 1 && word_str_cmp(&WORDS[key], &WORDS[(node->left)->key]) > 0 )
        return double_rotate_right(node);

    /* CASE 4 - right left case */
    // key < (node->key)->key
    if ( balance < -1 && word_str_cmp(&WORDS[key], &WORDS[(node->right)->key]) < 0 )
        return double_rotate_left(node);

    return node;
}

Node* rotate_right(Node *n2)
{
    Node *n1 = n2->left;
    Node *t2 = n1->right;

    n1->right = n2;
    n2->left = t2;
    n2->height = 1 + MAX(height(n2->left), height(n2->right));
    n1->height = 1 + MAX(height(n1->left), height(n2));
    return n1;
}

Node* rotate_left(Node *n2)
{
    Node *n1 = n2->right;
    Node *t2 = n1->left;

    n1->left = n2;
    n2->right = t2;

    n2->height = 1 + MAX(height(n2->left), height(n2->right));
    n1->height = 1 + MAX(height(n2), height(n1->right));
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
        printf("key: %d start: %d [ %d ] : ", root->key, WORDS[root->key].start_idx, WORDS[root->key].count);
        for (int i=0; i < WORDS[root->key].length; i++ ) printf("%c", POOL[WORDS[root->key].start_idx + i]);
        printf("\n");
        in_order_sort(root->right);
    }
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

/****************| HELPER UTILITY FUNC IMPLEMENTATION |****************/
// Custom strcmp comparing a cstring char array to a string stored in the string pool.
int str_cmp(const Word *str1, const char *str2)
{
    for ( int i=0; i < MIN(str1->length, (int) strlen(str2)); i++ ) {
        if ( POOL[str1->start_idx + i] < str2[i] )
            return 1;
        if ( POOL[str1->start_idx + i] > str2[i] )
            return -1;
    }

    if ( str1->length < strlen(str2) )
        return 1;
    if ( str1->length > strlen(str2) )
        return -1;

    return 0;
}

// Custom strcmp method using Word structs
int word_str_cmp(const Word *str1, const Word *str2)
{
    // Only compare as many characters as the length of the shortest word
    for ( int i=0; i < MIN(str1->length, str2->length); i++ ) {
        if ( POOL[str1->start_idx + i] < POOL[str2->start_idx + i] )
            return -1;
        if ( POOL[str1->start_idx + i] > POOL[str2->start_idx + i] )
            return 1;
    }

    // the substrings we have compared so far are equal so the shorter of the two words is smaller
    if ( str1->length < str2->length )
        return -1;
    if ( str1->length > str2->length )
        return 1;

    // Otherwise the words are the same and return 0
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
char *get_current_time()
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
void *ec_malloc(unsigned int size)
{
    void *ptr;
    ptr = malloc(size);
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}
