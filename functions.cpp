#include "functions.hpp"

//Functions for the semaphore operations

int sem_create(int num_of_semaphores){
    int semid; //the id key 
    if((semid = semget(SEMKEY, num_of_semaphores, IPC_CREAT | 0600))<0){   //create semaphore set
        perror("Error in creating semaphore"); // 0600 = read/alter by user
        exit(1);
    }
    return semid;
}

void sem_init(int semid, int index, int value){  // procedure to initialize specified semaphore to given value
   if (semctl (semid, index, SETVAL, value) < 0){  
        perror ("Error in initializing semaphore");
        exit (1);
    }
}

void sem_signal(int semid, int index){  // procedure to perform a V or signal operation on semaphore of given index
   struct sembuf sops[1];  // define operation on semaphore with given index

   sops[0].sem_num = index;// define operation on semaphore with given index
   sops[0].sem_op  = 1;    // add 1 to value for V operation
   sops[0].sem_flg = 0;    // type "man semop" in shell window for details

   if(semop (semid, sops, 1) == -1){
        perror ("error in semaphore operation");
        exit (1);
    }
}

void sem_wait(int semid, int index){    // procedure to perform a P or wait operation on a semaphore of given index 
  struct sembuf sops[1];  // only one semaphore operation to be executed

   sops[0].sem_num = index;// define operation on semaphore with given index
   sops[0].sem_op  = -1;   // subtract 1 to value for P operation
   sops[0].sem_flg = 0;    // type "man semop" in shell window for details

   if(semop (semid, sops, 1) == -1){  
        perror ("error in semaphore operation");
        exit (1);
    }
}

int read_line(std::string line, char memory[]){
    //string line;
    //getline(cin, line);
    strcpy(memory, line.c_str());
    //cout <<  "readline " <<memory << endl;
    return 1;
}

void free_resources(int  shmid , int  semid) {
    if(shmctl(shmid ,IPC_RMID ,NULL)<0){    //  Destroy  the  shared  memory  segment
        perror("shmctl"); 
        exit(1);
    }
    printf("Removed the shared memory segment with identifier %d\n", shmid);

    if(semctl(semid ,0,IPC_RMID ,0)<0){ //  Destroy semaphore set
        perror("semctl"); 
        exit(1);
    }
    printf("Removed semaphore with identifier %d\n", semid);
}

void pass_string(char *string, char dest[]){
    strcpy(dest, string);
}

int Poisson_distribution(int t){
    random_device rd;
    mt19937 gen(rd());
    std::poisson_distribution<> d(t);
    return d(gen);
}

int Exponential_distribution(int T){
    random_device rd;
    mt19937 gen(rd());
    std::exponential_distribution<> d(1.0/T);
    return d(gen);
}

int Uniform_distribution(int lo, int hi){
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(lo, hi);
    return dis(gen);
}