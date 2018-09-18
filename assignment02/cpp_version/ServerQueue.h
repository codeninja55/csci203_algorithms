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
        void add_waiting_customer(Customer &c, double ev_time);
        void enqueue(Customer &c);
        Customer dequeue();
        Customer next_waiting_customer(double ev_time);
        void calculate_average_queue_len(double ev_time);
        bool is_empty();
        int get_max_q_len() const;
        double get_avg_queue_len() const;
        double get_sum_q_len() const;
        double get_sum_q_len_time() const;
    private:
        int _head, _tail, _capacity, _n_customers, _max_q_len;
        double _sum_q_len, _sum_q_len_time, _prev_q_len_change_time;
        Customer *_q;
        char *_name;
};

#endif //ASSIGNMENT02_C_VERSION_SERVERQUEUE_H
