//
// Created by codeninja on 11/09/18.
//

#include <iostream>
#include "Servers.h"

Servers::Servers(int size)
{
    _IDLE = new Server[size];
    _CAPACITY = size;

    int i;
    for (i = 0; i < size; i++) {
        Server new_server = { i, false, 0 };
        _IDLE[i] = new_server;
    }
}

void Servers::add_customer(Customer &c)
{
    c.server_id = next_server();
    _IDLE[c.server_id].busy = true;
}

void Servers::remove_customer(int server_id)
{
    _IDLE[server_id].busy = false;
}

int Servers::next_server()
{
    int i;
    for (i = 0; i < _CAPACITY; i++ ) {
        if (!_IDLE[i].busy)
            return i;
    }
    return -1;
}

bool Servers::is_available()
{
    int i;
    for (i=0; i < _CAPACITY; i++) {
        if (!_IDLE[i].busy)
            return true;
    }
    return false;
}

