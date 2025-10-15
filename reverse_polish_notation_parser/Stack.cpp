#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#define PRIOR_N 4

Stack::Stack() {
    this->topElement = nullptr;
}


void Stack::push(char* data, bool isOperator, int size) {
    Node* newNode = new Node(data, isOperator, size);
    if (this->topElement == nullptr) {
        this->topElement = newNode;
    }
    else {
        newNode->next = this->topElement;
        this->topElement = newNode;
    }
}

void Stack::push(int data) {
    Node* newNode = new Node(data);
    if (this->topElement == nullptr) {
        this->topElement = newNode;
    }
    else {
        newNode->next = this->topElement;
        this->topElement = newNode;
    }
}

void Stack::push(bool data) {
    Node* newNode = new Node(data);
    if (this->topElement == nullptr) {
        this->topElement = newNode;
    }
    else {
        newNode->next = this->topElement;
        this->topElement = newNode;
    }
}

void Stack::pop() {
    if (this->topElement != nullptr) {
        Node* tmp = this->topElement;

        if (this->topElement->next != nullptr) {
            this->topElement = this->topElement->next;
            tmp->next = nullptr;
            delete tmp;
        }
        else {
            this->topElement->next = nullptr;
            this->topElement = nullptr;
            delete tmp;
        }
    }
    else {
        cout << "Pusty stack\n";
    }
}

Node Stack::top() {
    if (this->topElement != nullptr) {
        Node tmp = Node(*this->topElement);
        return tmp;
    }
    else {
        cout << "Pusty stack!";
        return NULL;
    }
}

void Stack::print() {
    Node* tmp = this->topElement;
    while (tmp != nullptr) {
        if (tmp->isOperator && strcmp(tmp->dataOperator, "(") != 0 && strcmp(tmp->dataOperator, ")") != 0) {
            cout << tmp->dataOperator << " ";
        }
        else if (!tmp->isOperator) {
            cout << tmp->dataNumber << " ";
        }
        tmp = tmp->next;
    }
    cout << '\n';
}


int Stack::operatorSize(char* dataOperator) {
    int size = 0;
    while (dataOperator[size] != '\0') {
        size++;
    }
    return size;
}

Stack::~Stack() {
    while (this->topElement != nullptr) {
        Node* temp = this->topElement;
        this->topElement = this->topElement->next;
        delete temp;
    }
}