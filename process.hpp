#ifndef __PROCESS__
#define __PROCESS__

#include "functions.hpp"

using namespace std;

int set_id();

class Process{
     private:
        int id;
        int size;
        int lifetime;
        int start_time;
        int execution_time; //counter 
        bool pending; //if the process is pending in the l list the variable is 1, if 0 the process is in the memory
    public:
        Process* next; //for the pending processes list
        Process(int size, int lifetime, int id);
        ~Process();
        void print();
        string print_to_filename();
        string copy_details();
        inline void start_process(int time){
            this->start_time = time;
            this->pending = false;
        }
        inline int get_process_id(){
            return this->id;
        }
        inline int get_size(){
            return this->size;
        }
        inline int get_lifetime(){
            return this->lifetime;
        }
        inline bool get_pending(){
            return this->pending;
        }
        inline int get_start_time(){
            return this->start_time;
        }
};

class Pending_Processes_List{   //aka L singly linked list
    private:
        Process* head;
        Process* tail;
    public:
        Pending_Processes_List();
        ~Pending_Processes_List();
        int append_process(Process*);
        void printList();
        Process* pop_process(); //returns and removes the first process in the list(fifo)
        inline Process* get_head(){
            return this->head;
        }
        inline Process* get_tail(){
            return this->tail;
        }

};

Process* create_process(char* process);
Process* process_generator(int t,int T, int lo, int hi);

#endif
