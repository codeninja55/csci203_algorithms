/*********************************************************************
* CSCI203 - Assignment 02
* Servers.cpp - Implementation for Server arrays.
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.12
*********************************************************************/
#include <iostream>
#include <iomanip>
#include "Servers.h"
using namespace std;

Servers::Servers(int size, char *name) : _capacity(size), _name(name)
{
    _idle = new Server[size];
    int i;
    for (i = 0; i < _capacity; i++) {
        Server new_server;
        new_server.id = i;
        new_server.busy = false;
        new_server.finish_time = new_server.last_ev_time = new_server.total_idle_time = 0;
        new_server.last_cust_served = new_server.count = 0;
        _idle[i] = new_server;
    }
}

void Servers::add_customer(Customer &c, double ev_time,  double finish_time)
{
    int next_server_id = next_server();
    if (next_server_id != -1) {
        c.server_id = next_server_id;
        _idle[next_server_id].busy = true;

        // TODO
        double last_service_time = _idle[next_server_id].last_ev_time;
        _idle[next_server_id].total_idle_time += ev_time - last_service_time;

        _idle[next_server_id].total_service_time += ev_time - finish_time;
        _idle[next_server_id].finish_time = finish_time;
        _idle[next_server_id].last_ev_time = ev_time;
        _idle[next_server_id].count++;
        _idle[next_server_id].last_cust_served = c.id;
    }
}

void Servers::remove_customer(int server_id) {
    _idle[server_id].busy = false;
    _idle[server_id].finish_time = 0;
    // _idle[server_id].last_cust_served = 0;  // leave this commented to see last cust_id served
}

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

void Servers::display()
{
    int i;
    std::cout << _name << "_Servers ==> ";
    for (i = 0; i < _capacity; i++)
        std::cout<< "[ {" << _idle[i].id << "} <ID " <<_idle[i].last_cust_served << "> : Finish: " << _idle[i].finish_time << " ] ";
    std::cout<<std::endl;
}

void Servers::display_idle_times()
{
    int i;
    cout << "|--------|-----------------|--------------------|" << endl;
    cout << left << setw(10) << "| Server |"
         << setw(18) << " Total Idle Time |"
         << setw(21) << " Total Service Time |" << endl;
    cout << "|--------|-----------------|--------------------|" << endl;
    for (i = 0; i < _capacity; i++) {
        cout << left <<"|    " << setw(3) << _idle[i].id + 1 << " |"
             << right <<  setw(16) << _idle[i].total_idle_time << " |"
             << setw(19) << _idle[i].total_service_time << " |" << endl;
    }
    cout << "|--------|-----------------|--------------------|" << endl;
    cout << endl;
}
