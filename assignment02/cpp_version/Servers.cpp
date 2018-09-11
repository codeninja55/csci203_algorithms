//
// Created by codeninja on 11/09/18.
//

#include <iostream>
#include <values.h>
#include "Servers.h"

Servers::Servers(int size) : _capacity(size)
{
    _idle = new Server[_capacity];
    int i;
    for (i = 0; i < _capacity; i++) {
        Server new_server = { i, false, 0, 0};
        _idle[i] = new_server;
    }
}

void Servers::add_customer(Customer &c, Time finish_time)
{
    int next_server_id = next_server();
    if (next_server_id != -1) {
        c.server_id = next_server_id;
        _idle[next_server_id].busy = true;
        _idle[next_server_id].finish_time = finish_time;
        _idle[next_server_id].count++;
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

Time Servers::server_wait_time() {
    int i;
    Time wait_time = MAXDOUBLE;
    for (i=0; i < _capacity; i++)
        wait_time = MIN(wait_time, _idle[i].finish_time);
    // TODO: Testing
    std::cout << "Wait Time: " << wait_time << std::endl;
    return wait_time;
}

bool Servers::is_available()
{
    int i;
    for (i=0; i < _capacity; i++)
        if (!_idle[i].busy) return true;
    return false;
}

void Servers::display()
{
    int i;
    for (i = 0; i < _capacity; i++)
        std::cout<<"[ "<<_idle[i].id<<" : "<<_idle[i].finish_time<<" ]";
    std::cout<<std::endl;
}

