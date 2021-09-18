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
    int flag = 0;
    char temp[128];
    Process* new_proc = NULL;

    Memory_List* memory = new Memory_List(S);
   // Memory_Tree* tree = new Memory_Tree(list_size);
    Pending_Processes_List* L = new Pending_Processes_List();
    int size = 10;
    Process* proc , *proc1, *proc2, *proc3, *proc4 = NULL;
    int life = 2;
    //proc = new Process(size, life);
    //memory->insert_to_memory(proc, best_fit(proc, L, memory, false));

    for(int i = 0; i<10; i++){
        life++;
        size+=20;
        proc1 = new Process(size, life);
        //tree->insert_process(proc1, buddy_algorithm(proc1, tree), L);
        memory->insert_to_memory(proc1, best_fit(proc1, L, memory, false));
        cout << endl;
    }

    memory->delete_node_by_position(250);
    memory->display();
    cout << endl;
    memory->delete_node_by_position(360);

    memory->display();
    L->printList();
    cout << endl;
    while(1){
        //cout << "hello from m" << endl;
        
        sem_wait(semid, M_to_G_SEM_RECV);
       
        //sem_wait(semid, mutex);

        //sem_signal(semid, M_to_G_SEM_SEND);
        //cout << "recv from m: " ;
        memset(temp, 0, 128);
        pass_string(mem, temp);
    
        if(flag){
            new_proc = create_process(temp);
            cout << new_proc << endl;
            cout << "HELLO " << flag;
            new_proc->print();
        }
        
        sem_signal(semid, G_to_M_SEM_SEND);
        flag++;
      if(flag==10){
            break;
        }
    }
    cout << "BYE M" << endl;
    delete memory;
    delete L;
    return 0;
}