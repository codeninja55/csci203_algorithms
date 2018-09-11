//
// Created by codeninja on 11/09/18.
//

#ifndef ASSIGNMENT02_C_VERSION_SERVERS_H
#define ASSIGNMENT02_C_VERSION_SERVERS_H

#include "EventQueue.h"

struct Server {
    int id;
    bool busy;
    // stats
    int count;
    // Time last_customer_served, total_idle, total_service;
};

typedef Server Server;

class Servers {
    public:
        explicit Servers(int size);
        void add_customer(Customer &c);
        void remove_customer(int server_id);
        int next_server();
        bool is_available();

    private:
        Server *_IDLE;
        int server_id;
        int _CAPACITY;
};


#endif //ASSIGNMENT02_C_VERSION_SERVERS_H
