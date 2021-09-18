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
    int S  = stoi(argv[6]);

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
    Process* proc = new Process(100, 3, set_id());
    proc->print();
    int flag = 0;
    while(1){
        
        sem_wait(semid, G_to_M_SEM_SEND);   
        if(flag==10){
            break;
        }
        //sem_wait(semid, mutex);
        //G create_process
        //G send process

        //cout << "write from g: " ;
        read_line(proc->copy_details(), mem);
        //char* lol = "djhfjkdhjks";
        //strcpy(mem, (char*)lol);
        //cout << "lol g wtf" << mem << endl;

        //sem_signal(semid, mutex);    
        sem_signal(semid, M_to_G_SEM_RECV);
        flag++;
 /*       if(flag==10){
            return 0;
        }*/
        //sem_wait(semid, M_to_G_SEM_SEND);
    }
    delete proc;
    cout << "BYE G" << endl;
    return 0;
}