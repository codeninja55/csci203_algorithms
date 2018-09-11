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
#include <stdbool.h>
#include <time.h>

/*====================| MACRO DEFINITIONS |====================*/
#define Time double
#define BUFFER_SZ 50
#define PARENT(i) ( (i-1) / 2 )
#define LEFT(i) ( (i * 2) + 1 )
#define RIGHT(i) ( (i * 2) + 2 )
#define QUEUE_SZ 1000

/*====================| STRUCT AND ENUM DEFINITIONS |====================*/
typedef struct {
    int id;
    bool busy;
    // stats stuff
    int count;
    Time last_customer_served, total_idle, total_service;
} Server;

enum EventType { eCustomerArrived = 0, eCustPrimaryFinished = 1, eCustSecondaryFinished = 2 };

typedef struct {
    enum EventType event_type;
    Time arrival_time, prim_service_time, sec_service_time;
} Event;

/*====================| FUNCTION PROTOTYPES |====================*/
// FIFO Queue
void enqueue(Event[], int, int, Event);
Event dequeue(Event[], int, int);
int queuy_empty(int, int);
void display(Event[], int, int);

// Priority Queue
void siftup_queue(Event[], int);
void min_heapify(Event[], int);
void build_priority_queue(Event[]);
void insert_event(Event[], Event);
Event peek_minimum(Event[]);
Event extract_next_event(Event *);
void decrease_key(Event[], Event, int);

// Helper Utilities
void swap(Event *A, Event *B);
char *get_current_time();

/*====================| GLOBAL VARIABLES |====================*/
Event EVENT_QUEUE[QUEUE_SZ];  // event priority queue (note: min event time has highest priority)
int EVENT_CTR = 0;

Event PRIM_SERVER_QUEUE[QUEUE_SZ / 2];  // primary server FIFO queue
int PRIM_SERVER_HEAD, PRIM_SERVER_TAIL;
bool PRIM_SERVER_FLAG = false;
Event SEC_SERVER_QUEUE[QUEUE_SZ / 2];  // secondary server FIFO queue
int SEC_SERVER_HEAD, SEC_SERVER_TAIL;
bool SEC_SERVER_FLAG = false;

/*====================| MAIN |====================*/
int main(int argc, const char * argv[])
{
    char buffer[BUFFER_SZ], filename[BUFFER_SZ];
    FILE *fd;

    if (argc == 2)  // arg passed
        strncpy(filename, argv[1], BUFFER_SZ);  // safer copy
    else {  // no arg passed
        printf("Input file name >> ");
        fgets(filename, BUFFER_SZ, stdin);  // safer read from stdin than scanf()
    }

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("[!!] Error: Failed to open file\nExit(1)...\n");
        return -1;
    }

    char *ptr;
    long prim_servers, sec_servers;
    // Read number of primary and secondary servers
    fscanf(fd, "%s", buffer);
    prim_servers = strtol(buffer, &ptr, 10);
    fscanf(fd, "%s", buffer);
    sec_servers = strtol(buffer, &ptr, 10);

    // Initialize servers
    Server PRIMARY_SERVER[prim_servers];  // primary server array
    Server SECONDARY_SERVER[sec_servers];  // secondary server array

    int i;
    for (i=0; i < prim_servers; i++) {
        Server new_server;
        new_server.id = i + 1;
        new_server.busy = false;
        PRIMARY_SERVER[i] = new_server;
    }

    for (i=0; i < sec_servers; i++) {
        Server new_server;
        new_server.id = i + 1;
        new_server.busy = false;
        SECONDARY_SERVER[i] = new_server;
    }

    PRIM_SERVER_HEAD = PRIM_SERVER_TAIL = -1;
    SEC_SERVER_HEAD = SEC_SERVER_TAIL = -1;

    // Initialise the timer clock()
    clock_t t;
    t = clock();
    Time sim_time = 0;

    char buf1[15], buf2[15], buf3[15];
    fscanf(fd, "%s %s %s", buf1, buf2, buf3);
    // TODO:  Main event loop
    /*
     * while the event queue is not empty
     *      get the top priority event from the event queue
     *
     *      if event = customer arrival event
     *          handle this event...
     *          read next customer arrival event etc...
     *      else if event = customer finished being served in a primary server
     *          handle this event...
     *      else if event = customer finished being served in a secondary server
     *          handle this event...
     *      end if
     *
     *      move queued customers into a server if one is available, add event to event queue if a customer is served
     * end while
     * print stats
     * */
    do {
        if (strtod(buf1, &ptr) == 0 && strtod(buf2, &ptr) == 0 && strtod(buf3, &ptr) == 0)
            break;

        // Convert buffer strings to double
        Event new_event = { .arrival_time = strtod(buf1, &ptr),
                .prim_service_time = strtod(buf2, &ptr),
                .sec_service_time = strtod(buf3, &ptr),
                .event_type = eCustomerArrived };

        if (new_event.event_type == eCustomerArrived) {
            // if ()
        }
        insert_event(EVENT_QUEUE, new_event);

    } while (fscanf(fd, "%s %s %s", buf1, buf2, buf3) == 3);

    fclose(fd);

    int j;
    printf("BEFORE BUILD\n");
    for (j=0; j < EVENT_CTR; j++) printf("%f\n", EVENT_QUEUE[j].arrival_time);
    printf("MINIMUM: %f\n", peek_minimum(EVENT_QUEUE).arrival_time);
    // build_priority_queue(EVENT_QUEUE);
    printf("AFTER BUILD\n");
    int event_queue_size = EVENT_CTR;
    for (j=0; j < event_queue_size; j++)
        printf("%f\n", extract_next_event(EVENT_QUEUE).arrival_time);

    // Subtract start time from latest clock() snapshot
    t = clock() - t;
    Time time_taken = ((Time) t) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken: %.9f", time_taken);

    /* TODO:
     * Output, to standard output will consist of the following data:
     *  - Number of people served.
     *  - Time last service request is completed.
     *  - Average total service time.
     *  - Average total time in queue(s). Both overall and separate.
     *  - Average length of queue. For each queue and overall.
     *  - Maximum Length of queue. For each queue and overall.
     *  - Total idle time for each server.
     * */

    return 0;
}

/*==========| FIFO QUEUE (ARRAY IMPLEMENTATION) |==========*/
void enqueue(Event queue[], int head, int tail, Event ev)
{
    if (tail == QUEUE_SZ - 1)
        printf("Queue is full.");
    else {
        if (head == -1)
            head = 0;
        tail++;
        queue[tail] = ev;
    }
}

Event dequeue(Event queue[], int head, int tail)
{
    if (head == -1) {
        printf("Queue is empty.");
        return NULL;
    } else {
        Event next = queue[head];
        head++;
        if (head > tail)
            head = tail = -1;
        return next;
    }
}

int queuy_empty(int head, int tail)
{
    return tail == head;
}

void display(Event queue[], int head, int tail)
{
    if(tail == -1)
        printf("Queue is empty.");
    else{
        int i;
        printf("\nQueue elements are:\n");
        for(i=head; i<=tail; i++)
            printf("%f\n", queue[i].arrival_time);
    }
}

/*==========| PRIORITY QUEUE (HEAPS IMPLEMENTATION) |==========*/
// Siftdown
void min_heapify(Event A[], int i)
{
    int smallest = i;

    if (LEFT(i) <= EVENT_CTR && A[LEFT(i)].arrival_time < A[i].arrival_time)
        smallest = LEFT(i);

    if (RIGHT(i) <= EVENT_CTR && A[RIGHT(i)].arrival_time < A[smallest].arrival_time)
        smallest = RIGHT(i);

    if (smallest != i) {
        swap(&A[i], &A[smallest]);
        min_heapify(A, smallest);
    }
}

// Move the element up the heap to its correct position
void siftup_queue(Event A[], int i)
{
    if (i == 0)  // no children
        return;
    if (A[PARENT(i)].arrival_time > A[i].arrival_time) {
        swap(&A[i], &A[PARENT(i)]);
        siftup_queue(A, PARENT(i));
    }
}

void build_priority_queue(Event A[])
{
    int i;
    for (i = ((EVENT_CTR/2) - 1); i >= 0; i--)
        min_heapify(A, i);
}

// Inserts the element x into the set S
void insert_event(Event A[], Event x)
{
    if (EVENT_CTR == QUEUE_SZ - 1) {
        printf("Heap overflow");
        return;
    }

    EVENT_CTR++;
    int i = EVENT_CTR - 1;
    A[i] = x;

    // Fix min-heap property
    while (i != 0 && A[PARENT(i)].arrival_time > A[i].arrival_time) {
        swap(&A[i], &A[PARENT(i)]);
        i = PARENT(i);
    }
}

// Returns the minimum element of S with the min arrival time
Event peek_minimum(Event S[])
{
    return S[0];
}

// Removes and returns the element from S with the min arrival time
Event extract_next_event(Event *A)
{
    if (EVENT_CTR <= 0)
        printf("Heap underflow.");
    if (EVENT_CTR == 1) {
        EVENT_CTR--;
        return A[0];
    }

    Event next = A[0];
    A[0] = A[EVENT_CTR - 1];
    EVENT_CTR--;
    min_heapify(A, 0);
    return next;
}

// Decreases the value of element x's key to the new value x.
void decrease_key(Event A[], Event x, int i)
{
    A[i] = x;
    while (i != 0 && A[PARENT(i)].arrival_time > A[i].arrival_time) {
        swap(&A[i], &A[PARENT(i)]);
        i = PARENT(i);
    }
}

/****************| HELPER UTILITY FUNC IMPLEMENTATION |****************/
// A function to return the current time
void swap(Event *A, Event *B)
{
    Event temp = *A;
    *A = *B;
    *B = temp;
}

// to get index of parent
// int parent(int i) { return (i-1)/2; }
// to get index of left child of node at index i
// int left(int i) { return (2*i + 1); }
// to get index of RIGHT child of node at index i
// int right(int i) { return (2*i + 2); }

char *get_current_time()
{
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return asctime(timeinfo);
}
