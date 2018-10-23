/*********************************************************************************
 * CSCI203 Algorithms and Data Structures - Assignment 03
 * Assignment03 MinHeap.h
 * Purpose:
 *
 * @version 0.1.dev
 * @date 23/10/18
 *
 * @author Andrew Dinh Che (codeninja55) <andrew@codeninja55.me>
 * @UOW dbac496 (5721970) <dbac496@uowmail.edu.au>
 *
 *********************************************************************************/

#ifndef ASSIGNMENT03_MINHEAP_H
#define ASSIGNMENT03_MINHEAP_H
#define MAX(a,b) ( (a > b) ? a : b )
#define MIN(a,b) ( (a < b) ? a : b )
#define PARENT(i) ( (i - 1) / 2 )  // get the parent index
#define LEFT(i) ( (2 * i) + 1 )    // get the left index
#define RIGHT(i) ( (2 * i) + 2 )   // get the right index

#include <cstdio>

template<class T>
class MinHeap {
public:
    explicit MinHeap(int capacity);           // default constructor
    void min_heapify(T elem);                 // sift down to heapify and re-balance tree
    void insert(T elem);                      // insert a new key
    T extract();                              // extract the top of the tree
    void decrease_key(int idx, T new_elem);   // decrease key value of key at index i to a new elem
    T get_min() { return HEAP[0]; }           // return the top of the heap
    // void remove(int idx);                  // delete the key stored at the index
private:
    long long int hash(T key);
    void probe();
    void swap(T *a, T *b);
    int _capacity;
    int _size;
    T * HEAP;
};

template<class T>
MinHeap<T>::MinHeap(int capacity) : _capacity(capacity), _size(0)
{
    HEAP = new T[_capacity];
    // initialise all elements
    for (int i=0; i < _capacity; i++)
        HEAP[i] = NULL;
}

template<class T>
void MinHeap<T>::min_heapify(T elem)
{
    int smallest = elem;

    if (LEFT(elem) < _size && HEAP[LEFT(elem)] < HEAP[elem])
        smallest = LEFT(elem);
    if (RIGHT(elem) < _size && HEAP[RIGHT(elem)] < HEAP[smallest])
        smallest = RIGHT(elem);
    if (smallest != elem) {
        swap(&HEAP[elem], &HEAP[smallest]);
        min_heapify(smallest);
    }
}

template<class T>
void MinHeap<T>::insert(T elem)
{
    if (_size == (_capacity - 1)) {
        perror("Could not insert element.");
        return;
    }

    MinHeap::probe();

    _size++;  // insert at end
    T idx = _size - 1;
    HEAP[idx] = elem;

    // heapify to re-balance
    while (idx != 0 && HEAP[PARENT(idx)] > HEAP[idx]) {
        MinHeap::swap(&HEAP[idx], &HEAP[PARENT(idx)]);
        idx = PARENT(idx);
    }
}

template<class T>
T MinHeap<T>::extract()
{
    if (_size <= 0)
        return -1;

    if (_size == 1) {
        _size--;
        return HEAP[0];
    }

    T root = HEAP[0];
    HEAP[0] = HEAP[_size - 1];
    _size--;
    MinHeap::min_heapify(0);

    return root;
}

// TODO: may not be necessary
template<class T>
long long int MinHeap<T>::hash(T key) {
    return key % _capacity;
}

template<class T>
void MinHeap<T>::probe()
{
    if (_size == (_capacity / 2)) {
        T *tmp = HEAP;
        HEAP = new T[_capacity * 2];
        int i;
        for (i = 0; i < _capacity; i++) HEAP[i] = tmp[i];
        _capacity *= 2;
        delete[] tmp;
    }
}

template<class T>
void MinHeap<T>::swap(T *a, T *b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

#endif //ASSIGNMENT03_MINHEAP_H
