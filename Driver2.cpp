#include <iostream>
#include "FibonacciHeap.h"

int main() {
    FibonacciHeap<char, int> myHeap;
    myHeap.insert('A', 1);
    myHeap.insert('B', 2);
    myHeap.insert('C', 3);
    myHeap.decreaseKey('B', 0);
    myHeap.print();
    return 0;
}