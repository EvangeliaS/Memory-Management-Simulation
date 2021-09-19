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
//  int lo = stoi(argv[2]);
//  int hi = stoi(argv[3]);
//  int t  = stoi(argv[4]);
//  int T  = stoi(argv[5]);
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
    Pending_Processes_List* L = new Pending_Processes_List();

   // Memory_Tree* tree = new Memory_Tree(list_size);

/*    memory->delete_node_by_position(250);
    memory->display();
    cout << endl;
    memory->delete_node_by_position(360);

    cout << endl;*/
    while(D--){
        sem_wait(semid, M_to_G_SEM_RECV);
        //cout << "D of M " << D << endl;
        memset(temp, 0, 128);
        pass_string(mem, temp);
    
        if(flag){
            new_proc = create_process(temp);
            memory->insert_to_memory(new_proc, worst_fit(new_proc, L, memory, false));           
        }
        
        sem_signal(semid, G_to_M_SEM_SEND);

        flag++;
    }

    //memory->display();
    //cout << endl;
    //L->printList();

    //create log_file.xxx
    pid_t pid = getpid();
    string log_file = "log_file.";
    log_file+= to_string(pid);

    ofstream filename(log_file);
    filename << "Best Fit: " << endl;
    Memory_List_Node* current = memory->get_head();
    int i = 0;
    filename << "Processes currenty in the memory: " << endl;
    while(current!=NULL){
        i++;
        filename << endl;
        filename << i << ") ";
        filename << current->print_to_filename();
        current = current->next;
    }

    filename << endl;
    filename << "Pending Processes: " << endl;
    
    Process* process = L->get_head();
    while(process!=NULL){
        //i++;
        filename << endl;
        //filename << i << ") ";
        filename << process->print_to_filename();
        process = process->next;
    }

    filename.close();

    delete memory;
    delete L;
/*
    if(new_proc!=NULL){
        delete new_proc;
    }*/

    return 0;
}