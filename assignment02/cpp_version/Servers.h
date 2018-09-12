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
    int id;
    bool busy;
    // stats
    int count, last_cust_served;
    double finish_time, total_idle_time, total_service_time;
};

typedef Server Server;

class Servers {
    public:
        explicit Servers(int size, char *name);
        void add_customer(Customer &c, double finish_time);
        void remove_customer(int server_id);
        int next_server();
        bool is_available();
        void display();
    private:
        Server *_idle;
        char *_name;
        int _capacity;
};

#endif //ASSIGNMENT02_C_VERSION_SERVERS_H
