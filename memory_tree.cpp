#include <iostream>
#include "memory_tree.hpp"

using namespace std;

Memory_Tree_Node::Memory_Tree_Node(int size){
    this->node_size = size;
    this->right = NULL;
    this->left  = NULL;
    this->process = NULL;
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

int Memory_Tree_Node::break_node(){
    if(this->is_leaf()){
        this->left  = new Memory_Tree_Node((this->node_size/2));
        this->right = new Memory_Tree_Node((this->node_size/2));
        return 0;
    }
    else{
        return -1;
    }
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


Memory_Tree_Node* Memory_Tree::find_tree_node(int size, Memory_Tree_Node* node){
    Memory_Tree_Node* left = NULL,  *right = NULL;
    if(node==NULL){
        return NULL;
    }
    if(node->get_node_size()>=size && node->stores_process()==false && node->is_leaf()){
        if((node->get_node_size()/2)<size && node->stores_process()==false && node->is_leaf()){
            return node;
        }
        node->break_node();
    }
    if((left = find_tree_node(size, node->left))!=NULL){
        return left;
    }
    else if((right = find_tree_node(size, node->right))!=NULL){
        return right;
    }
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

    cout << node->get_node_size() << " ";
    if(node->stores_process()){
        cout << " id: " << node->get_process()->get_process_id() << " size: " << node->get_process()->get_size() << endl;
    }
    else if(!node->is_leaf()){
        cout << " Not available " << endl;
    }
    else{
        cout << " Available " << endl;
    }
    cout << endl; 
    printPreorder(node->left);
    printPreorder(node->right);
}

Memory_Tree_Node* buddy_algorithm(Process* process, Memory_Tree* tree){
    if(process->get_size()>=tree->get_memory_size()){
        cout << "Error: The process cannot fit in the memory. " << endl;
        return NULL;
    }
    if(tree->get_root()==NULL){
        tree->set_root(new Memory_Tree_Node(tree->get_memory_size()));
    }
    return tree->find_tree_node(process->get_size(), tree->get_root());
}
