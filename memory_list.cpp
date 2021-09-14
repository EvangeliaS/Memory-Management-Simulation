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
    cout << "Memory node constructed: ( " << this->start << " , " << this->end << " )" << endl; 
}

Memory_List_Node::~Memory_List_Node(){
    delete this->process;
    this->process = NULL;
    this->next = NULL;
    this->prev = NULL;
}
void Memory_List_Node::print(){
    //print process
    cout << "( " << this->start << " , " << this->end << " )";
} 
Memory_List::Memory_List(int size){
    this->list_size = size;
    this->head = NULL;
    this->tail = NULL;
}

Memory_List::~Memory_List(){
    Memory_List_Node* prev = this->head;
    Memory_List_Node* temp = prev->next;

    while(temp!=NULL){
        delete prev;
        prev = temp;
        temp = temp->next;
    }
    delete prev;
    this->head = NULL;
    this->tail = NULL;
}

int Memory_List::insert_to_memory(Process* proc, Memory_List_Node* algorithm_node){
    if(algorithm_node!=NULL){
        Memory_List_Node* prev = algorithm_node;
        if(algorithm_node->get_end()+1+proc->get_size()>=this->list_size){  //checks if the end of the node is bigger or equal to the end of the memory
            return -1;
        }
        Memory_List_Node* new_node = new Memory_List_Node(proc->get_size(), algorithm_node->get_end()+1, ptime, proc);
        new_node->next = prev->next;
        new_node->prev = prev;
        if(prev->next!=NULL){
            prev->next->prev = new_node;
            prev->next = new_node;
        }
        else{
            prev->next = new_node;
        }
        return 0;
    }
    else{
        //there was no space in memory
        //cout << "No space available or item already in list . " << endl;
        return -1;
    }
}

int Memory_List::delete_node(Process* proc){
    
}

void Memory_List::display(){
    Memory_List_Node* current = this->head;
    while(current != NULL){
        current->print();
        cout << '\t';
        current = current->next;
    }
}

Memory_List_Node* best_fit(Process* process, Pending_Processes_List* L, Memory_List* memory){
    if(memory->is_empty()){
        memory->init_head(new Memory_List_Node(process->get_size(), 0, ptime, process));
        return memory->get_head();
    }
    Memory_List_Node* temp = memory->get_head();
    if(temp->next!=NULL){
        int best_fit_empty_block = temp->next->get_start() - temp->get_end() - 1;
        while(temp!=NULL && temp->next!=NULL){
            if(((temp->next->get_start() - temp->get_end() - 1) >= process->get_size()) && (temp->next->get_start() - temp->get_end() - 1) <= best_fit_empty_block){
                best_fit_empty_block = temp->next->get_start() - temp->get_end() - 1;
            }
            temp = temp->next;
        }
        if(best_fit_empty_block < process->get_size()){
            cout << "There is not available space in the memory. Pushing process in the Pending Processes List..." << endl;
            L->append_process(process);
            return NULL;
        }
        if(temp!=NULL){
            return temp;
        }
        return NULL;
    }
    else{
        return temp;
    } 
    
}

Memory_List_Node* worst_fit(Process* process, Pending_Processes_List* L, Memory_List* memory){
    if(process->get_size() >= memory->get_listSize()){
        return NULL;
    }
    if(memory->is_empty()==true && process->get_size() < memory->get_listSize()){
        process->print() ;
        memory->init_head(new Memory_List_Node(process->get_size(), 0, ptime, process));
        return NULL;
    }
    //set tail again
    Memory_List_Node* current = memory->get_head();
    while(current->next!=NULL){
        current = current->next;
    }
    memory->set_tail(current);

    Memory_List_Node* temp = memory->get_head();
    if(temp->next!=NULL){
        int biggest_empty_block = temp->next->get_start() - temp->get_end() - 1;
        while(temp!=NULL && temp->next!=NULL){
            if(biggest_empty_block < temp->next->get_start() - temp->get_end() - 1){
                biggest_empty_block = temp->next->get_start() - temp->get_end() - 1;
            }
            temp = temp->next;
        }
        if(biggest_empty_block < process->get_size() && memory->get_tail()->get_end() + process->get_size() >=memory->get_listSize()){
            cout << "There is not available space in the memory. Pushing process in the Pending Processes List..." << endl;
            L->append_process(process);
            return NULL;
        }
        if(temp!=NULL){
            return temp;
        }
        return NULL;
    }
    else{
        return temp;
    } 
}
