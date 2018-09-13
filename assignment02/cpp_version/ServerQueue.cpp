/*********************************************************************
* CSCI203 - Assignment 02
* ServerQueue.cpp - Implementation source file for a FIFO queue for
* each server type.
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.12
*********************************************************************/
#include <iostream>
#include "ServerQueue.h"

ServerQueue::ServerQueue(int size, char *name) : _capacity(size), _head(-1), _tail(-1), _n_customers(0), _name(name)
{
    _q = new Customer[_capacity];
}

void ServerQueue::enqueue(Customer c)
{
    if (_tail == _capacity - 1)
        std::cout << "Enqueue: " << _name << "Server_Q is full." << std::endl;
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
        std::cout << "Dequeue: " << _name << "_Server_Q is empty." << std::endl;
    } else {
        cust = _q[_head];
        _head++;
        if (_head > _tail)
            _head = _tail = -1;
        _n_customers--;
        return cust;
    }
}

int ServerQueue::size() { return _n_customers; }

bool ServerQueue::is_empty() { return _tail == -1; }
