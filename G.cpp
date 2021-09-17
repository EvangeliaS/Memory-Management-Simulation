#include <iostream>
#include "memory_tree.hpp"

using namespace std;

int main(int argc, char* argv[]){ 
    if(argc!=7){
        return -1;
    }
    cout << "Hello from G" << endl;
    int D  = stoi(argv[1]);
    int lo = stoi(argv[2]);
    int hi = stoi(argv[3]);
    int t  = stoi(argv[4]);
    int T  = stoi(argv[5]);
    int S  = stoi(argv[6]);
}