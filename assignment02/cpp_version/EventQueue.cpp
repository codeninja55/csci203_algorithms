/*********************************************************************
* CSCI203 - Assignment 02
* EventQueue.cpp - Implementation source code for Event priority queue
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.12
*********************************************************************/



void swap(Event *A, Event *B);

EventQueue::EventQueue(int size) : _capacity(size), _n_events(0)
{
    _q = new Event[_capacity];
}

void EventQueue::min_heapify(int i)
{
    int smallest = i;

    if (LEFT(i) <= _n_events && _q[LEFT(i)].ev_time < _q[i].ev_time)
        smallest = LEFT(i);

    if (RIGHT(i) <= _n_events && _q[RIGHT(i)].ev_time < _q[smallest].ev_time)
        smallest = RIGHT(i);

    if (smallest != i) {
        swap(&_q[i], &_q[smallest]);
        min_heapify(smallest);
    }
}

void EventQueue::add_event(EventType ev_type, double ev_time, Customer &cust)
{
    if (_n_events == _capacity - 1) {
        std::cout << "Event queue overflow." << std::endl;
        return;
    }

    if (_n_events == (_capacity / 2)) {
        Event *tmp;
        tmp = new Event[_capacity * 2];
        
        for ()
    }

    int i = _n_events++;
    Event new_event = { ev_type, ev_time, cust };
    _q[i] =  new_event;

    // Fix min-heap property
    while (i != 0 && _q[PARENT(i)].ev_time > _q[i].ev_time) {
        swap(&_q[i], &_q[PARENT(i)]);
        i = PARENT(i);
    }
}

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

void swap(Event *A, Event *B)
{
    Event temp = *A;
    *A = *B;
    *B = temp;
}
