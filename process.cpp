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
    cout << "ID: " << this->id << " ( " << this->size << " ) " << this->lifetime;
}

string Process::copy_details(){
    string data;
    data = "id: ";
    data = to_string(this->id);
    data+= "( ";
    data+= to_string(this->size);
    data+= " )";
    data+= to_string(this->lifetime);
    data+= ".";
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


//Functions for the semaphore operations

int sem_create(int num_of_semaphores){
    int semid; //the id key 
    if((semid = semget(SEMKEY, num_of_semaphores, IPC_CREAT | 0600))<0){   //create semaphore set
        perror("Error in creating semaphore"); // 0600 = read/alter by user
        exit(1);
    }
    return semid;
}

void sem_init(int semid, int index, int value){  // procedure to initialize specified semaphore to given value
   if (semctl (semid, index, SETVAL, value) < 0){  
        perror ("Error in initializing semaphore");
        exit (1);
    }
}

void sem_signal(int semid, int index){  // procedure to perform a V or signal operation on semaphore of given index
   struct sembuf sops[1];  // define operation on semaphore with given index

   sops[0].sem_num = index;// define operation on semaphore with given index
   sops[0].sem_op  = 1;    // add 1 to value for V operation
   sops[0].sem_flg = 0;    // type "man semop" in shell window for details

   if(semop (semid, sops, 1) == -1){
        perror ("error in semaphore operation");
        exit (1);
    }
}

void sem_wait(int semid, int index){    // procedure to perform a P or wait operation on a semaphore of given index 
  struct sembuf sops[1];  // only one semaphore operation to be executed

   sops[0].sem_num = index;// define operation on semaphore with given index
   sops[0].sem_op  = -1;   // subtract 1 to value for P operation
   sops[0].sem_flg = 0;    // type "man semop" in shell window for details

   if(semop (semid, sops, 1) == -1){  
        perror ("error in semaphore operation");
        exit (1);
    }
}

int read_line(string line, char memory[]){
    //string line;
    //getline(cin, line);
    strcpy(memory, line.c_str());
    cout <<  "readline " <<memory << endl;
    return 1;
}

void free_resources(int  shmid , int  semid) {
    if(shmctl(shmid ,IPC_RMID ,NULL)<0){    //  Destroy  the  shared  memory  segment
        perror("shmctl"); 
        exit(1);
    }
    printf("Removed the shared memory segment with identifier %d\n", shmid);

    if(semctl(semid ,0,IPC_RMID ,0)<0){ //  Destroy semaphore set
        perror("semctl"); 
        exit(1);
    }
    printf("Removed semaphore with identifier %d\n", semid);
}

void pass_string(char *string, char dest[]){
    strcpy(dest, string);
}