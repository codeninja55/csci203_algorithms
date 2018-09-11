//
// Created by codeninja on 11/09/18.
//

#ifndef ASSIGNMENT02_C_VERSION_SERVERS_H
#define ASSIGNMENT02_C_VERSION_SERVERS_H

#include "EventQueue.h"

typedef double Time;

typedef struct {
    int id;
    bool busy;
    // stats
    int count;
    Time last_customer_served, total_idle, total_service;
} Server;

class Servers {
    private:
        explicit Servers(int size);
        void add_customer(Customer c);
        void remove_customer(int server_id);
        bool is_available();
    public:
        Server *_IDLE;
};


#endif //ASSIGNMENT02_C_VERSION_SERVERS_H
