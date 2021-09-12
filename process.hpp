#include <iostream>

using namespace std;

class Process{
     private:
        int id;
        int size;
        int lifetime;
        int start_time;
        bool pending; //if the process is pending in the l list the variable is 1, if 0 the process is in the memory
    public:
        Process* next; //for the pending processes list
        Process(int s, int life, int start);
        ~Process();
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

class Pending_Processes_List{   //aka L
    private:

    public:
};
