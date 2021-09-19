#include <iostream>
#include "memory_tree.hpp"
#define G_to_M_SEM_SEND     0
//#define G_to_M_SEM_RECV     2
//#define M_to_G_SEM_SEND     3
#define M_to_G_SEM_RECV     1

using namespace std;

int main(int argc, char* argv[]){ 
    if(argc!=7){
        return -1;
    }
    int D  = stoi(argv[1]);
//  int lo = stoi(argv[2]);
//  int hi = stoi(argv[3]);
//  int t  = stoi(argv[4]);
//  int T  = stoi(argv[5]);
    int S  = stoi(argv[6]);

    int semid;      //identifier for a semaphore set
    int shmid;      // shared memory segment id
    char* mem;

    if ((semid = semget(SEMKEY, 2, 0600))< 0){
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
    Pending_Processes_List* L = new Pending_Processes_List();
    int d = 1;

/// EKTELESI ME BEST FIT ALGORITHM
    Memory_List* memory = new Memory_List(S);
    
    while(d<=D){
        sem_wait(semid, M_to_G_SEM_RECV);
        memset(temp, 0, 128);
        pass_string(mem, temp);
    
        //if(flag){
            new_proc = create_process(temp);
            memory->insert_to_memory(new_proc, best_fit(new_proc, L, memory, false, d), d);   
            //memory->delete_node_by_process_stop_time(d);  
        //}
        
        sem_signal(semid, G_to_M_SEM_SEND);

        flag++;
        d++;
    }

    //create log_file.xxx
    pid_t pid = getpid();
    string log_file = "log_file_best.";
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
        filename << endl;
        filename << process->print_to_filename();
        process = process->next;
    }

    filename.close();

    delete memory;
    delete L;
/*
    //EKTELESI ME WORST FIT
    Memory_List* memory = new Memory_List(S);
    while(d<=D){
        sem_wait(semid, M_to_G_SEM_RECV);
        memset(temp, 0, 128);
        pass_string(mem, temp);
    
        if(flag){
            new_proc = create_process(temp);
            memory->insert_to_memory(new_proc, best_fit(new_proc, L, memory, false, d),d);           
        }
        
        sem_signal(semid, G_to_M_SEM_SEND);

        flag++;
        d++;
    }
    //create log_file.xxx
    pid_t pid = getpid();
    string log_file = "log_file_worst.";
    log_file+= to_string(pid);

    ofstream filename(log_file);
    filename << "Worst Fit: " << endl;
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
        filename << endl;
        filename << process->print_to_filename();
        process = process->next;
    }

    filename.close();

    delete memory;
    delete L;
*/


/*
    //EKTELESI ME BUDDY ALGORITHM
    Memory_Tree* tree = new Memory_Tree(S);
    while(d<=D){
        sem_wait(semid, M_to_G_SEM_RECV);
        memset(temp, 0, 128);
        pass_string(mem, temp);
    
        if(flag){
            new_proc = create_process(temp);
            tree->insert_process(new_proc, buddy_algorithm(new_proc, tree), L, d);           
        }
        
        sem_signal(semid, G_to_M_SEM_SEND);

        flag++;
        d++;
    }
    //create log_file.xxx
    pid_t pid = getpid();
    string log_file = "log_file_buddy.";
    log_file+= to_string(pid);

    ofstream filename(log_file);
    filename << "Buddy Algorithm : " << endl;
    //Memory_Tree_Node* current = tree->get_root();
    filename << "Processes currenty in the memory: " << endl;
    //i could not print the tree in file so I print it as output
    tree->printPreorder(tree->get_root());

    filename << endl;
    filename << "Pending Processes: " << endl;
    Process* process = L->get_head();
    while(process!=NULL){
        filename << endl;
        filename << process->print_to_filename();
        process = process->next;
    }

    filename.close();

    delete tree;
    delete L;

*/
    return 0;
}