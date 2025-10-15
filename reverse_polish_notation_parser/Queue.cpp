#define _CRT_SECURE_NO_WARNINGS
#include "Queue.h"
#define PRIOR_N 4


Queue::Queue() {
    this->front = nullptr;
    this->back = nullptr;
}


void Queue::put(char* data, bool ifOperator, int size, unsigned short minMaxArg) {
    NodeQueue* newNode = new NodeQueue(data, ifOperator, size, minMaxArg);
    if (this->front == nullptr) {
        this->front = newNode;
        this->back = newNode;
    }
    else if (this->front == this->back) {
        newNode->next = this->front;
        this->back = newNode;
        this->front->prev = this->back;
    }
    else {
        newNode->next = this->back;
        this->back->prev = newNode;
        this->back = newNode;
    }
}

void Queue::put(int data) {
    NodeQueue* newNode = new NodeQueue(data);
    if (this->front == nullptr) {
        this->front = newNode;
    }
    else if (this->front == this->back) {
        newNode->next = this->front;
        this->back = newNode;
        this->front->prev = this->back;
    }
    else {
        newNode->next = this->back;
        this->back = newNode;
    }
}

void Queue::removeFront() {
    if (this->front != nullptr) {
        NodeQueue* tmp = this->front;

        if (this->front->prev != nullptr) {
            this->front->prev->next = nullptr;
            this->front = this->front->prev;
            tmp->prev = nullptr;
            delete tmp;
        }
        else {
            this->front->next = nullptr;
            this->front = nullptr;
            delete tmp;
        }
    }
    else {
        cout << "Pusty Queue\n";
    }
}

NodeQueue Queue::get() {
    if (this->front != nullptr) {
        NodeQueue tmp = NodeQueue(*this->front);
        return tmp;
    }
    else {
        cout << "Pusta kolejka!";
        return NULL;
    }
}

void Queue::print() {
    NodeQueue* tmp = this->front;
    while (tmp != nullptr) {
        if (tmp->isOperator && strcmp(tmp->dataOperator, "(") != 0 && strcmp(tmp->dataOperator, ")") != 0) {
            cout << tmp->dataOperator;
            if (strcmp(tmp->dataOperator, "MIN") == 0 || strcmp(tmp->dataOperator, "MAX") == 0) {
                cout << tmp->minMaxArg;
            }
            cout << " ";
        }
        else if (!tmp->isOperator) {
            cout << tmp->dataNumber << " ";
        }
        tmp = tmp->prev;
    }
    cout << '\n';
}

Queue::~Queue() {
    while (this->front != nullptr) {
        NodeQueue* temp = this->front;
        this->front = this->front->prev;
        delete temp;
    }
}