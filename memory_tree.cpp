#include <iostream>
#include "memory_tree.hpp"

using namespace std;

Memory_Tree_Node::Memory_Tree_Node(int size){
    this->right = NULL;
    this->left  = NULL;
    this->process = NULL;
    this->node_size = size;
}


Memory_Tree_Node::~Memory_Tree_Node(){
    if(this->stores_process()){
        delete this->process;
    }
/*    else{ 
        this->right = NULL;
        this->left  = NULL;
    }*/
}


bool Memory_Tree_Node::is_leaf(){
    if(this->right==NULL && this->left==NULL){
        return true;
    }
    return false;
}


Memory_Tree::Memory_Tree(int size){
    this->root = NULL;
    this->Memory_Size = size;

}

Memory_Tree::~Memory_Tree(){
    destroy_node(this->root);
    this->root = NULL;
}

int Memory_Tree::insert_process(Process* process, Memory_Tree_Node* buddy, Pending_Processes_List* L){
    if(buddy!=NULL){
        buddy->set_process(process);
        return 0;
    }   
    L->append_process(process);
    return -1;
}

Memory_Tree_Node* buddy_algorithm(Process* process, Memory_Tree* tree){
    if(process->get_size()>=tree->get_memory_size()){
        cout << "Error: The process cannot fit in the memory. " << endl;
        return NULL;
    }
    if(tree->get_root()==NULL){
        tree->set_root(new Memory_Tree_Node(tree->get_memory_size()));
        tree->preorder_search(process->get_size(), tree->get_root());
    }
}

Memory_Tree_Node* Memory_Tree::preorder_search(int size, Memory_Tree_Node* node){
    if(node->get_node_size()>=size && node->stores_process()==false && node->is_leaf()){
        return node;
    }
    else{
        size = size/2;
        node->set_size(size);
    }
    preorder_search(size, node->left);
    preorder_search(size, node->right);
}


void Memory_Tree::destroy_node(Memory_Tree_Node* node){
    if(node==NULL){
        return;
    }
    destroy_node(node->left);
    destroy_node(node->right);
    delete node;
    //node = NULL;
}

void Memory_Tree::printPreorder(Memory_Tree_Node* node){
    if (node == NULL)
        return;
 
    /* first print data of node */
    cout << node->get_node_size() << " ";
    if(node->stores_process()){
        cout << " id: " << node->get_process()->get_process_id() << " ";
    }
   
    /* then recur on left sutree */
    printPreorder(node->left);
 
    /* now recur on right subtree */
    printPreorder(node->right);
}