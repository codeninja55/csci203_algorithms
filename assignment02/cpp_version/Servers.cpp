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

// Constructor to create an _idle[] array of int index for idle servers
// and a Server[] array to store each server.
Servers::Servers(unsigned int size, char *name) : _capacity(size), _name(name), _n_idle_servers(0)
{
    _head = _tail = -1;
    _servers = new Server[_capacity];
    _idle = new int[_capacity];

    // loop through and initialise each server to _server[] array and
    // enqueue their index int to the _idle[] FIFO queue
    int i;
    for (i = 0; i < _capacity; i++) {
        Server new_server;
        new_server.idx = i;
        new_server.count = 0;
        new_server.finish_time = new_server.last_ev_time = new_server.total_idle_time = 0;
        enqueue(new_server.idx);
        _servers[i] = new_server;
    }
}

// dequeue a server from the next available server from _idle[] queue
// and add the customer to the Server struct from the _server[]
void Servers::add_customer(Customer &c, double start_time,  double finish_time)
{
    int next_avail_idx = dequeue();
    if (next_avail_idx != -1) {
        c.server_idx = next_avail_idx;

        double last_finish_time = _servers[next_avail_idx].finish_time;

        _servers[next_avail_idx].total_idle_time += (last_finish_time - start_time);
        _servers[next_avail_idx].total_service_time += (finish_time - start_time);  // this service time accumulated

        _servers[next_avail_idx].finish_time = finish_time;
        _servers[next_avail_idx].last_ev_time = start_time;
        _servers[next_avail_idx].count++;
    }
}

// implementation for the dequeue of an index int from the _idle[] queue
int Servers::dequeue()
{
    int s_id;
    if (_head == -1) {
        cout << "No Servers Available" << endl;
        return -1;
    } else {
        s_id = _idle[_head];
        _head++;
        if (_head > _tail)
            _head = _tail = -1;
        _n_idle_servers--;
        return s_id;
    }
}

// add the server index int back to the _idle[] FIFO queue
void Servers::remove_customer(int s_idx)
{
    _servers[s_idx].finish_time = 0;
    enqueue(s_idx);  // add server to idle queue
}

// FIFO enqueue implementation for an _idle[] int array of server indexes
void Servers::enqueue(int s_idx)
{
    if (_n_idle_servers == _capacity)
        cout << "Too many servers. \n";
    else {
        if (_head == -1)
            _head = 0;
        _tail++;
        _idle[_tail] = s_idx;
        _n_idle_servers++;
    }
}

// returns whether _idle[] queue is not empty
bool Servers::is_available() { return _n_idle_servers != 0; }

void Servers::display_server_statistics()
{
    int i;
    cout << "Idle times for " << _name << " servers:" << endl;
    cout << "|--------|-----------------|--------------------|" << endl;
    cout << left << setw(10) << "| Server |"
         << setw(18) << " Total Idle Time |"
         << setw(21) << " Total Service Time |" << endl;
    cout << "|--------|-----------------|--------------------|" << endl;
    for (i = 0; i < _capacity; i++) {
        cout << left << setprecision(7) << "|    " << setw(3) << _servers[i].idx + 1 << " |"
             << right << setprecision(7) << setw(16) << _servers[i].total_idle_time << " |"
             << setprecision(7) << setw(19) << _servers[i].total_service_time << " |" << endl;
    }
    cout << "|--------|-----------------|--------------------|" << endl;
    cout << endl;
}
