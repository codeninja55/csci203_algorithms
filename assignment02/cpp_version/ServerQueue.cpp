//
// Created by codeninja on 11/09/18.
//

#include <iostream>
#include "ServerQueue.h"

ServerQueue::ServerQueue(int size) {
    _Q = new Customer[size];
    _CAPACITY = size;
    _HEAD = _TAIL = -1;
}

void ServerQueue::enqueue(Customer c)
{
    if (_TAIL == _CAPACITY - 1)
        std::cout << "Queue is full." << std::endl;
    else {
        if (_HEAD == -1)
            _HEAD = 0;
        _TAIL++;
        _Q[_TAIL] = c;
    }
}

Customer ServerQueue::dequeue()
{
    if (_HEAD == -1) {
        std::cout << "Queue is empty." << std::endl;
        return NULL;
    } else {
        Customer c = _Q[_HEAD];
        _HEAD++;
        if (_HEAD > _TAIL)
            _HEAD = _TAIL = -1;
        return c;
    }
}

bool ServerQueue::is_empty() {
    return false;
}
