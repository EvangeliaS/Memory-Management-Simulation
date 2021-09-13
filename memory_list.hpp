#include <iostream>
#include "process.hpp"

using namespace std;

class Memory_List_Node{
    private:
        int start;
        int end;
        int size;
        Process* process;
    public:
        Memory_List_Node* next;
        Memory_List_Node* prev;

        Memory_List_Node(int s, int x, int y, Process*);
        ~Memory_List_Node();
        inline Process* get_process(){
            return this->process;
        }
};

class Memory_List{
    private:
        Memory_List_Node* head;
        Memory_List_Node* tail;
    public:
        Memory_List();
        ~Memory_List();
        bool check_empty_block();
        bool spot_empty_block();
        int best_fit(Process* process);
        int worst_fit(Process* process);
        int insert_node(Process* proc);
        int delete_node(Process* proc);
        
        inline Memory_List_Node* get_head(){
            return this->head;
        }
        inline Memory_List_Node* get_tail(){
            return this->tail;
        }
};