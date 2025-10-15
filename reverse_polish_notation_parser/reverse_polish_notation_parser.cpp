#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <conio.h>
#include "Stack.h"
#include "Queue.h"
#include "Node.h"
#include "NodeQueue.h"
#include "Input.h"
#include <fstream>
using namespace std;

int main()
{
    int number = 0;
    cin >> number;
    getchar();

    while (number > 0) {
        Input input = Input();
        input.readInput();
        number--;
        printf("\n");
    }

    return 0;
}