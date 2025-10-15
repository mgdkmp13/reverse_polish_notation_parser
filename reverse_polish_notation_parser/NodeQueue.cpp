#define _CRT_SECURE_NO_WARNINGS
#include "NodeQueue.h"

NodeQueue::NodeQueue() {
    this->next = nullptr;
    this->prev = nullptr;
    this->dataNumber = 0;
    this->dataOperator = NULL;
    this->isOperator = 0;
    this->priority = 0;
}

NodeQueue::NodeQueue(int data) {
    this->next = nullptr;
    this->prev = nullptr;
    this->dataNumber = data;
    this->dataOperator = NULL;
    this->isOperator = false;
    this->priority = 0;
}


NodeQueue::NodeQueue(const NodeQueue& other) {
    this->isOperator = other.isOperator;
    this->dataNumber = other.dataNumber;
    this->priority = other.priority;

    if (other.dataOperator != nullptr) {
        size_t size = strlen(other.dataOperator);
        this->dataOperator = new char[size + 1];
        strcpy(this->dataOperator, other.dataOperator);
        this->dataOperator[size] = '\0';
    }
    else {
        this->dataOperator = nullptr;
    }

    this->next = nullptr;
    this->prev = nullptr;
}

NodeQueue::NodeQueue(char* dataOperator, bool ifOperator, int size, unsigned short minMaxArg) {
    if (ifOperator) {
        char* newOperator = new char[size + 1];
        strcpy(newOperator, dataOperator);
        newOperator[size] = '\0';
        this->next = nullptr;
        this->prev = nullptr;
        this->dataNumber = 0;
        this->dataOperator = newOperator;
        this->isOperator = true;
        this->priority = checkPriority(dataOperator);
        this->minMaxArg = minMaxArg;
    }
    else {
        this->next = nullptr;
        this->prev = nullptr;
        this->dataNumber = this->convertToNumber(dataOperator, size);
        this->dataOperator = nullptr;
        this->isOperator = 0;
        this->priority = 0;
        this->minMaxArg = 0;
    }
}

const int NodeQueue::convertToNumber(char* dataOperator, int size) {
    int num = 0;
    for (int i = 0; i < size; i++) {
        char c = dataOperator[i];
        num = num * 10 + c - '0';
    }
    return num;
}

int NodeQueue::checkPriority(char* dataOperator) {
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
    else if (strcmp(dataOperator, "N") == 0) {
        return 4;
    }
    else {
        return 0;
    }
}


NodeQueue::~NodeQueue() {
    this->next = nullptr;
    this->prev = nullptr;
    if (this->dataOperator != nullptr) {
        delete[] dataOperator;
    }
    this->dataOperator = nullptr;
}