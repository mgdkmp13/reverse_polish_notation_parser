#pragma once
#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;

class Input {
public:
    Stack stack;
    Queue queue;
    Stack arityStack;
    Stack isMinMaxStack;
    Input();

    void readInput();
    void manageCharacters(char& c, char* expression, int& j);
    void manageNumbers(char& c, char* expression, int& j);
    void checkAndPop(char* dataOperator, int operatorSize, bool isComa = false);
    bool checkAndPopN(char* expression, int numberSize);
    void calculate();
    static int calculateResult(bool& ifExit, int first, int second, char* action);
    void calculateBinary(bool& ifExit);
    void calculateNeg();
    void calculateIf();
    void calculateMin(int argNum);
    void calculateMax(int argNum);
    char* addArityToOperator(Node& tmpNode);
    ~Input();
};