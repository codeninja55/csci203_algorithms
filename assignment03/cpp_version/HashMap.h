#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"
/*********************************************************************************
 * CSCI203 Algorithms and Data Structures - Assignment 03
 * Assignment03 HashMap.h
 * Purpose:
 *
 * @version 0.1.dev
 * @date 24/10/18
 *
 * @author Andrew Dinh Che (codeninja55) <andrew@codeninja55.me>
 * @UOW dbac496 (5721970) <dbac496@uowmail.edu.au>
 *
 *********************************************************************************/
#ifndef ASSIGNMENT03_HASHMAP_H
#define ASSIGNMENT03_HASHMAP_H

#include <stdlib.h>
#include <iostream>
using namespace std;

//template for generic type
template<typename K, typename V>
struct HashNode {
    public:
        V value;
        K key;

        //Constructor of hashnode
        HashNode(K key, V value)
        {
            this->value = value;
            this->key = key;
        }
};

template<typename K, typename V>
class HashMap {
    private:
        HashNode<K, V>** arr;     //hash element array
        int _capacity;            // total capacity of the map
        int _size;                //current size
    public:
        HashMap()
        {
            //Initial capacity of hash array
            _capacity = 20;
            _size = 0;
            arr = new HashNode<K, V>* [_capacity];

            //Initialise all elements of array as NULL
            for (int i = 0; i<_capacity; i++) arr[i] = NULL;
        }

        explicit HashMap(int capacity)
        {
            _capacity = capacity;
            _size = 0;
            arr = new HashNode<K, V>* [_capacity];

            //Initialise all elements of array as NULL
            for (int i = 0; i<_capacity; i++) arr[i] = NULL;
        }

        // This implements hash function to find index
        // for a key
        int hash_code(K key) { return key % _capacity;}

        //Function to add key value pair
        void insert_node(K key, V value)
        {
            HashNode<K, V> *temp = new HashNode<K, V>(key, value);

            // Apply hash function to find index for given key
            int hash_index = hash_code(key);

            //find next free space
            while (arr[hash_index]!=NULL && arr[hash_index]->key!=key
                    && arr[hash_index]->key!=-1) {
                hash_index++;
                hash_index %= _capacity;
            }

            //if new node to be inserted increase the current size
            if (arr[hash_index]==NULL || arr[hash_index]->key==-1)
                _size++;
            arr[hash_index] = temp;
        }

        //Function to delete a key value pair
        V delete_node(int key)
        {
            // Apply hash function to find index for given key
            int hash_index = hash_code(key);

            //finding the node with given key
            while (arr[hash_index]!=NULL) {
                //if node found
                if (arr[hash_index]->key==key) {
                    HashNode<K, V>* temp = arr[hash_index];

                    // Reduce size
                    _size--;
                    return temp->value;
                }
                hash_index++;
                hash_index %= _capacity;
            }

            //If not found return null
            return NULL;
        }

        //Function to search the value for a given key
        V get(int key)
        {
            // Apply hash function to find index for given key
            int hash_index = hash_code(key);

            //finding the node with given key
            while (arr[hash_index]!=NULL) {
                //if node found return its value
                if (arr[hash_index]->key==key)
                    return arr[hash_index]->value;
                hash_index++;
                hash_index %= _capacity;
            }

            //If not found return null
            return NULL;
        }

        //Return current size
        int size() { return _size; }

        //Return true if size is 0
        bool is_empty() { return _size==0; }

        //Function to display the stored key value pairs
        void display()
        {
            for (int i = 0; i<_capacity; i++) {
                if (arr[i] != NULL && arr[i]->key != -1)
                    cout << "key = " << arr[i]->key << "  value = " << arr[i]->value << endl;
            }
        }
};
#endif //ASSIGNMENT03_HASHMAP_H

#pragma clang diagnostic pop