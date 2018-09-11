/*********************************************************************
* CSCI203 - Assignment 02
* ass2.cpp - C++ main() driver for implementation of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.11
*********************************************************************/

#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*====================| MACRO DEFINITIONS |====================*/
#define Time double
#define BUFFER_SZ 50
#define PARENT(i) ( (i-1) / 2 )
#define LEFT(i) ( (i * 2) + 1 )
#define RIGHT(i) ( (i * 2) + 2 )
#define QUEUE_SZ 1000

int main(int argc, const char* argv[])
{
    char buffer[BUFFER_SZ], filename[BUFFER_SZ];
    ifstream fin;

    if (argc == 2)  // arg passed
        strncpy(filename, argv[1], BUFFER_SZ);
    else {
        cout << "Input file name >> ";
        cin.getline(filename, BUFFER_SZ);
    }

    fin.open(filename);

    if (!fin.good()) {
        cout << "[!!] Error: Failed to open file " << filename << "\nExiting...\n";
        return -1;
    }

    long prim_servers, sec_servers;
    fin >> prim_servers >> sec_servers;
    cout << prim_servers << " " << sec_servers;



    return 0;
}

