#include <iostream>
#include "memory_tree.hpp"
#define G_to_M_SEM_SEND     1
#define G_to_M_SEM_RECV     2
#define M_to_G_SEM_SEND     3
#define M_to_G_SEM_RECV     4


using namespace std;

int main(int argc, char* argv[]){ 
    if(argc!=7){
        return -1;
    }
    cout << "Hello from M" << endl;
    int D  = stoi(argv[1]);
    int lo = stoi(argv[2]);
    int hi = stoi(argv[3]);
    int t  = stoi(argv[4]);
    int T  = stoi(argv[5]);
    int S  = stoi(argv[6]);

    int semid;      //identifier for a semaphore set
    int shmid;      // shared memory segment id
    char* mem;

    if ((semid = semget(SEMKEY, 5, 0600))< 0){
        perror("semget"); 
        exit(1); 
    }

    shmid = shmget(SHMKEY, MEM_SIZE, 0666);   //create shared memory segment

    if(shmid == -1){
        perror("Creation/Shmget\n");
        return 0;
    }
    else{
        printf("M: Memory with identifier %d\n", shmid);
    }

    mem = (char *)shmat(shmid ,NULL ,0);   //Attach  the  shared  memory  segment
    memset(mem, 0, MEM_SIZE);

    if (mem == (char *) -1){
        perror("Shmat");
        exit(1);
    }
    char temp[128];
    while(1){
        //cout << "hello from m" << endl;
        sem_wait(semid, M_to_G_SEM_RECV);
        //sem_wait(semid, mutex);

        //sem_signal(semid, M_to_G_SEM_SEND);
        cout << "recv from m: " ;

        pass_string(mem, temp);
        cout << mem << "pppppppppppp" << endl;
/*        cout << "llllllllllllll " << temp << endl;

        if(temp!=" "){
            cout << "lol" <<endl;
        Process* new_proc = create_process(temp);
        //new_proc->print();
        }*/
        cout << "lol m wtf" << endl;
        sem_signal(semid, G_to_M_SEM_SEND);

    }
    return 0;
}