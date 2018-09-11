//
// Created by codeninja on 11/09/18.
//

#include <iostream>
#include "Servers.h"

Servers::Servers(int size) : _capacity(size)
{
    _idle = new Server[_capacity];
    int i;
    for (i = 0; i < _capacity; i++) {
        Server new_server = { i, false, 0 };
        _idle[i] = new_server;
    }
}

void Servers::add_customer(Customer &c)
{
    int next_server_id = next_server();
    if (next_server_id != -1) {
        c.server_id = next_server_id;
        _idle[next_server_id].busy = true;
    }
}

void Servers::remove_customer(int server_id) { _idle[server_id].busy = false; }

int Servers::next_server()
{
    int i;
    for (i = 0; i < _capacity; i++ )
        if (!_idle[i].busy) return i;
    return -1;
}

bool Servers::is_available()
{
    int i;
    for (i=0; i < _capacity; i++)
        if (!_idle[i].busy) return true;
    return false;
}

