/*********************************************************************
* CSCI203 - Exercise 7
* queue.h - Queue template class header.
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.28
*********************************************************************/

#ifndef EXERCISE07_QUEUE_H
#define EXERCISE07_QUEUE_H

template<class T>
class Queue {
public:
    explicit Queue();
    explicit Queue(int);
    ~Queue();
    int is_full();
    int is_empty();
    void enqueue(T);
    void probe();
    T dequeue();
    void print_queue();
private:
    T *items;
    int _head, _tail, _capacity, n_items;
};

#endif //EXERCISE07_QUEUE_H
