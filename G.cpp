#include <iostream>
#include "memory_tree.hpp"
#define G_to_M_SEM_SEND     0
#define M_to_G_SEM_RECV     1

using namespace std;

int main(int argc, char* argv[]){ 
    if(argc!=8){
        return -1;
    }
    int D  = stoi(argv[1]);
    int lo = stoi(argv[2]);
    int hi = stoi(argv[3]);
    int t  = stoi(argv[4]);
    int T  = stoi(argv[5]);
//  int S  = stoi(argv[6]);

    int semid;      //identifier for a semaphore set
    int shmid;      // shared memory segment id
    char* mem;

    shmid = shmget(SHMKEY, MEM_SIZE, 0666|IPC_CREAT);   //create shared memory segment
    
    if(shmid == -1){
        perror("Creation/Shmget\n");
        return 0;
    }
    else{
        printf("G: Allocated memory with identifier %d\n", shmid);
    }

    semid = sem_create(2);  //create semaphore set 

    printf("Semaphore id is: %d\n", semid);

    sem_init(semid, G_to_M_SEM_SEND, 1);
    sem_init(semid, M_to_G_SEM_RECV, 0);

    mem = (char *)shmat(shmid ,NULL ,0);   //Attach  the  shared  memory  segment
    memset(mem, 0, MEM_SIZE);

    if (mem == (char *) -1){
        perror("Shmat");
        exit(1);
    }

    Process* proc = NULL;
    
    int d = 0;
    int time = 0;
    while(d<D){
        d+=time;
        sem_wait(semid, G_to_M_SEM_SEND);   
        time = Poisson_distribution(t);
        proc = process_generator(t,T,lo,hi,d);
        read_line(proc->copy_details(), mem);
        
        sem_signal(semid, M_to_G_SEM_RECV); 
        delete proc;
    }
    sem_wait(semid, G_to_M_SEM_SEND); 
    read_line("$", mem);
    sem_signal(semid, M_to_G_SEM_RECV); 

    return 0;
}