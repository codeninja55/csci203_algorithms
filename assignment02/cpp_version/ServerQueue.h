//
// Created by codeninja on 11/09/18.
//

#ifndef ASSIGNMENT02_C_VERSION_SERVERQUEUE_H
#define ASSIGNMENT02_C_VERSION_SERVERQUEUE_H

#include "EventQueue.h"

class ServerQueue {
    public:
        explicit ServerQueue(int size);
        void enqueue(Customer c);
        Customer dequeue();
        int size();
        bool is_empty();
        void display();
    private:
        int _head, _tail, _capacity, _n_customers;
        Customer *_q;
};


#endif //ASSIGNMENT02_C_VERSION_SERVERQUEUE_H
