#include <iostream>
#include "memory_list.hpp"

using namespace std;

static int ptime = 0; //will fix

Memory_List_Node::Memory_List_Node(int s, int x, int ptime, Process* proc){
    this->size  = s;
    this->start = x;
    this->end   = x+s-1;
    this->process = proc;
    this->process->start_process(ptime);
    this->next = NULL;
    this->prev = NULL;
}

Memory_List_Node::~Memory_List_Node(){
    delete this->process;
    this->process = NULL;
    this->next = NULL;
    this->prev = NULL;
}

Memory_List::Memory_List(){
    this->head = NULL;
    this->tail = NULL;
}

Memory_List::~Memory_List(){
    Memory_List_Node* prev = this->head;
    Memory_List_Node* temp = prev->next;

    while(prev){
        delete prev;
        prev = temp;
        temp = temp->next;
    }
    this->head = NULL;
    this->tail = NULL;
}


Memory_List_Node* best_fit(Process* process, Pending_Processes_List* L, Memory_List* memory){
    if(memory->is_empty()){
        memory->init_head(new Memory_List_Node(process->get_size(), 0, ptime, process));
        return memory->get_head();
    }
    else{

    }
}
Memory_List_Node* worst_fit(Process* process, Pending_Processes_List* L, Memory_List* memory){
    if(memory->is_empty()){
        memory->init_head(new Memory_List_Node(process->get_size(), 0, ptime, process));
        return memory->get_head();
    }
}

int Memory_List::insert_to_memory(Process* proc, Memory_List_Node* algorithm_node){
    if(algorithm_node!=NULL && algorithm_node!=this->head){
        Memory_List_Node* prev = algorithm_node;
        Memory_List_Node* new_node = new Memory_List_Node(proc->get_size(), algorithm_node->get_end()+1, ptime, proc);
        new_node->next = prev->next;
        new_node->prev = prev;
        prev->next->prev = new_node;
        prev->next = new_node;
        return 0;
    }
    else if(algorithm_node!=NULL && algorithm_node==this->head){
        //the item was already added in the memory, by the best/worst fit algorithm
        return 1;
    }
    else{
        //there was no space in memory
        return -1;
    }
}