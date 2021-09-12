#include <iostream>

using namespace std;

class Process{
     private:
        int size;
        int lifetime;
        int start_time;
    public:
        Process(int s, int life, int start);
        ~Process();
}

class Memory_Block{
    private:
        int start;
        int end;
        int size;
    public:
        Process* process;
        Memory_Block* next;
        Memory_Block* prev;

        Memory_Block(int s, int x, int y);
        ~Memory_Block();
}

class Memory_List{
    private:
        Memory_Block* head;
        Memory_Block* tail;
    public:
        Memory_List();
        ~Memory_List();
        bool check_empty_block();
        bool spot_empty_block();
        
        inline Memory_Block* get_head(){
            return this->head;
        }
        inline Memory_Block* get_tail(){
            return this->tail;
        }
}