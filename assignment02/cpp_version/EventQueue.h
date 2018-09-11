/*********************************************************************
* CSCI203 - Assignment 02
* ass2.cpp - C++ main() driver for implementation of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.11
*********************************************************************/

#ifndef ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
#define ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
#define PARENT(i) ( (i-1) / 2 )
#define LEFT(i) ( (i * 2) + 1 )
#define RIGHT(i) ( (i * 2) + 2 )
#define SWAP(x,y) do \
   { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
     memcpy(swap_temp,&y, sizeof(x)); \
     memcpy(&y,&x,        sizeof(x)); \
     memcpy(&x,swap_temp, sizeof(x)); \
    } while(0)

typedef double Time;

enum EventType { eCustomerArrived = 0, eCustPrimaryFinished = 1, eCustSecondaryFinished = 2 };

typedef struct {
    double arrival_time, prim_service_duration, sec_service_duration;
} Customer;

typedef struct {
    EventType type;
    Time event_time;
    Customer customer;
    int server_id;
} Event;

class EventQueue {
    public:
        explicit EventQueue(int size);  // initialiser
        void add_event(Event &ev);
        Event extract_next_event(Customer c, int &server_id);
        Event peek_next_event();
        // void decrease_key(Event ev, int i);
    private:
        void min_heapify(int i);
        // void siftup_queue(int i);
        // void build_priority_queue();
        void swap(Event *A, Event *B);

        int _N_EVENTS;
        int _CAPACITY;
        Event *_Q;
};

#endif //ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
