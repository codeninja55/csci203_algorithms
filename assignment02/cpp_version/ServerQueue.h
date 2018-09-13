/*********************************************************************
* CSCI203 - Assignment 02
* ServerQueue.h - Header file for ServerQueue.cpp
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.12
*********************************************************************/

#ifndef ASSIGNMENT02_C_VERSION_SERVERQUEUE_H
#define ASSIGNMENT02_C_VERSION_SERVERQUEUE_H

#include "EventQueue.h"

class ServerQueue {
    public:
        explicit ServerQueue(int size, char *name);
        void enqueue(Customer c);
        Customer dequeue();
        int size();
        bool is_empty();
    private:
        int _head, _tail, _capacity, _n_customers;
        Customer *_q;
        char *_name;
};

#endif //ASSIGNMENT02_C_VERSION_SERVERQUEUE_H
