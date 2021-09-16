#include <iostream>
//#include "memory_list.hpp"
#include "memory_tree.hpp"

using namespace std;


int main(){
    int list_size = 1024;
    //Memory_List* memory = new Memory_List(list_size);
    Memory_Tree* tree = new Memory_Tree(list_size);
    Pending_Processes_List* L = new Pending_Processes_List();
    int size = 10;
    Process* proc , *proc1, *proc2, *proc3= NULL;
    int life = 2;
    proc = new Process(size, life);
    tree->insert_process(proc, buddy_algorithm(proc, tree), L);
    for(int i = 0; i<10; i++){
        life++;
         size+=20;
        proc1 = new Process(size, life);
        tree->insert_process(proc1, buddy_algorithm(proc1, tree), L);
        cout << endl;
       
    }

    proc2 = new Process(16, life);  
    tree->insert_process(proc2, buddy_algorithm(proc2, tree), L);
   
    proc3 = new Process(100, life);
    tree->insert_process(proc3, buddy_algorithm(proc3, tree), L);
    
    proc3 = new Process(200, life);   

    tree->insert_process(proc3, buddy_algorithm(proc3, tree), L);


    proc3 = new Process(500, life);   

    tree->insert_process(proc3, buddy_algorithm(proc3, tree), L);
   
    tree->printPreorder(tree->get_root());

    tree->remove_process(proc);

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

    cout <<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

    tree->printPreorder(tree->get_root());
    tree->remove_process(proc2);
    tree->printPreorder(tree->get_root());

    proc3 = new Process(31, life);
    tree->insert_process(proc3, buddy_algorithm(proc3, tree), L);

    tree->printPreorder(tree->get_root());
   
   // tree->remove_process(proc1);
    //tree->remove_process(proc2);

    L->printList();

    cout << endl;

    delete L;
    delete tree;
    //delete memory;
    
}