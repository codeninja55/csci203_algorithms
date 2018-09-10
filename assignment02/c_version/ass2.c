/*********************************************************************
* CSCI203 - Assignment 02
* ass2.c - main() driver for implementation of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.20
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <helper.h>

#define BUFFER_SZ 50

int main(int argc, const char * argv[])
{
    printf("|==========| CSCI203 Assignment 02 |==========|\n"
           "Author: Dinh Che (dbac496)\nRun at: %s", get_current_time());
    FILE *fd;
    char buffer[BUFFER_SZ];
    char filename[] = "sample.txt";

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("[!!] Error: Failed to open file\nExit(1)...\n");
        return -1;
    }

    char *ptr;
    long prim_servers, sec_servers;
    // Read number of primary servers
    fscanf(fd, "%s", buffer);
    prim_servers = strtol(buffer, &ptr, 10);

    // Read number of secondary servers
    fscanf(fd, "%s", buffer);
    sec_servers = strtol(buffer, &ptr, 10);

    // Read event data till EOF
    char buf1[15], buf2[15], buf3[15];
    double arrival_time, prim_service_time, sec_service_time;
    while (fscanf(fd, "%s %s %s", buf1, buf2, buf3) == 3) {
        // Convert buffer strings to double
        arrival_time = strtod(buf1, &ptr);
        prim_service_time = strtod(buf2, &ptr);
        sec_service_time = strtod(buf3, &ptr);

        printf("%.9lf %.9lf %.9lf \n", arrival_time, prim_service_time, sec_service_time);
    }
    fclose(fd);
}
