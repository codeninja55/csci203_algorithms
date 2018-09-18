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
    _max_q_len = 0;
    _sum_q_len = _sum_q_len_time = _prev_q_len_change_time = 0;
    _q = new Customer[_capacity];
}

void ServerQueue::add_waiting_customer(Customer &c, double ev_time)
{
    calculate_average_queue_len(ev_time);
    enqueue(c);
    _max_q_len = MAX(_max_q_len, _n_customers);
}

void ServerQueue::calculate_average_queue_len(double ev_time)
{
    // current_time - previous time length
    double q_len_delta_time = ev_time - _prev_q_len_change_time;  // last time the queue was changed
    _sum_q_len += q_len_delta_time * _n_customers;
    _sum_q_len_time += q_len_delta_time;
    _prev_q_len_change_time = ev_time;  // save the snapshot change time before enqueue/dequeue called
}

void ServerQueue::enqueue(Customer &c)
{
    if (_n_customers == _capacity - 1)
        std::cout << "Enqueue: " << _name << "Server_Q is full." << std::endl;
    else {
        if (_head == -1)
            _head = 0;
        _tail++;
        _q[_tail] = c;
        _n_customers++;
    }
}

Customer ServerQueue::next_waiting_customer(double ev_time)
{
    calculate_average_queue_len(ev_time);
    return dequeue();
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

int ServerQueue::get_max_q_len() const { return _max_q_len; }

double ServerQueue::get_avg_queue_len() const { return _sum_q_len / _sum_q_len_time; }

double ServerQueue::get_sum_q_len() const { return _sum_q_len; }

double ServerQueue::get_sum_q_len_time() const { return _sum_q_len_time; }

bool ServerQueue::is_empty() { return _head == -1; }
