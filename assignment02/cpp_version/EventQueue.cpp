/*********************************************************************
* CSCI203 - Assignment 02
* ass2.cpp - C++ main() driver for implementation of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.11
*********************************************************************/

#include <iostream>
#include "EventQueue.h"

EventQueue::EventQueue(int size)
{
    _CAPACITY = size;
    _N_EVENTS = 0;
    _Q = new Event[size];
}

void EventQueue::min_heapify(int i)
{
    int smallest = i;

    if (LEFT(i) <= _N_EVENTS && _Q[LEFT(i)].customer.arrival_time < _Q[i].customer.arrival_time)
        smallest = LEFT(i);

    if (RIGHT(i) <= _N_EVENTS && _Q[RIGHT(i)].customer.arrival_time < _Q[smallest].customer.arrival_time)
        smallest = RIGHT(i);

    if (smallest != i) {
        swap(&_Q[i], &_Q[smallest]);
        min_heapify(smallest);
    }
}

void EventQueue::add_event(Event &ev)
{
    if (_N_EVENTS == _CAPACITY - 1) {
        std::cout << "Event Queue overflow." << std::endl;
        return;
    }

    _N_EVENTS++;
    int i = _N_EVENTS - 1;
    _Q[i] =  ev;

    // Fix min-heap property
    while (i != 0 && _Q[PARENT(i)].customer.arrival_time > _Q[i].customer.arrival_time) {
        swap(&_Q[i], &_Q[PARENT(i)]);
        i = PARENT(i);
    }
}

Event EventQueue::peek_next_event()
{
    return _Q[0];
}

Event EventQueue::extract_next_event(Customer c, int &server_id)
{
    if (_N_EVENTS <= 0)
        std::cout << "Heap underflow."<< std::endl;

    if (_N_EVENTS == 1) {
        _N_EVENTS--;
        return _Q[0];
    }

    Event next = _Q[0];
    _Q[0] = _Q[_N_EVENTS - 1];
    _N_EVENTS--;
    min_heapify(0);
    return next;
}

void EventQueue::swap(Event *A, Event *B)
{
    Event temp = *A;
    *A = *B;
    *B = temp;
}


