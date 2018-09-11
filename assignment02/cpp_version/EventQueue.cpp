/*********************************************************************
* CSCI203 - Assignment 02
* ass2.cpp - C++ main() driver for implementation of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.11
*********************************************************************/

#include <iostream>
#include "EventQueue.h"

void swap(Event *A, Event *B);

EventQueue::EventQueue(int size) : _capacity(size), _n_events(0)
{
    _q = new Event[_capacity];
}

void EventQueue::min_heapify(int i)
{
    int smallest = i;

    if (LEFT(i) <= _n_events && _q[LEFT(i)].customer.arrival_time < _q[i].customer.arrival_time)
        smallest = LEFT(i);

    if (RIGHT(i) <= _n_events && _q[RIGHT(i)].customer.arrival_time < _q[smallest].customer.arrival_time)
        smallest = RIGHT(i);

    if (smallest != i) {
        swap(&_q[i], &_q[smallest]);
        min_heapify(smallest);
    }
}

void EventQueue::add_event(EventType ev_type, double ev_time, Customer &cust)
{
    if (_n_events == _capacity - 1) {
        std::cout << "Event Queue overflow." << std::endl;
        return;
    }

    _n_events++;
    int i = _n_events - 1;
    Event new_event = { ev_type, ev_time, cust };
    _q[i] =  new_event;

    // Fix min-heap property
    while (i != 0 && _q[PARENT(i)].customer.arrival_time > _q[i].customer.arrival_time) {
        swap(&_q[i], &_q[PARENT(i)]);
        i = PARENT(i);
    }
}

Event EventQueue::peek_next_event() { return _q[0]; }

Event EventQueue::extract_next_event()
{
    if (_n_events <= 0)
        std::cout << "Event Queue underflow."<< std::endl;

    if (_n_events == 1) {
        _n_events--;
        return _q[0];
    }

    Event next = _q[0];
    _q[0] = _q[_n_events - 1];
    _n_events--;
    min_heapify(0);
    return next;
}

bool EventQueue::more_events() { return _n_events > 0; }

void EventQueue::display()
{
    int i;
    std::cout << "Event Queue: " << std::endl;
    for (i = 0; i < _n_events; i++)
        std::cout << "Event: " << _q[i].event_time << std::endl;
}

void swap(Event *A, Event *B)
{
    Event temp = *A;
    *A = *B;
    *B = temp;
}
