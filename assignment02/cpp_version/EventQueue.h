/*********************************************************************
* CSCI203 - Assignment 02
* EventQueue.h - Header file for EventQueue.cpp
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.12
*********************************************************************/
#ifndef ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
#define ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )
#define PARENT(i) ( (i-1) / 2 )
#define LEFT(i) ( (i * 2) + 1 )
#define RIGHT(i) ( (i * 2) + 2 )

enum EventType { eCustomerArrived = 0, eCustPrimaryFinished = 1, eCustSecondaryFinished = 2 };

struct Customer {
    double arrival_time, p_service_duration, s_service_duration;
    double wait_duration, cust_queued_time;
    int server_idx;
};

struct Event {
    EventType type;  // type of event
    double ev_time;  // snapshot time of event to process
    Customer cust;  // customer for event
};

typedef Event Event;
typedef Customer Customer;

class EventQueue {
    public:
        explicit EventQueue(int size);  // initialiser
        void add_event(EventType ev_type, double ev_time, Customer &cust);
        Event extract_next_event();
        bool more_events();
    private:
        void min_heapify(int i);
        int _n_events, _capacity;
        Event *_q;
};

#endif //ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
