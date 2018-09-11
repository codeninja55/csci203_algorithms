//
// Created by codeninja on 11/09/18.
//

#ifndef ASSIGNMENT02_C_VERSION_SERVERQUEUE_H
#define ASSIGNMENT02_C_VERSION_SERVERQUEUE_H

#include "EventQueue.h"

class ServerQueue {
    public:
        ServerQueue(int size);
        void enqueue(Customer c);
        Customer dequeue();
        bool is_empty();
    private:
        int _HEAD, _TAIL, _CAPACITY;
        Customer *_Q;
};


#endif //ASSIGNMENT02_C_VERSION_SERVERQUEUE_H
