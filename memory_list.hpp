#include <iostream>
#include "process.hpp"
#define   BEST_FIT  1
#define   WORST_FIT 2

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

        Memory_List_Node(int s, int x, int time, Process*);
        ~Memory_List_Node();
        inline Process* get_process(){
            return this->process;
        }
        inline int get_end(){
            return this->end;
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
        Memory_List_Node* best_fit(Process* process);
        Memory_List_Node* worst_fit(Process* process);
        int insert_node(Process* proc, int algorithm);
        int delete_node(Process* proc);
        int search_node(int x);
        
        inline Memory_List_Node* get_head(){
            return this->head;
        }
        inline Memory_List_Node* get_tail(){
            return this->tail;
        }
};