/*********************************************************************
* CSCI203 - Assignment 02
* ass2.cpp - C++ main() driver and class implementations of Assignment 02
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.18
*********************************************************************/
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

/*====================| MACRO DEFINITIONS |====================*/
#define BUFFER_SZ 50
#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )
#define PARENT(i) ( (i-1) / 2 )
#define LEFT(i) ( (i * 2) + 1 )
#define RIGHT(i) ( (i * 2) + 2 )

/*====================| STRUCT AND ENUM DEFINITIONS |====================*/
enum EventType { eCustomerArrived = 0, eCustPrimaryFinished = 1, eCustSecondaryFinished = 2 };

struct Customer {
    double arrival_time, p_service_duration, s_service_duration;
    double wait_duration, cust_queued_time;
    int server_idx;
};

struct Event {
    EventType type;  // type of event
    double ev_time;  // snapshot time of event to process
    Customer cust;  // customer for event
};

struct Server {
    int idx;
    // stats
    int count;
    double finish_time, total_idle_time, total_service_time;
};

typedef Server Server;
typedef Event Event;
typedef Customer Customer;

/*====================| CLASS DEFINITIONS |====================*/
class EventQueue {
    public:
        explicit EventQueue(int size);  // initialiser
        void add_event(EventType ev_type, double ev_time, Customer &cust);
        Event extract_next_event();
        bool more_events();
    private:
        void min_heapify(int i);
        int _n_events, _capacity;
        Event *_q;
};

class Servers {
    public:
        explicit Servers(unsigned int size, char *name);  // main initialiser
        void add_customer(Customer &c, double start_time, double finish_time);
        void remove_customer(int s_idx);  // enqueue server
        void enqueue(int s_idx);
        int dequeue();  // dequeue server
        bool is_available();
        void display_server_statistics(double last_service_time);
    private:
        Server *_servers;
        int *_idle;
        char *_name;
        int _head, _tail;
        unsigned int _capacity, _n_idle_servers;
};

class ServerQueue {
    public:
        explicit ServerQueue(int size, char *name);
        void add_waiting_customer(Customer &c, double ev_time);
        void enqueue(Customer &c);
        Customer dequeue();
        Customer next_waiting_customer(double ev_time);
        void calculate_average_queue_len(double ev_time);
        bool is_empty();
        int get_max_q_len() const;
        double get_avg_queue_len() const;
        double get_sum_q_len() const;
        double get_sum_q_len_time() const;
    private:
        int _head, _tail, _capacity, _n_customers, _max_q_len;
        double _sum_q_len, _sum_q_len_time, _prev_q_len_change_time;
        Customer *serv_q;
        char *_name;
};

/*====================| FUNCTION PROTOTYPES |====================*/
void print_statistics(Servers, Servers, ServerQueue, ServerQueue);
void swap(Event *A, Event *B);

/*====================| GLOBAL VARIABLE DEFINITIONS |====================*/
int n_total_cust;
double last_service_completed, total_service_time, p_server_q_wait_times, s_server_q_wait_times;
int p_server_n_cust, s_server_n_cust;


int main(int argc, const char* argv[])
{
    cout<<"Author: Dinh Che (dbac496 | codeninja55)"<<endl;

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
    unsigned int n_p_servers, n_s_servers;
    fin >> n_p_servers >> n_s_servers;
    char p_name[] = "Primary";
    char s_name[] = "Secondary";
    Servers p_servers = Servers(n_p_servers, p_name);  // wrapper class for array of primary server structs
    Servers s_servers = Servers(n_s_servers, s_name);  // wrapper class for array of secondary server structs

    // Initialise queues
    ServerQueue p_server_q = ServerQueue(2000, p_name);  // FIFO queue - waiting to be served by a p server
    ServerQueue s_server_q = ServerQueue(2000, s_name);  // FIFO queue - waiting to be served by a s server
    EventQueue event_q = EventQueue(200);  // Priority queue implemented as a heap with an array - main event queue

    // Statistic counters initialisers
    n_total_cust = 0;
    last_service_completed = total_service_time = p_server_q_wait_times = s_server_q_wait_times = 0;
    p_server_n_cust = s_server_n_cust = 0;

    bool cust_arrival_flag = true;  // flag to be changed if no other events to read from file

    // Read first customer from file
    Customer first_cust;
    first_cust.wait_duration = 0;
    fin >> first_cust.arrival_time
        >> first_cust.p_service_duration
        >> first_cust.s_service_duration;

    // add the first customer to the event_q
    event_q.add_event(eCustomerArrived, first_cust.arrival_time, first_cust);

    // main simulation event loop
    while (event_q.more_events()) {  // check if there are any more events waiting to be processed
        // the top priority event based on (min) event_time when added
        Event ev = event_q.extract_next_event();

        /* Events are either:
         *  eCustomerArrived
         *      - customer is served by a p server if available, and event_time is set to when service complete
         *      - customer is put in a p server queue if no server available, time they went in queue stored
         *  eCustpFinished - customer has finished with p server
         *      - customer is served by a s server if available, and event_time is set to when service completed
         *      - customer is put in a s server FIFO queue if no server available, time they went in queue stored
         * eCustSecondaryFinished - customer has finished with a s server and being served
         * */
        switch (ev.type) {
            case eCustomerArrived:
                // read next customer from file and put them in event_q on arrival_time
                if (cust_arrival_flag) {
                    Customer next_read_cust;
                    fin >> next_read_cust.arrival_time
                        >> next_read_cust.p_service_duration
                        >> next_read_cust.s_service_duration;

                    // break loop if 0, 0, 0 reached in txt file and close file
                    if (next_read_cust.arrival_time == 0.0 && next_read_cust.p_service_duration == 0.0) {
                        cust_arrival_flag = false;
                        fin.close();
                    } else {
                        next_read_cust.wait_duration = 0;
                        event_q.add_event(eCustomerArrived, next_read_cust.arrival_time, next_read_cust);
                    }
                }

                if (p_servers.is_available()) {  // p server in array to be dequeue'd
                    double p_service_finish_time = ev.cust.arrival_time + ev.cust.p_service_duration;
                    p_servers.add_customer(ev.cust, ev.ev_time, p_service_finish_time);
                    event_q.add_event(eCustPrimaryFinished, p_service_finish_time, ev.cust);
                } else {
                    ev.cust.cust_queued_time = ev.ev_time;
                    p_server_q.add_waiting_customer(ev.cust, ev.ev_time);
                    p_server_n_cust++;
                }

                break;

            case eCustPrimaryFinished:
                // free up a server in primary server array
                p_servers.remove_customer(ev.cust.server_idx);

                total_service_time += (ev.cust.p_service_duration + ev.cust.wait_duration);  // wait_duration only for p

                if (s_servers.is_available()) {
                    double s_service_finish_time = ev.ev_time + ev.cust.s_service_duration;
                    s_servers.add_customer(ev.cust, ev.ev_time, s_service_finish_time);
                    event_q.add_event(eCustSecondaryFinished, s_service_finish_time, ev.cust );
                } else {
                    ev.cust.cust_queued_time = ev.ev_time;
                    s_server_q.add_waiting_customer(ev.cust, ev.ev_time);
                    s_server_n_cust++;
                }

                break;

            case eCustSecondaryFinished:
                // free up a server in secondary server array
                s_servers.remove_customer(ev.cust.server_idx);
                n_total_cust++;
                total_service_time += (ev.cust.s_service_duration + ev.cust.wait_duration);

                if (!event_q.more_events()) {
                    last_service_completed = ev.ev_time;
                    p_server_q.calculate_average_queue_len(last_service_completed);
                    s_server_q.calculate_average_queue_len(last_service_completed);
                }

                break;
        }

        // Check if there are any secondary servers available to process
        // someone in queue if there is a queue
        if (!s_server_q.is_empty() && s_servers.is_available()) {
            Customer waiting_cust = s_server_q.next_waiting_customer(ev.ev_time);

            waiting_cust.wait_duration = ev.ev_time - waiting_cust.cust_queued_time;
            double s_server_finish_time = ev.ev_time + waiting_cust.s_service_duration;

            s_servers.add_customer(waiting_cust, ev.ev_time, s_server_finish_time);
            event_q.add_event(eCustSecondaryFinished, s_server_finish_time, waiting_cust);

            s_server_q_wait_times += waiting_cust.wait_duration;  // accumulate waiting time stats
        }

        // Check if there are any primary servers available to process
        // someone in queue if there is a queue
        if (!p_server_q.is_empty() && p_servers.is_available()) {
            Customer waiting_cust = p_server_q.next_waiting_customer(ev.ev_time);

            waiting_cust.wait_duration = ev.ev_time - waiting_cust.cust_queued_time;
            double p_server_finish_time = ev.ev_time + waiting_cust.p_service_duration;

            p_servers.add_customer(waiting_cust, ev.ev_time, p_server_finish_time);
            event_q.add_event(eCustPrimaryFinished, p_server_finish_time, waiting_cust);

            p_server_q_wait_times += waiting_cust.wait_duration;  // accumulate waiting time stats
        }
    }

    print_statistics(p_servers, s_servers, p_server_q, s_server_q);

    cout << "|=======|  Assignment 02 -- Simulation Complete  |=======|" << endl << endl;
    return 0;
}

void print_statistics(Servers p_servers, Servers s_servers, ServerQueue p_server_q, ServerQueue s_server_q)
{
    cout << "\n\n|=======| Assignment 02 -- Simulation Statistics  |=======|" << endl << endl;

    cout << fixed << setprecision(3) << left << setfill('.') << setw(50) << "Number of People Served:" << " "
         << n_total_cust << endl;
    cout << left << setw(50) << "Time Last Service Request Completed:" << " "
         << last_service_completed << endl;
    cout << left << setw(50) << "Total Service Time:" << " "
         << total_service_time << endl;
    cout << left << setw(50) << "Average Total Service Time:" << " "
         << total_service_time / n_total_cust << endl << endl;

    cout << left << setw(50) << "Total Time in Queues:" << " "
         << ((p_server_q_wait_times + s_server_q_wait_times) / (p_server_n_cust + s_server_n_cust))
            * (p_server_n_cust + s_server_n_cust) << endl;
    cout << left << setw(50) << "Average Time Spent in Primary Server Queue:" << " "
         << p_server_q_wait_times / p_server_n_cust << endl;
    cout << left << setw(50) << "Average Time Spent in Secondary Server Queue:" << " "
         << s_server_q_wait_times / s_server_n_cust << endl;
    cout << left << setw(50) << "Average Total Time in Queues:" << " "
            << (p_server_q_wait_times + s_server_q_wait_times) / (p_server_n_cust + s_server_n_cust)
            << endl << endl;

    // TODO
    cout << left << setw(50) << "Average Length of the Primary Server Queue:" << " "
         << p_server_q.get_avg_queue_len() << endl;
    cout << left << setw(50) << "Average Length of the Secondary Server Queue:" << " "
         << s_server_q.get_avg_queue_len() << endl;
    cout << left << setw(50) << "Average Length of the Queues:" << " "
         << (p_server_q.get_sum_q_len() + s_server_q.get_sum_q_len())  /
            (p_server_q.get_sum_q_len_time() + s_server_q.get_sum_q_len_time())
         << endl << endl;

    cout << left << setw(50) << "Max Length of Primary Server Queue:" << " "
         << p_server_q.get_max_q_len() << endl;
    cout << left << setw(50) << "Max Length of Secondary Server Queue:" << " "
         << s_server_q.get_max_q_len() << endl;
    cout << left << setw(50) << "Max Length of Queues:" << " "
         << MAX(p_server_q.get_max_q_len(), s_server_q.get_max_q_len())
         << endl << endl << setfill(' ');

    p_servers.display_server_statistics(last_service_completed);
    s_servers.display_server_statistics(last_service_completed);
}

/*====================| CLASS: Servers IMPLEMENTATION |====================*/
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
        new_server.finish_time = new_server.total_idle_time = 0;
        enqueue(new_server.idx);
        _servers[i] = new_server;
    }
}

// dequeue a server from the next available server from _idle[] queue
// and add the customer to the Server struct from the _server[]
void Servers::add_customer(Customer &c, double start_time,  double finish_time)
{
    // calculate_idle_times(start_time);
    int next_avail_idx = dequeue();
    if (next_avail_idx != -1) {
        c.server_idx = next_avail_idx;

        // stats for each server
        // this service time accumulated
        _servers[next_avail_idx].total_service_time += (finish_time - start_time);
        // last time they served someone minus starting time for this event
        _servers[next_avail_idx].total_idle_time += start_time - _servers[next_avail_idx].finish_time;

        _servers[next_avail_idx].finish_time = finish_time;
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

void Servers::display_server_statistics(double last_service_time)
{
    int i;
    cout << "Statistics for " << _name << " servers:" << endl;
    cout << "|--------|-----------------|--------------------|" << endl;
    cout << left << setw(10) << "| Server |"
         << setw(18) << " Total Idle Time |"
         << setw(21) << " Total Service Time |" << endl;
    cout << "|--------|-----------------|--------------------|" << endl;
    for (i = 0; i < _capacity; i++) {
        // Final update
        _servers[i].total_idle_time += last_service_time - _servers[i].finish_time;

        cout << left << fixed << setprecision(5) << "|    " << setw(3) << _servers[i].idx + 1 << " |"
             << right << setw(16) << _servers[i].total_idle_time << " |"
             << setw(19) << _servers[i].total_service_time << " |" << endl;
    }
    cout << "|--------|-----------------|--------------------|" << endl;
    cout << endl;
}

/*====================| CLASS: ServerQueue IMPLEMENTATION |====================*/
ServerQueue::ServerQueue(int size, char *name) : _capacity(size), _head(-1), _tail(-1), _n_customers(0), _name(name)
{
    _max_q_len = 0;
    _sum_q_len = _sum_q_len_time = _prev_q_len_change_time = 0;
    serv_q = new Customer[_capacity];
}

void ServerQueue::add_waiting_customer(Customer &c, double ev_time)
{
    calculate_average_queue_len(ev_time);
    enqueue(c);
    _max_q_len = MAX(_max_q_len, _n_customers);
}

void ServerQueue::calculate_average_queue_len(double ev_time)
{
    // current_time - previous time length
    double q_len_delta_time = ev_time - _prev_q_len_change_time;  // last time the queue was changed
    _sum_q_len += q_len_delta_time * _n_customers;
    _sum_q_len_time += q_len_delta_time;
    _prev_q_len_change_time = ev_time;  // save the snapshot change time before enqueue/dequeue called
}

void ServerQueue::enqueue(Customer &c)
{
    if (_n_customers == _capacity - 1)
        std::cout << "Enqueue: " << _name << "Server_Q is full." << std::endl;
    else {
        if (_head == -1)
            _head = 0;
        _tail++;
        serv_q[_tail] = c;
        _n_customers++;
    }
}

Customer ServerQueue::next_waiting_customer(double ev_time)
{
    calculate_average_queue_len(ev_time);
    return dequeue();
}

Customer ServerQueue::dequeue()
{
    Customer cust;
    if (_head == -1) {
        std::cout << "Dequeue: " << _name << "_Server_Q is empty." << std::endl;
    } else {
        cust = serv_q[_head];
        _head++;
        if (_head > _tail)
            _head = _tail = -1;
        _n_customers--;
        return cust;
    }
}

int ServerQueue::get_max_q_len() const { return _max_q_len; }

double ServerQueue::get_avg_queue_len() const { return _sum_q_len / _sum_q_len_time; }

double ServerQueue::get_sum_q_len() const { return _sum_q_len; }

double ServerQueue::get_sum_q_len_time() const { return _sum_q_len_time; }

bool ServerQueue::is_empty() { return _head == -1; }

/*====================| CLASS: EventQueue IMPLEMENTATION |====================*/
EventQueue::EventQueue(int size) : _capacity(size), _n_events(0)
{
    _q = new Event[_capacity];
}

void EventQueue::min_heapify(int i)
{
    int smallest = i;

    if (LEFT(i) <= _n_events && _q[LEFT(i)].ev_time < _q[i].ev_time)
        smallest = LEFT(i);

    if (RIGHT(i) <= _n_events && _q[RIGHT(i)].ev_time < _q[smallest].ev_time)
        smallest = RIGHT(i);

    if (smallest != i) {
        swap(&_q[i], &_q[smallest]);
        min_heapify(smallest);
    }
}

void EventQueue::add_event(EventType ev_type, double ev_time, Customer &cust)
{
    if (_n_events == _capacity - 1) {
        std::cout << "Event queue overflow." << std::endl;
        return;
    }

    if (_n_events == (_capacity / 2)) {
        Event *tmp = _q;
        _q = new Event[_capacity * 2];

        int i;
        for (i = 0; i < _capacity; i++) { _q[i] = tmp[i]; }
        delete[] tmp;
    }

    int i = _n_events++;
    Event new_event = { ev_type, ev_time, cust };
    _q[i] =  new_event;

    // Fix min-heap property
    while (i != 0 && _q[PARENT(i)].ev_time > _q[i].ev_time) {
        swap(&_q[i], &_q[PARENT(i)]);
        i = PARENT(i);
    }
}

Event EventQueue::extract_next_event()
{
    if (_n_events <= 0)
        std::cout << "Event Queue underflow."<< std::endl;

    if (_n_events == 1) {
        _n_events--;
        return _q[0];
    }

    Event next = _q[0];
    _q[0] = _q[_n_events - 1];
    _n_events--;
    min_heapify(0);
    return next;
}

bool EventQueue::more_events() { return _n_events > 0; }

/*====================| UTILITY FUNCTION IMPLEMENTATIONS |====================*/
void swap(Event *A, Event *B)
{
    Event temp = *A;
    *A = *B;
    *B = temp;
}
