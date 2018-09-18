/*********************************************************************
* CSCI203 - Assignment 02
* Servers.h - Header file for Servers.cpp
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.12
*********************************************************************/
#ifndef ASSIGNMENT02_C_VERSION_SERVERS_H
#define ASSIGNMENT02_C_VERSION_SERVERS_H
#define MIN(a,b) ( ((a) < (b)) ? (a) : (b) )

#include "EventQueue.h"

struct Server {
    int idx;
    // stats
    int count;
    double finish_time, total_idle_time, total_service_time;
};

typedef Server Server;

class Servers {
    public:
        explicit Servers(unsigned int size, char *name);  // main initialiser
        void add_customer(Customer &c, double start_time, double finish_time);
        void remove_customer(int s_idx);  // enqueue server
        void enqueue(int s_idx);
        int dequeue();  // dequeue server
        bool is_available();
        void display_server_statistics(double last_service_time);
    private:
        Server *_servers;
        int *_idle;
        char *_name;
        int _head, _tail;
        unsigned int _capacity, _n_idle_servers;
};

#endif //ASSIGNMENT02_C_VERSION_SERVERS_H
