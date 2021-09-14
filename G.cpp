#include <iostream>
#include "memory_list.hpp"

using namespace std;


int main(){
    cout << "Hello bro" << endl;
    int list_size = 1024;
    Memory_List* memory = new Memory_List(list_size);
    Pending_Processes_List* L = new Pending_Processes_List();
    int size = 200;
    Process* proc = NULL;
    int life = 2;
    for(int i = 0; i<10; i++){
        life++;
        proc = new Process(size, life);
        memory->insert_to_memory(proc, worst_fit(proc, L, memory));
        cout << endl;
    }
    memory->display();
    cout << endl;
    L->printList();

    cout << endl;
    
    
}