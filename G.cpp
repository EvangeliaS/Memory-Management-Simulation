#include <iostream>
#include "memory_tree.hpp"
#define mutex       0   // semaphore index for mutual exclusion to buffer

#define G_to_M_SEM_SEND     1
#define G_to_M_SEM_RECV     2
#define M_to_G_SEM_SEND     3
#define M_to_G_SEM_RECV     4

using namespace std;

int main(int argc, char* argv[]){ 
    if(argc!=7){
        return -1;
    }
    cout << "Hello from G" << endl;
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

    semid = sem_create(5);  //create semaphore set 

    printf("Semaphore id is: %d\n", semid);

    sem_init(semid, mutex, 1);
    sem_init(semid, G_to_M_SEM_SEND, 1);
    sem_init(semid, G_to_M_SEM_RECV, 0);
    sem_init(semid, M_to_G_SEM_SEND, 0);
    sem_init(semid, M_to_G_SEM_RECV, 0);

    mem = (char *)shmat(shmid ,NULL ,0);   //Attach  the  shared  memory  segment
    memset(mem, 0, MEM_SIZE);

    if (mem == (char *) -1){
        perror("Shmat");
        exit(1);
    }
    Process* proc = NULL;
    //int flag = 0;
    int life = 5;
    int size = 10;
    cout << "POISSON " << Poisson_distribution(T) << endl;
    cout << "EXPONENTIAL "<<Exponential_distribution(t) << endl;
    cout << "UNIFORM " << Uniform_distribution(lo,hi) << endl;
    while(D--){
 /*       if(flag==10){
            break;
        }*/
        for(int i = 0; i<100; i++){
            sem_wait(semid, G_to_M_SEM_SEND);   
            //cout << "SIZE IS " << size << endl;
            proc = new Process(size, life, set_id());
            memset(mem, 0, 128);
            read_line(proc->copy_details(), mem);
            //cout << mem << " BY G " << endl;
            size+=20;
            sem_signal(semid, M_to_G_SEM_RECV);
            
            delete proc;

        }
        break;

        //sem_wait(semid, M_to_G_SEM_SEND);
    }

    cout << "BYE G" << endl;
    return 0;
}