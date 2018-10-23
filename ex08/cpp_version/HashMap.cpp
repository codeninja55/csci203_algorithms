/*********************************************************************************
* CSCI203 (Spring 2018) - Exercise 08
* Exercise 08 - HashMap.cpp
* Purpose:
*
* @version 0.1.dev
* @date 2018.10.06
*
* @authors Dinh Che (codeninja55) <andrew at codeninja55.me>
*********************************************************************************/

#include <stdlib.h>
#include <iostream>
using namespace std;

//template for generic type
template<typename K, typename V>
class HashNode {
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
    //hash element array
    HashNode<K, V>** arr;
    int capacity;
    //current size
    int size;
    //dummy node
    HashNode<K, V>* dummy;

public:
    HashMap()
    {
        //Initial capacity of hash array
        capacity = 20;
        size = 0;
        arr = new HashNode<K, V>* [capacity];

        //Initialise all elements of array as NULL
        for (int i = 0; i<capacity; i++)
            arr[i] = NULL;

        //dummy node with value and key -1
        dummy = new HashNode<K, V>(-1, -1);
    }
    // This implements hash function to find index
    // for a key
    int hash_code(K key)
    {
        return key%capacity;
    }

    //Function to add key value pair
    void insert_node(K key, V value)
    {
        auto* temp = new HashNode<K, V>(key, value);

        // Apply hash function to find index for given key
        int hash_index = hash_code(key);

        //find next free space
        while (arr[hash_index]!=NULL && arr[hash_index]->key!=key
                && arr[hash_index]->key!=-1) {
            hash_index++;
            hash_index %= capacity;
        }

        //if new node to be inserted increase the current size
        if (arr[hash_index]==NULL || arr[hash_index]->key==-1)
            size++;
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

                //Insert dummy node here for further use
                arr[hash_index] = dummy;

                // Reduce size
                size--;
                return temp->value;
            }
            hash_index++;
            hash_index %= capacity;
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
            hash_index %= capacity;
        }

        //If not found return null
        return NULL;
    }

    //Return current size
    int size_of_map() { return size; }

    //Return true if size is 0
    bool is_empty() { return size==0; }

    //Function to display the stored key value pairs
    void display()
    {
        for (int i = 0; i<capacity; i++) {
            if (arr[i]!=NULL && arr[i]->key!=-1)
                cout << "key = " << arr[i]->key
                     << "  value = " << arr[i]->value << endl;
        }
    }
};
