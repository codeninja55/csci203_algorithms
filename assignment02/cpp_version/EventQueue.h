/*********************************************************************
* CSCI203 - Assignment 02
* ass2.cpp - C++ main() driver for implementation of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.11
*********************************************************************/

#ifndef ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
#define ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )
#define PARENT(i) ( (i-1) / 2 )
#define LEFT(i) ( (i * 2) + 1 )
#define RIGHT(i) ( (i * 2) + 2 )
#define Time double
#define Id int

static int G_CUST_ID = 1;

enum EventType { eCustomerArrived = 0, eCustPrimaryFinished = 1, eCustSecondaryFinished = 2 };

struct Customer {
    Time arrival_time, prim_service_duration, sec_service_duration;
    Time wait_duration;
    Id cust_id, server_id;
};

struct Event {
    EventType type;  // type of event
    Time event_time;  // snapshot time of event
    Customer customer;  // customer for event
};

typedef Event Event;
typedef Customer Customer;

class EventQueue {
    public:
        explicit EventQueue(int size);  // initialiser
        void add_event(EventType ev_type, double ev_time, Customer &cust);
        Event extract_next_event();
        Event peek_next_event();
        bool more_events();
        void display();
    private:
        void min_heapify(int i);
        int _n_events;
        int _capacity;
        Event *_q;
};

#endif //ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
