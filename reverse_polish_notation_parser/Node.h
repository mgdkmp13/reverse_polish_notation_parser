#pragma once
#include <iostream>
using namespace std;

class Node {
public:
    bool isOperator;
    bool isMinMax;
    int dataNumber;
    char* dataOperator;
    int priority;
    Node* next;

    Node();
    Node(int data);
    Node(bool data);
    Node(const Node& other);
    Node(char* dataOperator, bool ifOperator, int size);
    ~Node();

    const int convertToNumber(char* dataOperator, int size);
    int checkPriority(char* dataOperator);
};