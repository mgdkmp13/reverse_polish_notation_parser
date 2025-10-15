#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

class Stack {
public:
    Node* topElement;
    Stack();
    ~Stack();
    void push(int data);
    void push(char* data, bool isOperator, int size);
    void push(bool data);
    void pop();
    Node top();
    void print();
    static int operatorSize(char* dataOperator);
};