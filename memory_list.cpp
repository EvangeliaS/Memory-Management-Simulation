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
    cout << "Delete node with process: ";
    this->process->print();
    cout << endl;
    delete this->process;
    this->process = NULL;
    this->next = NULL;
    this->prev = NULL;
}
void Memory_List_Node::print(){
    //print process
    cout << "( " << this->start << " , " << this->end << " )";
    this->process->print();
} 
Memory_List::Memory_List(int size){
    this->list_size = size;
    this->head = NULL;
    this->tail = NULL;
    cout << "Memory List constructed" << endl;
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
        if((algorithm_node->get_end()+1+proc->get_size())>=this->list_size){  //checks if the end of the node is bigger or equal to the end of the memory
            //cout << algorithm_node->get_end() << "   " << proc->get_size() << endl;
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
    Memory_List_Node* current = NULL; 
    if((current = search_node_by_process(proc))==NULL){
        return -1;
    }
    current->prev->next = current->next;
    if(current->next->prev!=NULL){
        current->next->prev = current->prev;
    }
    cout << " Process: " << current->get_process()->get_process_id() << endl;
    delete current;
    return 0;
}

int Memory_List::delete_node_by_position(int x){
    Memory_List_Node* current = NULL; 
    if((current = search_node_by_position(x))==NULL){
        return -1;
    }
    current->prev->next = current->next;
    if(current->next->prev!=NULL){
        current->next->prev = current->prev;
    }
    cout << " Process: " << current->get_process()->get_process_id() << endl;
    delete current;
    return 0;
}

Memory_List_Node* Memory_List::search_node_by_process(Process* process){
    Memory_List_Node* current = this->head;
    while(current!=NULL){
        if(current->get_process()==process){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Memory_List_Node* Memory_List::search_node_by_position(int position){
    Memory_List_Node* current = this->head;
    while(current!=NULL){
        if(current->get_start()==position){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void Memory_List::display(){
    Memory_List_Node* current = this->head;
    while(current != NULL){
        current->print();
        cout << '\t';
        current = current->next;
    }
}

Memory_List_Node* best_fit(Process* process, Pending_Processes_List* L, Memory_List* memory, bool pending){
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
        int best_fit_empty_block = temp->next->get_start() - temp->get_end() - 1;
        Memory_List_Node* best_fit = temp;
        while(temp!=NULL && temp->next!=NULL){
            if((temp->next->get_start() - temp->get_end() - 1 >= process->get_size()) && ((temp->next->get_start() - temp->get_end() - 1 <= best_fit_empty_block) || best_fit_empty_block==0)){
                best_fit_empty_block = temp->next->get_start() - temp->get_end() - 1;
                best_fit = temp;
                cout <<"New best is " << best_fit->next->get_start() -  best_fit->get_end()  -1  << endl;
            }
            temp = temp->next;
        }
        if((best_fit_empty_block < process->get_size()) && (memory->get_tail()->get_end() + process->get_size() >= memory->get_listSize())){
            //cout << "There is not available space in the memory. Pushing process in the Pending Processes List..." << endl;
            if(pending==true){
                return NULL;
            }
            L->append_process(process);
            return NULL;
        }
        else if(best_fit_empty_block < process->get_size() &&  ((memory->get_tail()->get_end() + process->get_size()) < memory->get_listSize())){
            return temp; //last node
        }
        else{
            return best_fit;
        }

        return NULL;
    }
    else{
        return temp;
    } 
    
}

Memory_List_Node* worst_fit(Process* process, Pending_Processes_List* L, Memory_List* memory, bool pending){
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
        Memory_List_Node* biggest = temp;
        while(temp!=NULL && temp->next!=NULL){
            if(biggest_empty_block < temp->next->get_start() - temp->get_end() - 1){
                biggest_empty_block = temp->next->get_start() - temp->get_end() - 1;
                biggest = temp;
                cout <<"New biggest is " << biggest->next->get_start() -  biggest->get_end()  -1  << endl;
            }
            temp = temp->next;
        }
        if((biggest_empty_block < process->get_size()) && ((memory->get_tail()->get_end() + process->get_size()) >=memory->get_listSize())){
            cout << "There is not available space in the memory. Pushing process in the Pending Processes List..." << endl;
            if(pending==true){
                return NULL;
            }
            L->append_process(process);
            return NULL;
        }
        else if(biggest_empty_block < process->get_size() &&  ((memory->get_tail()->get_end() + process->get_size()) < memory->get_listSize())){
            return temp; //last node
        }
        else{
            return biggest;
        }
        return NULL;
    }
    else{
        return temp;
    } 
}


int add_pending_process(Memory_List* memory, Pending_Processes_List* L, int algorithm){
    Process* process = L->get_head();
    if(process == NULL){
        return -1;
    }
    if(algorithm==BEST_FIT){
        if((memory->insert_to_memory(process, best_fit(process, L, memory, true)))==0){   
            process = L->pop_process();
        }
    }
    else if(algorithm==WORST_FIT){
        if((memory->insert_to_memory(process, worst_fit(process, L, memory, true)))==0){   
            process = L->pop_process();
        }
    }
    else{
        return -1;
    }
    return 0;
}
