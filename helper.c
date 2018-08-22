/*********************************************************************
 * helper.c - helper file with functions that are reused throughout
 * Dinh Che | dbac496 | Last modified 2018.07.31
 * Author: codeninja55
 *********************************************************************/

#include <helper.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "helper.h"

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
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}
