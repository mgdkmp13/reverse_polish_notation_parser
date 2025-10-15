#define _CRT_SECURE_NO_WARNINGS
#include "Input.h"
#include <fstream>
#include <cstring>
#define PRIOR_N 4


Input::Input() {
    this->stack = Stack();
    this->queue = Queue();
    this->arityStack = Stack();
    this->isMinMaxStack = Stack();
}

void Input::readInput() {
    int j = 0;
    char c = ' ';
    char* expression = new char[128];

    auto isOperator = [](char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '(' || ch == ')' || ch == 'N' || ch == 'I' ||
            ch == 'F' || ch == ',' || ch == 'M' || ch == 'A' || ch == 'X';
        };

    while (c != '.' && c != EOF) {
        c = getchar();

        if (isOperator(c)) {
            this->manageCharacters(c, expression, j);
        }
        else if (c >= '0' && c <= '9') {
            this->manageNumbers(c, expression, j);
        }

        strcpy(expression, "");

        if (c != '.') {
            j = 0;
        }
    }

    while (this->stack.topElement != nullptr) {
        Node topElement = this->stack.top();
        char* topOperator = topElement.dataOperator;
        this->queue.put(topOperator, 1, this->stack.operatorSize(topOperator));
        this->stack.pop();
    }

    delete[] expression;

    this->queue.print();
    this->calculate();
}

void Input::manageCharacters(char& c, char* expression, int& j) {
    while (c != ' ' && c != '\n' && c != '.' && c != ',') {
        expression[j] = c;
        j++;
        c = getchar();
    }
    expression[j] = '\0';
    if (c == ',') {
        if (this->stack.topElement != nullptr) {
            if (strcmp(this->stack.top().dataOperator, "IF") == 0) {
                strcpy(expression, ")");
                this->checkAndPop(expression, j, true);
                strcpy(expression, "(");
                this->stack.push(expression, 1, 1);
            }
            else if (this->isMinMaxStack.topElement != nullptr && !this->isMinMaxStack.topElement->isMinMax) {
                strcpy(expression, ")");
                this->checkAndPop(expression, j, true);
                strcpy(expression, "(");
                this->stack.push(expression, 1, 1);
            }
            else if (strcmp(this->stack.top().dataOperator, "MIN") == 0 || strcmp(this->stack.top().dataOperator, "MAX") == 0 || (this->isMinMaxStack.topElement != nullptr && this->isMinMaxStack.topElement->isMinMax)) {
                int counter = this->arityStack.topElement->dataNumber;
                this->arityStack.pop();
                this->arityStack.push(counter + 1);
                strcpy(expression, ")");
                this->checkAndPop(expression, j, true);
                strcpy(expression, "(");
                this->stack.push(expression, 1, 1);
            }

        }
    }
    else if (strcmp(expression, "IF") == 0) {
        this->isMinMaxStack.push(false);
        this->stack.push(expression, 1, 2);
        strcpy(expression, "(");
        this->stack.push(expression, 1, 1);

    }
    else if (strcmp(expression, "MIN") == 0 || strcmp(expression, "MAX") == 0) {
        this->isMinMaxStack.push(true);
        this->arityStack.push(1);
        this->stack.push(expression, 1, 3);
        strcpy(expression, "(");
        this->stack.push(expression, 1, 1);
    }
    else {
        int size = this->stack.operatorSize(expression);
        this->checkAndPop(expression, size);
        if (strcmp(expression, ")") != 0) {
            this->stack.push(expression, 1, size);
        }
    }
}

void Input::manageNumbers(char& c, char* expression, int& j) {
    while (c != ' ' && c != '.') {
        expression[j] = c;
        j++;
        c = getchar();
    }
    expression[j] = '\0';
    if (!this->checkAndPopN(expression, j)) {
        this->queue.put(expression, 0, j);
    }
}

void Input::checkAndPop(char* dataOperator, int operatorSize, bool isComa) {
    if (this->stack.topElement != nullptr) {
        if (strcmp(dataOperator, ")") == 0) {
            while (strcmp(this->stack.topElement->dataOperator, "(") != 0) {
                this->queue.put(this->stack.topElement->dataOperator, true, this->stack.operatorSize(this->stack.topElement->dataOperator));
                this->stack.pop();
                if (this->stack.topElement == nullptr) {
                    break;
                }
            }
            this->stack.pop();
            if (strcmp(dataOperator, "(") == 0) {
                this->stack.pop();

            }
            if (this->stack.topElement != nullptr && (strcmp(this->stack.topElement->dataOperator, "IF") == 0 || strcmp(this->stack.topElement->dataOperator, "N") == 0 /*|| strcmp(this->stack.topElement->dataOperator, "MIN") || strcmp(this->stack.topElement->dataOperator, "MAX")*/)) {
                this->queue.put(this->stack.topElement->dataOperator, true, this->stack.operatorSize(this->stack.topElement->dataOperator));
                this->stack.pop();
            }
            else if (!isComa && this->stack.topElement != nullptr) {
                if (this->stack.topElement->next != nullptr) {
                    if (strcmp(this->stack.topElement->dataOperator, "(") == 0 && (strcmp(this->stack.topElement->next->dataOperator, "IF") == 0)) {
                        this->stack.pop();
                        this->queue.put(this->stack.topElement->dataOperator, true, this->stack.operatorSize(this->stack.topElement->dataOperator));
                        this->stack.pop();
                        this->isMinMaxStack.pop();
                    }
                    else if (strcmp(this->stack.topElement->next->dataOperator, "MIN") == 0 || strcmp(this->stack.topElement->next->dataOperator, "MAX") == 0) {
                        this->stack.pop();
                        if (this->stack.topElement != nullptr) {
                            Node tmpNode = Node(this->stack.top());
                            this->stack.pop();
                            unsigned short num = this->arityStack.top().dataNumber;
                            this->arityStack.pop();
                            this->queue.put(tmpNode.dataOperator, true, this->stack.operatorSize(tmpNode.dataOperator), num);
                            this->isMinMaxStack.pop();
                        }
                    }
                }
                else {
                    if (strcmp(this->stack.topElement->dataOperator, "IF") == 0) {
                        this->queue.put(this->stack.topElement->dataOperator, true, this->stack.operatorSize(this->stack.topElement->dataOperator));
                        this->stack.pop();
                        this->isMinMaxStack.pop();
                    }
                    else if (this->stack.topElement != nullptr && strcmp(this->stack.topElement->dataOperator, "MIN") == 0 || strcmp(this->stack.topElement->dataOperator, "MAX") == 0) {
                        Node tmpNode = Node(this->stack.top());
                        this->stack.pop();
                        unsigned short num = this->arityStack.top().dataNumber;
                        this->arityStack.pop();
                        this->queue.put(tmpNode.dataOperator, true, this->stack.operatorSize(tmpNode.dataOperator), num);
                        this->stack.pop();
                        this->isMinMaxStack.pop();
                    }
                }
            }
        }
        else {
            Node* tmp = new Node(dataOperator, true, operatorSize);
            int prior = tmp->checkPriority(tmp->dataOperator);
            if (this->stack.topElement->priority != PRIOR_N || prior != PRIOR_N) {
                while (this->stack.topElement != nullptr && this->stack.topElement->checkPriority(this->stack.topElement->dataOperator) >= prior && strcmp(tmp->dataOperator, "(") != 0 && strcmp(this->stack.topElement->dataOperator, "(") != 0) {
                    this->queue.put(this->stack.topElement->dataOperator, true, this->stack.operatorSize(this->stack.topElement->dataOperator));
                    this->stack.pop();
                }
            }
            delete tmp;
        }
    }
}

bool Input::checkAndPopN(char* expression, int numberSize) {
    if (this->stack.topElement != nullptr) {
        if (strcmp(this->stack.topElement->dataOperator, "N") == 0) {
            this->queue.put(expression, 0, numberSize);
            this->queue.put(this->stack.topElement->dataOperator, true, this->stack.operatorSize(this->stack.topElement->dataOperator));
            this->stack.pop();
            return true;

        }
        return false;
    }
    return false;
}

void Input::calculate() {
    while (true) {
        bool ifExit = 0;
        if (this->queue.front != nullptr) {
            if (this->queue.front->isOperator) {
                if (strcmp(this->queue.front->dataOperator, "+") == 0 || strcmp(this->queue.front->dataOperator, "-") == 0 || strcmp(this->queue.front->dataOperator, "*") == 0 || strcmp(this->queue.front->dataOperator, "/") == 0) {
                    this->calculateBinary(ifExit);
                }
                else if (strcmp(this->queue.front->dataOperator, "N") == 0) {
                    this->calculateNeg();
                }
                else if (strcmp(this->queue.front->dataOperator, "IF") == 0) {
                    this->calculateIf();
                }
                else if (strlen(this->queue.front->dataOperator) == 3 && this->queue.front->dataOperator[0] == 'M') {
                    int i = 3;
                    int j = 0;
                    while (this->queue.front->dataOperator[j] != '\0') {
                        cout << this->queue.front->dataOperator[j];
                        j++;
                    }
                    cout << this->queue.front->minMaxArg;
                    cout << " ";
                    this->stack.print();

                    if (this->queue.front->dataOperator[1] == 'I' && this->queue.front->dataOperator[2] == 'N') {
                        calculateMin(this->queue.front->minMaxArg);
                    }
                    else if (this->queue.front->dataOperator[1] == 'A' && this->queue.front->dataOperator[2] == 'X') {
                        calculateMax(this->queue.front->minMaxArg);
                    }
                }
            }
            else {
                int number = this->queue.get().dataNumber;
                this->queue.removeFront();
                this->stack.push(number);
            }
        }
        else {
            cout << this->stack.topElement->dataNumber << '\n';
            break;
        }
        if (ifExit) {
            break;
        }
    }
}

void Input::calculateBinary(bool& ifExit) {
    int i = 0;
    while (this->queue.front->dataOperator[i] != '\0') {
        cout << this->queue.front->dataOperator[i];
        i++;
    }
    cout << " ";
    this->stack.print();

    int second = this->stack.top().dataNumber;
    this->stack.pop();

    int first = this->stack.top().dataNumber;
    this->stack.pop();

    int result = this->calculateResult(ifExit, first, second, this->queue.front->dataOperator);
    this->stack.push(result);

    this->queue.removeFront();
}

void Input::calculateNeg() {
    cout << this->queue.front->dataOperator << " ";
    this->stack.print();

    int first = this->stack.top().dataNumber;
    this->stack.pop();

    first = -first;
    this->stack.push(first);

    this->queue.removeFront();
}

void Input::calculateIf() {
    int i = 0;
    while (this->queue.front->dataOperator[i] != '\0') {
        cout << this->queue.front->dataOperator[i];
        i++;
    }
    cout << " ";
    this->stack.print();

    int third = this->stack.top().dataNumber;
    this->stack.pop();

    int second = this->stack.top().dataNumber;
    this->stack.pop();

    int first = this->stack.top().dataNumber;
    this->stack.pop();

    if (first > 0) {
        this->stack.push(second);
    }
    else {
        this->stack.push(third);
    }

    this->queue.removeFront();
}

void Input::calculateMin(int argNum) {
    int result = 999999999;
    for (int k = 0; k < argNum; k++) {
        int arg = this->stack.top().dataNumber;
        this->stack.pop();
        if (arg < result) {
            result = arg;
        }
    }
    this->stack.push(result);
    this->queue.removeFront();
}

void Input::calculateMax(int argNum) {
    int result = -999999999;
    for (int l = 0; l < argNum; l++) {
        int arg = this->stack.top().dataNumber;
        this->stack.pop();
        if (arg > result) {
            result = arg;
        }
    }
    this->stack.push(result);
    this->queue.removeFront();
}

int Input::calculateResult(bool& ifExit, int first, int second, char* action) {
    if (strcmp(action, "+") == 0) {
        return first + second;
    }
    else if (strcmp(action, "-") == 0) {
        return first - second;
    }
    else if (strcmp(action, "*") == 0) {
        return first * second;
    }
    else if (strcmp(action, "/") == 0) {
        if (second != 0) {
            return first / second;
        }
        else {
            cout << "ERROR\n";
            ifExit = 1;
            return 0;
        }
    }
    return 0;
}


Input::~Input() {
}