#pragma once
#include <iostream>
using namespace std;

class NodeQueue {
public:
    bool isOperator;
    int dataNumber;
    char* dataOperator;
    int priority;
    short minMaxArg;
    NodeQueue* next;
    NodeQueue* prev;

    NodeQueue();
    NodeQueue(int data);
    NodeQueue(const NodeQueue& other);
    NodeQueue(char* dataOperator, bool ifOperator, int size, unsigned short minMaxArg = 0);
    ~NodeQueue();

    const int convertToNumber(char* dataOperator, int size);
    int checkPriority(char* dataOperator);
};