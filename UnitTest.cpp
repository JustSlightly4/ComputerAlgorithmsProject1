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
bool UnitTest4(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *lastNode1 = A.insert(0);
    auto *lastNode2 = B.insert(0);
    auto *lastNode3 = C.insert(0);
    for (int i = 150; i < 300; ++i) {
        lastNode1 = A.insert(i);
        lastNode2 = B.insert(i);
        lastNode3 = C.insert(i);
    }
    A.decreaseKey(lastNode1, 0);
    B.decreaseKey(lastNode2, 0);
    C.decreaseKey(lastNode3, 0);
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest5(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *firstNode1 = A.insert(301);
    auto *firstNode2 = B.insert(301);
    auto *firstNode3 = C.insert(301);
    for (int i = 150; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    A.decreaseKey(firstNode1, 0);
    B.decreaseKey(firstNode2, 0);
    C.decreaseKey(firstNode3, 0);
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest6(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *firstNode1 = A.insert(155);
    auto *firstNode2 = B.insert(155);
    auto *firstNode3 = C.insert(155);
    for (int i = 150; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    A.decreaseKey(firstNode1, 0);
    B.decreaseKey(firstNode2, 0);
    C.decreaseKey(firstNode3, 0);
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest7(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *firstNode1 = A.insert(155);
    auto *firstNode2 = B.insert(155);
    auto *firstNode3 = C.insert(155);
    for (int i = 150; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    A.decreaseKey(firstNode1, 151);
    B.decreaseKey(firstNode2, 151);
    C.decreaseKey(firstNode3, 151);
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest8(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *firstNode1 = A.insert(155);
    auto *firstNode2 = B.insert(155);
    auto *firstNode3 = C.insert(155);
    for (int i = 150; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    A.decreaseKey(firstNode1, 151);
    B.decreaseKey(firstNode2, 151);
    C.decreaseKey(firstNode3, 151);
    A.decreaseKey(firstNode1, 0);
    B.decreaseKey(firstNode2, 0);
    C.decreaseKey(firstNode3, 0);
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest9(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *firstNode1 = A.insert(155);
    auto *firstNode2 = B.insert(155);
    auto *firstNode3 = C.insert(155);
    for (int i = 150; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    A.decreaseKey(firstNode1, 151);
    B.decreaseKey(firstNode2, 151);
    C.decreaseKey(firstNode3, 151);
    A.decreaseKey(firstNode1, 0);
    B.decreaseKey(firstNode2, 0);
    C.decreaseKey(firstNode3, 0);
    A.extractMin();
    B.extractMin();
    C.extractMin();
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest10(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *firstNode1 = A.insert(155);
    auto *firstNode2 = B.insert(155);
    auto *firstNode3 = C.insert(155);
    for (int i = 150; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    A.decreaseKey(firstNode1, 151);
    B.decreaseKey(firstNode2, 151);
    C.decreaseKey(firstNode3, 151);
    A.extractMin();
    B.extractMin();
    C.extractMin();
    A.decreaseKey(firstNode1, 0);
    B.decreaseKey(firstNode2, 0);
    C.decreaseKey(firstNode3, 0);
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest11(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *firstNode1 = A.insert(155);
    auto *firstNode2 = B.insert(155);
    auto *firstNode3 = C.insert(155);
    for (int i = 150; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    A.extractMin();
    B.extractMin();
    C.extractMin();
    A.decreaseKey(firstNode1, 151);
    B.decreaseKey(firstNode2, 151);
    C.decreaseKey(firstNode3, 151);
    A.decreaseKey(firstNode1, 151);
    B.decreaseKey(firstNode2, 151);
    C.decreaseKey(firstNode3, 151);
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
    return true;
}

template <typename HeapType1, typename HeapType2, typename HeapType3>
bool UnitTest12(HeapType1 &A, HeapType2 &B, HeapType3 &C) {
    auto *firstNode1 = A.insert(155);
    auto *firstNode2 = B.insert(155);
    auto *firstNode3 = C.insert(155);
    for (int i = 150; i < 300; ++i) {
        A.insert(i);
        B.insert(i);
        C.insert(i);
    }
    A.extractMin();
    B.extractMin();
    C.extractMin();
    A.decreaseKey(firstNode1, 151);
    B.decreaseKey(firstNode2, 151);
    C.decreaseKey(firstNode3, 151);
    A.decreaseKey(firstNode1, 999);
    B.decreaseKey(firstNode2, 999);
    C.decreaseKey(firstNode3, 999);
    if (!(A.min() == B.min() && B.min() == C.min())) return false;
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
    cout << "Unit Test 4: " << (UnitTest4(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 5: " << (UnitTest5(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 6: " << (UnitTest6(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 7: " << (UnitTest7(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 8: " << (UnitTest8(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 9: " << (UnitTest9(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 10: " << (UnitTest10(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 11: " << (UnitTest11(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
    cout << "Unit Test 12: " << (UnitTest12(fibHeap, pairingHeap, heap) ? "true\n" : "false\n");
}
