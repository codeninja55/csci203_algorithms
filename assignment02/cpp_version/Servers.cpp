/*********************************************************************
* CSCI203 - Assignment 02
* Servers.cpp - Implementation for Server arrays.
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.12
*********************************************************************/
#include <iostream>
#include <values.h>
#include "Servers.h"

Servers::Servers(int size, char *name) : _capacity(size), _name(name)
{
    _idle = new Server[size];
    int i;
    for (i = 0; i < _capacity; i++) {
        Server new_server = { i, false, 0, 0, 0 };
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
        _idle[next_server_id].cust_id = c.id;
    }
}

void Servers::remove_customer(int server_id) {
    _idle[server_id].busy = false;
    _idle[server_id].finish_time = 0;
    // _idle[server_id].cust_id = 0;  // leave this commented to see last cust_id served
}

int Servers::next_server()
{
    int i;
    for (i = 0; i < _capacity; i++ )
        if (!_idle[i].busy) return i;
    return -1;
}

Time Servers::next_server_time() {
    int i;
    Time wait_time = 9999999.9;
    for (i=0; i < _capacity; i++)
        wait_time = MIN(wait_time, _idle[i].finish_time);
    // TODO: Testing
    std::cout << "Next available " << _name << " server time ==> " << wait_time << std::endl;
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
    std::cout << _name << "_Servers ==> ";
    for (i = 0; i < _capacity; i++)
        std::cout<< "[ {" << _idle[i].id << "} <ID " <<_idle[i].cust_id << "> : Finish: " << _idle[i].finish_time << " ] ";
    std::cout<<std::endl;
}

