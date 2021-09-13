#include <iostream>
#include "memory_list.hpp"

using namespace std;


int main(){
    cout << "Hello bro" << endl;

    Memory_List* memory = new Memory_List();
    Pending_Processes_List* L = new Pending_Processes_List();
    int iter = 200;
    for(int i = 0; i<10; i++){
        iter++;
        Process* proc = new Process(iter, 2);
        memory->insert_to_memory(proc, best_fit(proc, L, memory));
    }
    memory->display();
    
}