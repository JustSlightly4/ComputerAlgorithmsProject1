#include <iostream>
#include "Heap.h"
#include "FibonacciHeap.h"
#include "PairingHeap.h"

int main() {
    PairingHeap<char, int> myHeap;
    myHeap.insert('A', 1);
    myHeap.insert('B', 2);
    myHeap.insert('C', 3);
    myHeap.decreaseKey('B', 0);
    myHeap.print();
    return 0;
}