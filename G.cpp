#include <iostream>
//#include "memory_list.hpp"
#include "memory_tree.hpp"

using namespace std;


int main(){
    cout << "Hello bro" << endl;
    int list_size = 1024;
    //Memory_List* memory = new Memory_List(list_size);
    Memory_Tree* tree = new Memory_Tree(list_size);
    Pending_Processes_List* L = new Pending_Processes_List();
    int size = 200;
    Process* proc = NULL;
    int life = 2;
    for(int i = 0; i<10; i++){
        life++;
        size = size/2;
        proc = new Process(size, life);
        tree->insert_process(proc, buddy_algorithm(proc, tree), L);
        cout << endl;
    }

    tree->printPreorder(tree->get_root());
/*
    cout << endl;
    memory->delete_node_by_position(400);
    memory->display();

    memory->delete_node_by_position(600);

    memory->display();
    proc = new Process(100, life);
    cout << "________________________" << memory->insert_to_memory(proc, worst_fit(proc, L, memory));
    
    memory->display();

    memory->delete_node_by_position(200);
    memory->display();

    proc = new Process(100, life);
    cout << "________________________" << memory->insert_to_memory(proc, best_fit(proc, L, memory));
    
    memory->display();
*/    

    cout << endl;
    L->printList();

    cout << endl;

    delete L;
    delete tree;
    //delete memory;
    
}