#include <iostream>
#include "process.hpp"

using namespace std;

static int ID = 45672;

int set_id(){
    return ID++;
}

Process::Process(int s, int life,int id){
    this->id = id;
    this->lifetime = life;
    this->size = s;
    this->pending = true;
    this->next = NULL;
    this->start_time = 0;
    this->stop_time = 0;
    this->birth_time = 0;
}

Process::~Process(){

}

void Process::print(){
    cout << this->id << " ( " << this->size << " ) " << this->lifetime << " start_time: " << this->start_time;
}

string Process::print_to_filename(){
    string data;
    data = " id: ";
    data = to_string(this->id);
    data+= " size: ";
    data+= to_string(this->size);
    data+= " lifetime: ";
    data+= to_string(this->lifetime);
    data+= " Start time: ";
    data+=to_string(this->start_time);
    return data;
}

string Process::copy_details(){
    string data;
    data = "id- ";
    data = to_string(this->id);
    data+= "-";
    data+= to_string(this->size);
    data+= "-";
    data+= to_string(this->lifetime);
    data+= "-";
    data+= to_string(this->birth_time);
    return data;
}


Pending_Processes_List::Pending_Processes_List(){
    this->head = NULL;
    this->tail = NULL;
}

Pending_Processes_List::~Pending_Processes_List(){
    if(head==NULL){
        return;
    }
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
        //cout << "Process: " << new_node->get_process_id()  << " added in Pending Processes as head. "<< endl; 
        return 0;
    }
    if(head->next==NULL){
        head->next = new_node;
        tail = new_node;
        //cout << "Process: " << new_node->get_process_id()  << " added in Pending Processes. "<< endl; 
        return 0;
    }
    tail->next = new_node;
    tail = new_node;
    //cout << "Process: " << new_node->get_process_id()  << " added in Pending Processes. "<< endl; 
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

Process* create_process(char* process){
    Process* proc = NULL;
    char * token1 = strtok(process,"-");
    int count1 = 0;
    string id, size, lifetime, birth;
    while(token1){
        if(count1==0){
            string line(token1);
            id.assign(line);
            //cout << "id " << id << endl;
        }
        else if(count1==1){
            string line(token1);
            size.assign(line);

            //cout << "size " << size << endl;
        }
        else if(count1==2){
            string line(token1);
            lifetime.assign(line);

            //cout << "lifetime " << lifetime << endl;
        }
        else if(count1==3){
            string line(token1);
            birth.assign(line);
        }
        count1++;
        token1 = strtok(NULL,"-");
    }
    proc = new Process(stoi(size), stoi(lifetime), stoi(id));
    proc->set_birth_time(stoi(birth));
    return proc;
}

Process* process_generator(int t,int T, int lo, int hi, int birth){
    int lifetime = Exponential_distribution(T);
    int size = Uniform_distribution(lo, hi);
    if(lifetime>0 && size>0){
        Process* process = new Process(size,lifetime, set_id());
        process->set_birth_time(birth);
        return process;
    }
        
    else{
        Process* process = new Process(size +2 ,lifetime +1 , set_id());
        process->set_birth_time(birth);
        return process;
    }
}
