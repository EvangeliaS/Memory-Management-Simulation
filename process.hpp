#include <iostream>

using namespace std;

static int ID = 45672;

class Process{
     private:
        int id;
        int size;
        int lifetime;
        int start_time;
        bool pending; //if the process is pending in the l list the variable is 1, if 0 the process is in the memory
    public:
        Process* next; //for the pending processes list
        Process(int s, int life);
        ~Process();
        inline void start_process(int time){
            this->start_time = time;
            this->pending = false;
        }
        inline void set_id(){
            this->id = ID++;
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
};

class Pending_Processes_List{   //aka L singly linked list
    private:
        Process* head;
        Process* tail;
    public:
        Pending_Processes_List();
        ~Pending_Processes_List();
        int append_process(Process*);
        Process* pop_process(); //returns and removes the first process in the list(fifo)
        inline Process* get_head(){
            return this->head;
        }
        inline Process* get_tail(){
            return this->tail;
        }

};
