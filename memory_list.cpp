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

int Memory_List::best_fit(Process* proc){
}

int Memory_List::worst_fit(Process* proc){

}

int Memory_List::insert_node(Process* proc, int algorithm){
    Memory_List_Node* temp = this->head;
    if(algorithm == BEST_FIT){
        if(head==NULL){
            head = new Memory_List_Node(proc->get_size(), best_fit(proc), ptime, proc);
            tail = head;
            return 0;
        }
    }
    if(algorithm == WORST_FIT){
        if(head==NULL){
            head = new Memory_List_Node(proc->get_size(), worst_fit(proc), ptime, proc);
            tail = head;
            return 0;
        }
            
    }
    else{
        return -1;
    }
    return -1;
}