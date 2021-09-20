#include <iostream>
#include "memory_tree.hpp"
#define G_to_M_SEM_SEND     0
#define M_to_G_SEM_RECV     1

using namespace std;


int main(int argc, char* argv[]){ 
    if(argc!=8){
        return -1;
    }
//  int D  = stoi(argv[1]);
//  int lo = stoi(argv[2]);
//  int hi = stoi(argv[3]);
//  int t  = stoi(argv[4]);
//  int T  = stoi(argv[5]);
    int S  = stoi(argv[6]);
    int algorithm = stoi(argv[7]);

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

    //int flag = 0;
    char temp[128];
    Process* new_proc = NULL;
    Pending_Processes_List* L = new Pending_Processes_List();
    int d = 0;
    string details;
    int finished_processes = 0;

    if(algorithm==1){    /// EKTELESI ME BEST FIT ALGORITHM
        //create log_file.xxx
        cout << "Running Best fit: " << endl;
        pid_t pid = getpid();
        string log_file = "log_file_best";
        log_file+= to_string(pid);
        log_file+=".txt";

        ofstream filename(log_file);
        filename << "Best Fit: " << endl << endl;
        filename << "Finished processes: " << endl;
        Memory_List* memory = new Memory_List(S);

        while(1){
            sem_wait(semid, M_to_G_SEM_RECV);
            memset(temp, 0, 128);
            pass_string(mem, temp);
        
            if(strcmp("$", temp)==0){
                break;
            }
        
            if(strcmp("", temp)!=0 && strcmp("$", temp)!=0){
                new_proc = create_process(temp);
                d = new_proc->get_birth_time(); 
                memory->insert_to_memory(new_proc, best_fit(new_proc, L, memory, false, d),d);           
            }
            if(strcmp("", temp)!=0){
                if((details = memory->delete_node_by_process_stop_time(d))!=""){
                    if (filename.is_open()){
                        filename << "Removed process: ";  
                        filename << details; 
                        filename.flush();
                    }
                add_pending_process(memory, L, BEST_FIT, d);
                finished_processes++;
                }
            }
            sem_signal(semid, G_to_M_SEM_SEND);
        }

        sem_signal(semid, G_to_M_SEM_SEND);

        Memory_List_Node* current = memory->get_head();

        int i = 0;
        if (filename.is_open()){
            filename.flush();
            filename << "Finished processes: " << finished_processes << endl;
            filename << endl;
            filename << "Processes currenty in the memory: " << endl;
            while(current!=NULL){
                i++;
                filename << endl;
                filename << i << ") ";
                filename << current->print_to_filename();
                current = current->next;
                filename.flush();
            }
        
            filename << endl;
            filename << "Pending Processes: " << endl;
            
            Process* process = L->get_head();
            while(process!=NULL){
                filename << endl;
                filename << process->print_to_filename();
                process = process->next;
                filename.flush();
            }
        }
        filename.close();

        delete memory;
        delete L;
    }


    else if(algorithm==2){    //EKTELESI ME WORST FIT

        cout << "Running Worst fit: " << endl;
        //create log_file.xxx
    
        pid_t pid = getpid();
        string log_file = "log_file_worst";
        log_file+= to_string(pid);
        log_file+=".txt";

        ofstream filename(log_file);
        filename << "Worst Fit: " << endl << endl;
        filename << "Finished processes: " << endl;
        Memory_List* memory = new Memory_List(S);
        while(1){
            sem_wait(semid, M_to_G_SEM_RECV);

            memset(temp, 0, 128);
            pass_string(mem, temp);
            if(strcmp("$", temp)==0){
                break;
            }
        
            if(strcmp("", temp)!=0 && strcmp("$", temp)!=0){
                new_proc = create_process(temp);
                d = new_proc->get_birth_time(); 
                memory->insert_to_memory(new_proc, worst_fit(new_proc, L, memory, false, d),d);           
            }
            if(strcmp("", temp)!=0){
                if((details = memory->delete_node_by_process_stop_time(d))!=""){
                    if (filename.is_open()){
                        filename << "Finished process: ";  
                        filename << details; 
                        filename.flush();
                    }
                    add_pending_process(memory, L, WORST_FIT, d);
                    finished_processes++;
                }
            }
            sem_signal(semid, G_to_M_SEM_SEND);
        }

        sem_signal(semid, G_to_M_SEM_SEND);
        Memory_List_Node* current = memory->get_head();
        int i = 0;
        if (filename.is_open()){
            filename.flush();
            filename << endl;
            filename << "Finished processes: " << finished_processes << endl;
            filename << endl;
            filename << "Processes currenty in the memory: " << endl;
            while(current!=NULL){
                i++;
                filename << endl;
                filename << i << ") ";
                filename << current->print_to_filename();
                current = current->next;
                filename.flush();
            }
        
            filename << endl;
            filename << "Pending Processes: " << endl;
            
            Process* process = L->get_head();
            while(process!=NULL){
                filename << endl;
                filename << process->print_to_filename();
                process = process->next;
                filename.flush();
            }
        }
        filename.close();

        delete memory;
        delete L;
    }

    else if(algorithm==3){  //EKTELESI ME BUDDY ALGORITHM

        cout << "Running Buddy Algorithm: " << endl;
        Memory_Tree* tree = new Memory_Tree(S);

        while(1){
            sem_wait(semid, M_to_G_SEM_RECV);

            memset(temp, 0, 128);
            pass_string(mem, temp);
            if(strcmp("$", temp)==0){
                break;
            }
        
            if(strcmp("", temp)!=0 && strcmp("$", temp)!=0){
                new_proc = create_process(temp);
                d = new_proc->get_birth_time(); 
                tree->insert_process(new_proc, buddy_algorithm(new_proc, tree), L, d, false);  
                        
            }
    /*      if(strcmp("", temp)!=0 && flag==1){
                if(tree->remove_process(tree->search_process_by_stop_time(d,tree->get_root())->get_process())==0){
                    finished_processes++;
                }*/
                add_pending_process(tree, L, d);
                    
            sem_signal(semid, G_to_M_SEM_SEND);
        }

        sem_signal(semid, G_to_M_SEM_SEND);
        
        //i could not print the tree in file so I print it as output
        tree->printPreorder(tree->get_root());
        
        //create log_file.xxx
        pid_t pid = getpid();
        string log_file = "log_file_buddy";
        log_file+= to_string(pid);
        log_file+=".txt";

        ofstream filename(log_file);
        filename << "Buddy Algorithm : " << endl;

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
    }
    else{
        cout << "Please input 1,2,3 for algorithm choise(last parameter)" << endl;
    }

    return 0;
}
