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

typedef double Time;

enum EventType { eCustomerArrived = 0, eCustPrimaryFinished = 1, eCustSecondaryFinished = 2 };

struct Customer {
    double arrival_time, prim_service_duration, sec_service_duration;
    int server_id;
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
        // void decrease_key(Event ev, int i);
        void display();
    private:
        void min_heapify(int i);
        // void siftup_queue(int i);
        // void build_priority_queue();

        int _n_events;
        int _capacity;
        Event *_q;
};

#endif //ASSIGNMENT02_C_VERSION_EVENTQUEUE_H
