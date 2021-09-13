#include <iostream>
#include "process.hpp"

using namespace std;

Process::Process(int s, int life){
    this->set_id();
    this->lifetime = life;
    this->size = s;
    this->pending = true;
}

Process::~Process(){

}

Pending_Processes_List::Pending_Processes_List(){
    this->head = NULL;
    this->tail = NULL;
}

Pending_Processes_List::~Pending_Processes_List(){
    this->head = NULL;
}

int Pending_Processes_List::add_process(Process* new_node){
    if(head==NULL){
        head = new_node;
        head->next = NULL;
        tail = new_node;
        tail->next = NULL;
        return 0;
    }
    if(head->next==NULL){
        head->next = new_node;
        tail = new_node;
        tail->next = NULL;
        return 0;
    }
    tail->next = new_node;
    new_node = tail;
    tail->next = NULL;
    return 0;

}
Process* Pending_Processes_List::pop_process(){
    Process* temp = this->head;
    head = head->next;
    return temp;
}