//
// Created by codeninja on 11/09/18.
//

#ifndef ASSIGNMENT02_C_VERSION_SERVERS_H
#define ASSIGNMENT02_C_VERSION_SERVERS_H
#define MIN(a,b) ( ((a) < (b)) ? (a) : (b) )

#include "EventQueue.h"

struct Server {
    int id;
    bool busy;
    // stats
    int count;
    Time finish_time;
    // Time last_customer_served, total_idle, total_service;
};

typedef Server Server;

class Servers {
    public:
        explicit Servers(int size);
        void add_customer(Customer &c, Time finish_time);
        void remove_customer(int server_id);
        int next_server();
        Time server_wait_time();
        bool is_available();
        void display();
    private:
        Server *_idle;
        int _capacity;
};


#endif //ASSIGNMENT02_C_VERSION_SERVERS_H
