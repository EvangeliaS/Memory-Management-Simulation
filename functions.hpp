#ifndef __FUNCTIONS__
#define __FUNCTIONS__

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
#include <random>

#define MEM_SIZE    (128*sizeof(char)) // 128 bytes for the string
#define SHMKEY      (key_t)9817       // key value of shared memory segment
#define SEMKEY      (key_t)5423      //key value of semaphore set

using namespace std;

int sem_create(int num_of_semaphores);  //creates the semaphores
void sem_init(int semid, int index, int value); //initializes the semaphores
void sem_signal(int semid, int index);  //V semaphore operation 
void sem_wait(int semid, int index);    //P semaphore operation

int read_line(string line, char mem[]);  //reads message, and copies it in the memory segment
void free_resources(int  shmid , int  semid); //deletes the memory segment and the semaphores
void pass_string(char*string, char dest[]); //the program can pass messages like "RETRY" in the memory

int Poisson_distribution(int t);
int Exponential_distribution(int T);
int Uniform_distribution(int lo, int hi);

#endif