#include <iostream>
#include "process.hpp"

using namespace std;

class Memory_Tree_Node{
    private:
        Process* process;
        int node_size;
    public:
        Memory_Tree_Node* right;
        Memory_Tree_Node* left;
        Memory_Tree_Node(int size);
        ~Memory_Tree_Node();
        bool is_leaf();
        int break_node();
        inline bool stores_process(){
            if(this->process==NULL) return false;
            else return true;
        }
        inline int get_node_size(){
            return this->node_size;
        }
        inline void set_size(int size){
            this->node_size = size;
        }
        inline void set_process(Process* proc){
            this->process = proc;
        }
        inline Process* get_process(){
            return this->process;
        }
};

class Memory_Tree{ //binary tree used for the buddy algorithm
    private:
        Memory_Tree_Node* root;
        int Memory_Size;
    public:
        Memory_Tree(int size);
        ~Memory_Tree();
        int insert_process(Process* process, Memory_Tree_Node* buddy, Pending_Processes_List* L);
        void merge_nodes();
        void destroy_node(Memory_Tree_Node* node);
        void printPreorder(Memory_Tree_Node* node);
        Memory_Tree_Node* find_tree_node(int size , Memory_Tree_Node* node);    //searches preorderly for the last tree node that is bigger than the "size"
        inline Memory_Tree_Node* get_root(){
            return this->root;
        }
        inline int get_memory_size(){
            return Memory_Size;
        }
        inline void set_root(Memory_Tree_Node*node){
            this->root = node;
        }
};

Memory_Tree_Node* buddy_algorithm(Process* process, Memory_Tree* tree);
       