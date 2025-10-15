#pragma once
#include "NodeQueue.h"
#include <iostream>
using namespace std;

class Queue {
public:
    NodeQueue* front;
    NodeQueue* back;
    Queue();
    ~Queue();
    void put(int data);
    void put(char* data, bool ifOperator, int size, unsigned short minMaxArg = 0);
    NodeQueue get();
    void removeFront();
    void print();
};