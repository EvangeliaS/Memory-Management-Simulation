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
    else{
        this->right = NULL;
        this->left  = NULL;
    }
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

int Memory_Tree_Node::remove_process(){
    if(this->process!=NULL){
        delete this->process;
        this->process = NULL;
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
    if(this->root->is_leaf()){
        delete this->root;
    }
    else{
        destroy_node(this->root);
    }
    this->root = NULL;
}

int Memory_Tree::insert_process(Process* process, Memory_Tree_Node* buddy, Pending_Processes_List* L, int start_time){
    if(buddy!=NULL){
        buddy->set_process(process, start_time);
        return 0;
    }   
    L->append_process(process);
    return -1;
}

int Memory_Tree::remove_process(Process* process){
    Memory_Tree_Node* node = this->search_process(process, this->root);
    if(node==NULL){
        return -1;
    }
    else{
        cout << node->get_process()->get_size() << endl;
        this->destroy_specific_node(this->root->left,this->root, node);
        if(this->root->left->is_leaf() && this->root->right->is_leaf()){
            delete this->root->left;
            delete this->root->right;
            this->root->left = NULL;
            this->root->right = NULL;
        }
        return 0;
    }
}

Memory_Tree_Node* Memory_Tree::search_process(Process* process, Memory_Tree_Node* node){
    Memory_Tree_Node* left = NULL,  *right = NULL;
    if(node==NULL){
        return NULL;
    }
    if(node->get_process()==process){
        return node;
    }
    if((left = search_process(process, node->left))!=NULL){
        return left;
    }
    else if((right = search_process(process, node->right))!=NULL){
        return right;
    }
    else{
        return NULL;
    }
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
    else{
        return NULL;
    }
}


void Memory_Tree::destroy_node(Memory_Tree_Node* node){
    if(node==NULL){
        return;
    }
    //if(node->left!=NULL){
        //cout << node->left->is_leaf() << endl;
        destroy_node(node->left);

   // if(node->right!=NULL){
        //cout << node->left->is_leaf() << endl;
        destroy_node(node->right);
    
//    if (node->left==NULL && node->right==NULL){
  //      return;
    delete node;
    node = NULL;
}

Memory_Tree_Node* Memory_Tree::destroy_specific_node(Memory_Tree_Node* child,Memory_Tree_Node* parent, Memory_Tree_Node* node){
    if(child == NULL){
        return NULL;
    }   
    if ((child==node) && (child->left == NULL) && (child->right == NULL)) {
        if (parent->left == node && parent->right->stores_process()==false && parent->right->is_leaf()==true){
            delete parent->left; 
            delete parent->right; 
            parent->left = NULL;
            parent->right = NULL;
        }
        else if(parent->left == node &&  parent->right->stores_process()==true){
            parent->left->remove_process();
        }
        else if(parent->right == node && parent->left->stores_process()==false && parent->left->is_leaf()==true){
            delete parent->left; 
            delete parent->right; 
            parent->left = NULL;
            parent->right = NULL;
        }
        else if(parent->right == node && parent->left->stores_process()==true){
            parent->right->remove_process();
        }
    }
    else if(parent->left->stores_process()==false && parent->left->is_leaf()==true && parent->right->stores_process()==false && parent->right->is_leaf()==true){
        delete parent->left; 
        delete parent->right; 
        parent->left = NULL;
        parent->right = NULL;
    }
    else{
        destroy_specific_node(child->left,child, node);
        destroy_specific_node(child->right,child, node);
    }
    return NULL;

}

void Memory_Tree::printPreorder(Memory_Tree_Node* node){
    if (node == NULL)
        return;

    if(node->stores_process()){
        cout << node->get_node_size() << " ";
        cout << " id: " << node->get_process()->get_process_id() << " size: " << node->get_process()->get_size()  << " start_time: " << node->get_process()->get_start_time() << endl;
    }
    else if(!node->is_leaf()){
        cout << node->get_node_size() << " ";
        cout << " Not available " << endl;
    }
    else{
        cout << node->get_node_size() << " ";
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
