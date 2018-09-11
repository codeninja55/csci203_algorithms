/*********************************************************************
* CSCI203 - Assignment 02
* ass2.cpp - C++ main() driver for implementation of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.11
*********************************************************************/

#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "EventQueue.h"
#include "ServerQueue.h"
#include "Servers.h"
using namespace std;

/*====================| MACRO DEFINITIONS |====================*/
#define BUFFER_SZ 50
#define PARENT(i) ( (i-1) / 2 )
#define LEFT(i) ( (i * 2) + 1 )
#define RIGHT(i) ( (i * 2) + 2 )

int main(int argc, const char* argv[])
{
    char filename[BUFFER_SZ];
    ifstream fin;

    if (argc == 2)  // arg passed
        strncpy(filename, argv[1], BUFFER_SZ);
    else {
        cout << "Input file name >> ";
        cin.getline(filename, BUFFER_SZ);
    }

    fin.open(filename);

    if (!fin.good()) {
        cout << "[!!] Error: Failed to open file " << filename << "\nExiting...\n";
        return -1;
    }


    // Initialise servers
    int prim_servers, sec_servers;
    fin >> prim_servers >> sec_servers;

    Servers primary_servers = Servers(prim_servers);
    Servers secondary_servers = Servers(sec_servers);
    // Initialise queues
    ServerQueue prim_server_q = ServerQueue(1000);
    ServerQueue sec_server_q = ServerQueue(1000);
    EventQueue event_q = EventQueue(2000);

    bool cust_arrival_flag = true;

    Customer new_cust;
    fin >> new_cust.arrival_time >> new_cust.prim_service_duration >> new_cust.sec_service_duration;
    event_q.add_event(eCustomerArrived, new_cust.arrival_time, new_cust);
    Time time = 0;

    // Main event loop
    do {
        // break loop if 0, 0, 0 from read
        Event ev = event_q.extract_next_event();
        time += ev.event_time;
        switch (ev.type) {
            case eCustomerArrived:
                if (primary_servers.is_available()) {
                    // TODO: check waiting time
                    Time ev_time = time + ev.customer.arrival_time + ev.customer.prim_service_duration;
                    event_q.add_event(eCustPrimaryFinished, ev_time, ev.customer );

                    Customer ca_cust;
                    fin >> ca_cust.arrival_time >> ca_cust.prim_service_duration >> ca_cust.sec_service_duration;

                    if (ca_cust.arrival_time == 0 && ca_cust.prim_service_duration == 0) {
                        cust_arrival_flag = false;
                        cout << ev.event_time << endl;
                    } else {
                        event_q.add_event(eCustomerArrived, ca_cust.arrival_time, ca_cust );
                    }
                } else {
                    prim_server_q.enqueue(ev.customer);
                }
                break;
            case eCustPrimaryFinished:
                primary_servers.remove_customer(ev.customer.server_id);

                // TODO: do service time stats

                if (secondary_servers.is_available()) {
                    // TODO: Need to check for waiting times
                    // arrival_time, waiting_prim_time, prim_service_time, waiting_sec_time, sec_service_time
                    Time ev_time = time + ev.event_time + ev.customer.sec_service_duration;
                    event_q.add_event(eCustSecondaryFinished, ev_time, ev.customer );
                } else {
                    sec_server_q.enqueue(ev.customer);
                }
                break;
            case eCustSecondaryFinished:
                secondary_servers.remove_customer(ev.customer.server_id);
                // TODO: do service time stats
                break;
        }

        if (!sec_server_q.is_empty() && secondary_servers.is_available()) {
            Customer next_sec_cust = sec_server_q.dequeue();
            // TODO: Need to check for waiting times
            Time ev_time = time + next_sec_cust.arrival_time +
                            next_sec_cust.prim_service_duration +
                            next_sec_cust.sec_service_duration;

            event_q.add_event(eCustSecondaryFinished, ev_time, next_sec_cust);

            // TODO: do FIFO waiting time stats
        }

        if (!prim_server_q.is_empty() && primary_servers.is_available()) {
            Customer next_prim_cust = prim_server_q.dequeue();
            // TODO: Need to check for waiting times
            Time ev_time = time + next_prim_cust.arrival_time +
                            next_prim_cust.prim_service_duration +
                            next_prim_cust.sec_service_duration;
            event_q.add_event(eCustPrimaryFinished, ev_time, next_prim_cust);

            // TODO: do FIFO waiting time stats
        }

    } while (!event_q.more_events() && cust_arrival_flag);

    event_q.display();

    return 0;
}

