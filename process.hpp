#ifndef __PROCESS__
#define __PROCESS__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <mutex>
#include <unistd.h>
#include <fstream>

#define MEM_SIZE    (144*sizeof(char)) // 128 bytes for the string and
#define SHMKEY      (key_t)9876       // key value of shared memory segment
#define SEMKEY      (key_t)5432      //key value of semaphore set

using namespace std;

static int ID = 45672;

class Process{
     private:
        int id;
        int size;
        int lifetime;
        int start_time;
        int execution_time; //counter 
        bool pending; //if the process is pending in the l list the variable is 1, if 0 the process is in the memory
    public:
        Process* next; //for the pending processes list
        Process(int size, int lifetime);
        ~Process();
        void print();
        string copy_details();
        inline void start_process(int time){
            this->start_time = time;
            this->pending = false;
        }
        inline void set_id(){
            this->id = ID++;
        }
        inline int get_process_id(){
            return this->id;
        }
        inline int get_size(){
            return this->size;
        }
        inline int get_lifetime(){
            return this->lifetime;
        }
        inline bool get_pending(){
            return this->pending;
        }
};

class Pending_Processes_List{   //aka L singly linked list
    private:
        Process* head;
        Process* tail;
    public:
        Pending_Processes_List();
        ~Pending_Processes_List();
        int append_process(Process*);
        void printList();
        Process* pop_process(); //returns and removes the first process in the list(fifo)
        inline Process* get_head(){
            return this->head;
        }
        inline Process* get_tail(){
            return this->tail;
        }

};

int sem_create(int num_of_semaphores);  //creates the semaphores
void sem_init(int semid, int index, int value); //initializes the semaphores
void sem_signal(int semid, int index);  //V semaphore operation 
void sem_wait(int semid, int index);    //P semaphore operation

int read_line(string line, char mem[]);  //reads message, and copies it in the memory segment
void free_resources(int  shmid , int  semid); //deletes the memory segment and the semaphores
void pass_string(char*string, char dest[]); //the program can pass messages like "RETRY" in the memory, 

#endif
