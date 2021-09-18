#include "memory_tree.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc!=7){
        return -1;
    }
    cout << "Welcome " << endl;
    cout << endl;

    const char* argv_for_exec[8];
    argv_for_exec[1] = argv[1];
    argv_for_exec[2] = argv[2];
    argv_for_exec[3] = argv[3];
    argv_for_exec[4] = argv[4];
    argv_for_exec[5] = argv[5];
    argv_for_exec[6] = argv[6];
    argv_for_exec[7] = nullptr;
    pid_t pid_for_G, pid_for_M;   

    //starting G
    argv_for_exec[0] = "./G";
    pid_for_G = fork();
    if(pid_for_G ==-1){
        cout << "Error in fork" << endl;
    }
    else if(pid_for_G==0){    
        execvp("./G", (char* const*)argv_for_exec);   
    }
    else{
        //cout << "Program" << endl;
    }

    //starting M
    argv_for_exec[0] = "./M";
    pid_for_M = fork();
    if(pid_for_M ==-1){
        cout << "Error in fork" << endl;
    }
    else if(pid_for_M==0){    
        execvp(argv_for_exec[0], (char* const*)argv_for_exec);   
    }
    else{
        //cout << "Program vol2" << endl;
    }
    
    //while(1){}

    return 0;
}