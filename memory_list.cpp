#include <iostream>
#include "memory_list.hpp"

using namespace std;

Memory_List_Node::Memory_List_Node(int s, int x, int y, Process* proc){
    this->size  = s;
    this->start = x;
    this->end   = y;
    this->process = proc;
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