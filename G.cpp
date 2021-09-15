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
    int size = 10;
    Process* proc = NULL;
    int life = 2;
    for(int i = 0; i<11; i++){
        life++;
        proc = new Process(size, life);
        tree->insert_process(proc, buddy_algorithm(proc, tree), L);
        cout << endl;
        size+=20;
    }


    proc = new Process(100, life);
    tree->insert_process(proc, buddy_algorithm(proc, tree), L);
    
    proc = new Process(200, life);   

    tree->insert_process(proc, buddy_algorithm(proc, tree), L);


    proc = new Process(500, life);   

    tree->insert_process(proc, buddy_algorithm(proc, tree), L);
    
    proc = new Process(16, life);  
     tree->insert_process(proc, buddy_algorithm(proc, tree), L);
   
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