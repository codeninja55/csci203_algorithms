//
// Created by codeninja on 11/09/18.
//

#include <iostream>
#include "ServerQueue.h"

ServerQueue::ServerQueue(int size) : _capacity(size), _head(-1), _tail(-1), _n_customers(0)
{
    _q = new Customer[_capacity];
}

void ServerQueue::enqueue(Customer c)
{
    if (_tail == _capacity - 1)
        std::cout << "Queue is full." << std::endl;
    else {
        if (_head == -1)
            _head = 0;
        _tail++;
        _q[_tail] = c;
        _n_customers++;
    }
}

Customer ServerQueue::dequeue()
{
    Customer cust;
    if (_head == -1) {
        std::cout << "Server Queue is empty." << std::endl;
    } else {
        cust = _q[_head];
        _head++;
        if (_head > _tail)
            _head = _tail = -1;
        return cust;
    }
}

int ServerQueue::size() { return _n_customers; }

bool ServerQueue::is_empty() { return _head == -1; }

void ServerQueue::display()
{
    if (_tail == -1)
        std::cout << "Server Queue is empty" << std::endl;
    else {
        int i;
        std::cout << "Queue elements are:" << std::endl;
        for (i = _head; i <= _tail; i++)
            std::cout << _q[i].arrival_time << std::endl;
    }
}
