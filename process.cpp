#include <iostream>
#include "process.hpp"

using namespace std;

Process::Process(int s, int life){
    this->set_id();
    this->lifetime = life;
    this->size = s;
    this->pending = true;
    this->next = NULL;
}

Process::~Process(){

}

void Process::print(){
    cout << "ID: " << this->id << " ( " << this->size << " ) ";
}

Pending_Processes_List::Pending_Processes_List(){
    this->head = NULL;
    this->tail = NULL;
}

Pending_Processes_List::~Pending_Processes_List(){
    Process* temp = this->head;
    Process* next = temp->next;
    while(next!=NULL){
        delete temp;
        temp = next;
        next = next->next;
    }
    delete temp;
    this->head = NULL;
}

int Pending_Processes_List::append_process(Process* new_node){
    if(head==NULL){
        head = new_node;
        tail = head;
        cout << "Process: " << new_node->get_process_id()  << " added in Pending Processes as head. "<< endl; 
        return 0;
    }
    if(head->next==NULL){
        head->next = new_node;
        tail = new_node;
        cout << "Process: " << new_node->get_process_id()  << " added in Pending Processes. "<< endl; 
        return 0;
    }
    tail->next = new_node;
    tail = new_node;
    cout << "Process: " << new_node->get_process_id()  << " added in Pending Processes. "<< endl; 
    return 0;

}
Process* Pending_Processes_List::pop_process(){
    Process* temp = this->head;
    head = head->next;
    return temp;
}

void Pending_Processes_List::printList(){
    cout << "Pending Processes: ";
    Process* temp = this->head;
    while(temp != NULL){
        temp->print();
        temp = temp->next;
    }
}