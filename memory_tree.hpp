#include <iostream>
#include "process.hpp"

using namespace std;

class Memory_Tree_Node{
    private:
        Process* process;
    public:
        Memory_Tree_Node* right;
        Memory_Tree_Node* left;
};

class Memory_Tree{ //binary tree used for the budddy algorithm
    private:
        Memory_Tree_Node* root;
    public:
};
