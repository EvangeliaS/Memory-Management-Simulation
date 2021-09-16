#include <iostream>
#include "memory_tree.hpp"

using namespace std;

int main(){
    int D = 100;
    int d = D;
    int list_size = 1024;
    Memory_List* memory = new Memory_List(list_size);
   // Memory_Tree* tree = new Memory_Tree(list_size);
    Pending_Processes_List* L = new Pending_Processes_List();
    int size = 10;
    Process* proc , *proc1, *proc2, *proc3= NULL;
    int life = 2;
    proc = new Process(size, life);
    memory->insert_to_memory(proc, best_fit(proc, L, memory, false));

    cout <<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

    for(int i = 0; i<10; i++){
        life++;
        size+=20;
        proc1 = new Process(size, life);
        //tree->insert_process(proc1, buddy_algorithm(proc1, tree), L);
        memory->insert_to_memory(proc1, best_fit(proc1, L, memory, false));
        cout << endl;
       
    }

/*
    proc2 = new Process(16, life);  
    //tree->insert_process(proc2, buddy_algorithm(proc2, tree), L);
    memory->insert_to_memory(proc2, best_fit(proc2, L, memory));
   
    proc3 = new Process(100, life);
    memory->insert_to_memory(proc3, best_fit(proc3, L, memory));
   
    //tree->insert_process(proc3, buddy_algorithm(proc3, tree), L);
    
    proc3 = new Process(200, life);   
    memory->insert_to_memory(proc3, best_fit(proc3, L, memory));
   
    memory->delete_node_by_position(200);*/
    memory->display();

    memory->delete_node_by_position(250);
    memory->display();
    //add_pending_process(memory, L, BEST_FIT);
    cout << endl;
    memory->delete_node_by_position(360);
    memory->display();
    cout << endl;
    L->printList();
    cout << endl;
    add_pending_process(memory, L, BEST_FIT);
    memory->display();
    cout << endl;

    cout << endl;

    delete L;
    //delete tree;
    delete memory;
    
}