#include "FibonacciHeap.h"
#include "PairingHeap.h"
#include "Heap.h"
#include <iostream>
#include <chrono>
using namespace std;

/* chrono function to get wall clock time as double */
double getTime() {
    return chrono::duration<double>(
        chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}

//Adds values and prints out heap
template <typename HeapType>
void UnitTest0(HeapType& heap) {
    for (int i = 0; i < 10; ++i) {
        heap.insert(i);
    }
    heap.extractMin();
    heap.extractMin();
    heap.extractMin();
    heap.print();
}

//Times the amount of insertions into the heap
template <typename HeapType>
void UnitTest1(HeapType& heap, int amount) {
    double startTime = getTime();
    for (int i = 0; i < amount; ++i) {
        heap.insert(amount);
    }
    double endTime = getTime();
    cout << endTime - startTime << "\n";
}

//Times the amount of insertions and extracts from the heap
template <typename HeapType>
void UnitTest2(HeapType& heap, int amount) {
    double startTime = getTime();
    for (int i = 0; i < amount; ++i) {
        heap.insert(i);
    }
    for (int i = 0; i < amount; ++i) {
        heap.extractMin();
    }
    double endTime = getTime();
    cout << endTime - startTime << "\n";
}


int main() {
    FibonacciHeap<int> fibHeap;
    PairingHeap<int> pairingHeap;
    Heap<int> heap;
    int amount = 15000;
    UnitTest2(fibHeap, amount);
    UnitTest2(pairingHeap, amount);
    UnitTest2(heap, amount);
}
