/*********************************************************************
* CSCI203 - Assignment 02
* ass2.cpp - C++ main() driver for implementation of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.13
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

/*====================| STRUCT AND ENUM DEFINITIONS |====================*/


/*====================| CLASS DEFINITIONS |====================*/


/*====================| CLASS DEFINITIONS |====================*/


/*====================| GLOBAL DEFINITIONS |====================*/
static int GLOBAL_CUST_ID = 1;


int main(int argc, const char* argv[])
{
    cout<<"|===============| CSCI203 Assignment 02 |===============|\n Author: Dinh Che (codeninja55 | dbac496)"<<endl;

    char filename[BUFFER_SZ];
    ifstream fin;

    // Check for any args passed or prompt for filename to be read from
    if (argc == 2)  // arg passed
        strncpy(filename, argv[1], BUFFER_SZ);
    else {  // no arg passed, prompt for filename
        cout << "Input file name >> ";
        cin.getline(filename, BUFFER_SZ);
    }

    // open file to read and check if correctly opened
    fin.open(filename);
    if (!fin.good()) {
        cout << "[!!] Error: Failed to open file " << filename << "\nExiting...\n";
        return -1;
    }

    // Initialise servers from read in file parameters
    int n_p_servers, n_s_servers;
    fin >> n_p_servers >> n_s_servers;
    char p_name[] = "Primary";
    char s_name[] = "Secondary";
    Servers p_servers = Servers(n_p_servers, p_name);
    Servers s_servers = Servers(n_s_servers, s_name);

    // Initialise queues
    ServerQueue p_server_q = ServerQueue(4000, p_name);  // FIFO queue - waiting to be served by a p server
    ServerQueue s_server_q = ServerQueue(4000, s_name);  // FIFO queue - waiting to be served by a s server
    EventQueue event_q = EventQueue(2000);  // Priority queue implemented as a heap with an array - main event queue

    // Statistic counters
    Time total_service_time = 0;
    Time avg_total_service_time = 0;
    Time p_server_q_wait_times = 0;
    Time s_server_q_wait_times = 0;

    bool cust_arrival_flag = true;  // flag to be changed if no other events to read from file

    // Read first customer from file
    Customer first_cust;
    first_cust.id = GLOBAL_CUST_ID++;  // TODO: may not need this later so can remove
    fin >> first_cust.arrival_time
        >> first_cust.p_service_duration
        >> first_cust.s_service_duration;

    // add the first customer to the event_q
    event_q.add_event(eCustomerArrived, first_cust.arrival_time, first_cust);

    // main simulation event loop
    while (event_q.more_events()) {  // check if there are any more events waiting to be processed

        // TODO: Testing
        cout << "\n|=== " << event_q.peek_next_event().ev_time << " ===|\n";
        event_q.display();
        p_servers.display();
        p_server_q.display();
        s_servers.display();
        s_server_q.display();
        cout<<endl;

        // the top priority event based on event_time when added
        Event ev = event_q.extract_next_event();
        cout << "Processing ==> {" << ev.type << "} <ID " << ev.cust.id << "> : Event Time: " << ev.ev_time << endl;

        // read next customer from file and put them in event_q on arrival_time
        if (cust_arrival_flag) {
            Customer next_read_cust;
            fin >> next_read_cust.arrival_time
                >> next_read_cust.p_service_duration
                >> next_read_cust.s_service_duration;

            // break loop if 0, 0, 0 reached in sample.txt and close file
            if (next_read_cust.arrival_time == 0.0 && next_read_cust.p_service_duration == 0.0) {
                cust_arrival_flag = false;
                fin.close();
            } else {
                next_read_cust.id = GLOBAL_CUST_ID++;
                event_q.add_event(eCustomerArrived, next_read_cust.arrival_time, next_read_cust);
            }
        }

        /* Events are either:
         *  eCustomerArrived
         *      - customer is served by a p server if available, and event_time is set to when service complete
         *      - customer is put in a p server queue if no server available, wait duration till next server
         *        available is calculated and stored.
         *  eCustpFinished - customer has finished with p server
         *      - customer is served by a s server if available, and event_time is set to when service completed
         *      - customer is put in a s server FIFO queue if no server available, wait duration till next
         *        server available is calculated and stored.
 *       * eCustSecondaryFinished - customer has finished with a s server and being served
         *      - statistics are calculated
         * */
        switch (ev.type) {
            case eCustomerArrived:

                // p server in _idle[] available to serve next customer
                if (p_servers.is_available()) {

                    Time eCPF_ev_time = ev.cust.arrival_time + ev.cust.p_service_duration;
                    p_servers.add_customer(ev.cust, eCPF_ev_time);
                    event_q.add_event(eCustPrimaryFinished, eCPF_ev_time, ev.cust);

                } else {
                    ev.cust.wait_duration = p_servers.next_server_time() - ev.cust.arrival_time;

                    // TODO: Testing
                    cout << "Waiting in p_Server_Q ==> {" << ev.type << "} : <ID " << ev.cust.id << "> "
                         << ": Event Time: " << ev.ev_time << " : Waiting till: "
                         << ev.ev_time + ev.cust.wait_duration << endl;

                    p_server_q.enqueue(ev.cust);
                }

                break;

            case eCustPrimaryFinished:
                p_servers.remove_customer(ev.cust.server_id);

                // TODO: do service time stats

                if (s_servers.is_available()) {
                    Time eCSF_ev_time = ev.ev_time + ev.cust.s_service_duration;
                    s_servers.add_customer(ev.cust, eCSF_ev_time);
                    event_q.add_event(eCustSecondaryFinished, eCSF_ev_time, ev.cust );
                } else {
                    ev.cust.wait_duration = s_servers.next_server_time() - ev.ev_time;

                    // TODO: Testing
                    cout << "Waiting in Secondary_Server_Q ==> {" << ev.type << "} : <ID "
                         << ev.cust.id << "> " << ": Event Time: " << ev.ev_time << " : Waiting till: "
                         << ev.ev_time + ev.cust.wait_duration << endl;

                    s_server_q.enqueue(ev.cust);
                }

                break;

            case eCustSecondaryFinished:
                s_servers.remove_customer(ev.cust.server_id);

                // TODO: do service time stats
                total_service_time += ev.ev_time;

                break;
        }

        // Check if there are any s servers available to process
        // someone in queue if there is a queue
        if (!s_server_q.is_empty() && s_servers.is_available()) {
            Customer waiting_cust;
            waiting_cust = s_server_q.dequeue();

            // TODO: Testing
            cout << "Secondary_Server_Q ==> <ID " << waiting_cust.id << "> Waited: "
                 << waiting_cust.wait_duration << endl;

            Time s_server_q_ev_time = waiting_cust.arrival_time + waiting_cust.p_service_duration
                    + waiting_cust.wait_duration + waiting_cust.s_service_duration;
            event_q.add_event(eCustSecondaryFinished, s_server_q_ev_time, waiting_cust);

            // TODO: do FIFO waiting time stats
            s_server_q_wait_times += s_server_q_ev_time;
        }

        // Check if there are any p servers available to process
        // someone in queue if there is a queue
        if (!p_server_q.is_empty() && p_servers.is_available()) {
            Customer waiting_cust;
            waiting_cust = p_server_q.dequeue();

            // TODO: Testing
            cout << "p_Server_Q ==> <ID " << waiting_cust.id << "> Waited: "
                 << waiting_cust.wait_duration << endl;

            Time p_server_q_ev_time = waiting_cust.arrival_time + waiting_cust.wait_duration +
                    waiting_cust.s_service_duration;
            event_q.add_event(eCustPrimaryFinished, p_server_q_ev_time, waiting_cust);

            // TODO: do FIFO waiting time stats
            p_server_q_wait_times += p_server_q_ev_time;
        }
    }

    cout << "|===============| Simulation Statistics |===============|" << endl;

    cout << "Total Number of People Served: " << GLOBAL_CUST_ID - 1 << endl;
    cout << "Total p Server Wait Time: " << p_server_q_wait_times << endl;
    cout << "Total Secondary Server Wait Time: " << s_server_q_wait_times << endl;
    cout << "Time Last Service Completed: " << endl;
    cout << "Total Service Time: " << total_service_time << endl;
    cout << "Average Total Service Time: " << total_service_time / (GLOBAL_CUST_ID - 1) << endl;


    /* TODO: Output, to standard output will consist of the following data:
     *  - Number of people served. --> Use the static ID counter
     *  - Time last service request is completed.  -->
     *  - Average total service time.  -->
     *  - Average total time in queue(s). Both overall and separate.  -->
     *  - Average length of queue. For each queue and overall.
     *  - Maximum Length of queue. For each queue and overall.
     *  - Total idle time for each server.
     * */

    cout << "|===============| Assignment 02 Output Complete |===============|" << endl;

    return 0;
}

