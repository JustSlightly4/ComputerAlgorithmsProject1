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
void VisualTest(HeapType& heap) {
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
void TimingTest1(HeapType& heap, int amount) {
    double startTime = getTime();
    for (int i = 0; i < amount; ++i) {
        heap.insert(amount);
    }
    double endTime = getTime();
    cout << endTime - startTime << "\n";
}

//Times the amount of insertions and extracts from the heap
template <typename HeapType>
void TimingTest2(HeapType& heap, int amount) {
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

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest1(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    for (int i = 0; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    for (int i = 0; i < 150; ++i) {
        if (!(A.min() == B.min() && B.min() == C.min())) return false;
        A.extractMin();
        B.extractMin();
        C.extractMin();
    }
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest2(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    for (int i = 0; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    for (int i = 0; i < 300; ++i) {
        if (!(A.min() == B.min() && B.min() == C.min())) return false;
        A.extractMin();
        B.extractMin();
        C.extractMin();
    }
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest3(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    for (int i = 0; i < 300; ++i) {
        A.insert(1);
        B.insert(1);
        C.insert(1);
    }
    for (int i = 0; i < 300; ++i) {
        if (!(A.min() == B.min() && B.min() == C.min())) return false;
        A.extractMin();
        B.extractMin();
        C.extractMin();
    }
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest3(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    for (int i = 0; i < 300; ++i) {
        A.insert(1);
        B.insert(1);
        C.insert(1);
    }
    for (int i = 0; i < 300; ++i) {
        if (!(A.min() == B.min() && B.min() == C.min())) return false;
        A.extractMin();
        B.extractMin();
        C.extractMin();
    }
    return true;
}

int main() {
    FibonacciHeap<int> fibHeap;
    PairingHeap<int> pairingHeap;
    Heap<int> heap;
    int amount = 100000;
    cout << "Unit Test 1: " << (UnitTest1(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 2: " << (UnitTest2(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 3: " << (UnitTest3(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
}
