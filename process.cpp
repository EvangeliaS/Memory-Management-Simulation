#include <iostream>
#include "process.hpp"

using namespace std;

Process::Process(int s, int life){
    this->set_id();
    this->lifetime = life;
    this->size = s;
    this->pending = true;
}