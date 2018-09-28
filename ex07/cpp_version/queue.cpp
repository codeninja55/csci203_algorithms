/*********************************************************************
* CSCI203 - Exercise 7
* queue.cpp - Queue template class implementation for FIFO queue.
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.28
*********************************************************************/

#include <iostream>
#include "queue.h"

template<class T>
Queue<T>::Queue(): _head(-1), _tail(-1), _capacity(0), n_items(0)
{
    items = new T[2];
}

template<class T>
Queue<T>::Queue(int size): _head(-1), _tail(-1), _capacity(size), n_items(0)
{
    items = new T[size];
}

template<class T>
Queue<T>::~Queue()
{
    delete[] items;
}

template<class T>
int Queue<T>::is_full() { return (_head == _capacity - 1) ? 1 : 0; }

template<class T>
int Queue<T>::is_empty() { return (_head == -1) ? 1 : 0; }

template<class T>
void Queue<T>::enqueue(T elem)
{
    if (is_full() == 1) {
        std::cout << "Queue is full.\n";
        return;
    } else {
        if (_head == -1) _head = 0;



        _tail++;
        items[_tail] = elem;
    }
}

template<class T>
void Queue<T>::probe()
{
    if (n_items > _capacity / 2) {
        T tmp = items;
        items = new T[_capacity * 2];
        int i;
        for (i = 0; i < _capacity; i++) items[i] = tmp[i];
        _capacity *= 2;
        delete[] tmp;
    }
}

template<class T>
T Queue<T>::dequeue() {
    T ret;
    if (is_empty() == 1) {
        std::cout << "Queue is empty.\n";
        ret = -1;
    } else {
        ret = items[_head++];
        if (_head > _tail) _head = _tail = -1;
    }
    return ret;
}

template<class T>
void Queue<T>::print_queue() {
    int i;
    std::cout << "Queue ==> ";
    for (i = 0; i < n_items; i++)
        std::cout << items[i] << " ";
    std::cout << std::endl;
}
