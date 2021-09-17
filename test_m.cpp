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
    Process* proc , *proc1, *proc2, *proc3, *proc4 = NULL;
    int life = 2;
    proc = new Process(size, life);
    memory->insert_to_memory(proc, best_fit(proc, L, memory, false));

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

    proc1 = L->pop_process();

    memory->insert_to_memory(proc1, best_fit(proc1, L, memory, 0));
    proc2 = new Process(20, life);
    memory->insert_to_memory(proc2, best_fit(proc2, L, memory, 0));
    memory->display();
    proc4 = new Process(200, life);
    cout << endl << endl << endl;
    proc4->print();
    memory->insert_to_memory(proc4, best_fit(proc4, L, memory, 0));
    cout << "lol" << endl;
    memory->display();
    L->printList();
    proc3 = L->get_head();

    memory->insert_to_memory(proc3, best_fit(proc3, L, memory, 1));

    proc2 = new Process(5,life);

    memory->insert_to_memory(proc2, best_fit(proc2, L, memory, 0));

    proc2 = new Process(10,life);

    memory->insert_to_memory(proc2, best_fit(proc2, L, memory, 0));

    L->printList();
    memory->delete_node_by_position(250);

    add_pending_process(memory, L, BEST_FIT);
    cout << endl;

    memory->display();
    cout << endl;
    L->printList();
    cout << endl << endl;

    delete L;
    //delete tree;
    delete memory;
    
}