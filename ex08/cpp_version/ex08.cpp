/*********************************************************************************
* CSCI203 (Spring 2018) - Exercise 08
* Exercise 08 - ex08.cpp
* Purpose:
*
* @version 1.0
* @date 2018.10.06
*
* @authors Dinh Che (codeninja55) <andrew at codeninja55.me>
*********************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "HashMap.cpp"
using namespace std;

#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )
#define BUFFER_SZ 100
#define CARD_SZ 52

typedef struct Card {
  char *rank{};
  char suit{};

  bool operator< ( )
} Card;

int crazy_up();
void fatal(char *message);
void * ec_malloc(unsigned int size);

Card CARDS[CARD_SZ];
int CTR = 0;

int main(int argc, const char * argv[])
{
    cout << "|==========| CSCI203 Exercise 08 |==========|\nAuthor: Dinh Che (dbac496)\n\n";
    ifstream fin;
    char filename[BUFFER_SZ];

    if (argc == 2)
        strncpy(filename, argv[1], BUFFER_SZ);
    else {
        cout << "Input file name >> ";
        cin.getline(filename, BUFFER_SZ);
    }

    fin.open(filename);
    if(!fin.good()) {
        cout << "[!!] Error: Failed to open file: " << filename << "\nExiting...\n";
        return -1;
    }

    while (!fin.eof()) {
        char tmp[3];
        Card c;
        fin >> tmp;

        if (strlen(tmp) == 3) {
            c.rank = (char *)ec_malloc(sizeof("10"));
            strcpy(c.rank, "10");
            c.suit = tmp[2];
        } else {
            c.rank = (char *)ec_malloc(sizeof(char));
            *c.rank = tmp[0];
            c.suit = tmp[1];
        }
        CARDS[CTR++] = c;
    }

    cout << "N cards: " << CTR - 1 << "\n";
    cout << "Max Length: " << crazy_up() << endl;
}

int crazy_up()
{
    int length[CTR];
    length[0] = 0;
    int max_length, first_node, last_node;
    max_length = first_node = last_node = 0;

    for (int i = 1; i < CTR; i++) {
        int len = 1;

        for (int j = i-1; j >= 0; j--) {
            if (*CARDS[i].rank == *CARDS[j].rank || CARDS[i].suit == CARDS[j].suit ||
                *CARDS[i].rank == '8' || *CARDS[j].rank == '8') {
                len = MAX(len, length[j] + 1);
            }
            if (len == max_length)
                first_node = j;

        }
        length[i] = len;
        if (max_length != MAX(len, max_length)) {
            last_node = i;
            max_length = MAX(len, max_length);
        } else
            max_length = MAX(max_length, len);
    }

    cout << "First Node: " << CARDS[first_node].rank << CARDS[first_node].suit << endl;
    cout << "Last Node: " << CARDS[last_node].rank << CARDS[last_node].suit << endl;
    return max_length;
}

// A function to display an error message and then exit
void fatal(char * message)
{
    char error_message[200];

    strcpy(error_message, "[!!] Fatal Error ");
    strncat(error_message, message, 83);
    perror(error_message);
    exit(-1);
}

// An error-checked malloc() wrapper function
void * ec_malloc(unsigned int size)
{
    void *ptr;
    ptr = malloc(size);
    if(ptr == nullptr)
        fatal(const_cast<char*>("in ec_malloc() on memory allocation"));
    return ptr;
}