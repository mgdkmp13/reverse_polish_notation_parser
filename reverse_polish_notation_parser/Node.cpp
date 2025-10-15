#define _CRT_SECURE_NO_WARNINGS
#include "Node.h"
#include <cstring>

Node::Node() {
    this->next = nullptr;
    this->dataNumber = 0;
    this->dataOperator = NULL;
    this->isOperator = 0;
    this->priority = 0;
    this->isMinMax = false;
}

Node::Node(int data) {
    this->next = nullptr;
    this->dataNumber = data;
    this->dataOperator = NULL;
    this->isOperator = 0;
    this->priority = 0;
    this->isMinMax = false;
}

Node::Node(bool data) {
    this->next = nullptr;
    this->dataNumber = data;
    this->dataOperator = NULL;
    this->isOperator = 0;
    this->priority = 0;
    this->isMinMax = data;
}


Node::Node(const Node& other) {
    this->isOperator = other.isOperator;
    this->dataNumber = other.dataNumber;
    this->priority = other.priority;
    this->isMinMax = other.isMinMax;

    if (other.dataOperator != nullptr) {
        size_t size = strlen(other.dataOperator) + 1;
        this->dataOperator = new char[size];

        strcpy_s(this->dataOperator, size, other.dataOperator);
        this->dataOperator[size - 1] = '\0';
    }
    else {
        this->dataOperator = nullptr;
    }

    this->next = nullptr;
}

Node::Node(char* dataOperator, bool ifOperator, int size) {
    if (ifOperator) {
        char* newOperator = new char[size + 1];

        strcpy_s(newOperator, size + 1, dataOperator);
        newOperator[size] = '\0';
        this->next = nullptr;
        this->dataNumber = 0;
        this->dataOperator = newOperator;
        this->isOperator = 1;
        this->priority = checkPriority(dataOperator);
        if (strcmp(dataOperator, "MIN") == 0 || strcmp(dataOperator, "MAX") == 0) {
            this->isMinMax = true;
        }
        else {
            this->isMinMax = false;
        }
    }
    else {
        this->next = nullptr;
        this->dataNumber = this->convertToNumber(dataOperator, size);
        this->dataOperator = NULL;
        this->isOperator = 0;
        this->priority = 0;
    }
}

const int Node::convertToNumber(char* dataOperator, int size) {
    int num = 0;
    for (int i = 0; i < size; i++) {
        char c = dataOperator[i];
        num = num * 10 + c - '0';
    }
    return num;
}

int Node::checkPriority(char* dataOperator) {
    if (strcmp(dataOperator, "+") == 0 || strcmp(dataOperator, "-") == 0) {
        return 2;
    }
    else if (strcmp(dataOperator, "*") == 0 || strcmp(dataOperator, "/") == 0) {
        return 3;
    }
    else if (strcmp(dataOperator, "(") == 0) {
        return 8;
    }
    else if (strcmp(dataOperator, ")") == 0) {
        return 9;
    }
    else if (strcmp(dataOperator, "N") == 0 || strcmp(dataOperator, "IF") == 0 || strcmp(dataOperator, "MIN") == 0 || strcmp(dataOperator, "MAX") == 0) {
        return 4;
    }
    else {
        return 0;
    }
}



Node::~Node() {
    this->next = nullptr;
    if (this->dataOperator != nullptr) {
        delete[] dataOperator;
        this->dataOperator = nullptr;
    }
}