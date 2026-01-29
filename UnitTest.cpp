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
template <template <typename, typename> class HeapType>
void VisualTest() {
    HeapType<int, int> heap;
    for (int i = 0; i < 10; ++i) {
        heap.insert(i, i);
    }
    heap.extractMin();
    heap.extractMin();
    heap.extractMin();
    heap.print();
}

//Times the amount of insertions into the heap
template <template <typename, typename> class HeapType>
void TimingTest1(int amount) {
    double startTime = getTime();
    HeapType<int, int> heap;
    for (int i = 0; i < amount; ++i) {
        heap.insert(i, amount);
    }
    double endTime = getTime();
    cout << endTime - startTime << "\n";
}

//Times the amount of insertions and extracts from the heap
template <template <typename, typename> class HeapType>
void TimingTest2(int amount) {
    double startTime = getTime();
    HeapType<int, int> heap;
    for (int i = 0; i < amount; ++i) {
        heap.insert(i, i);
    }
    for (int i = 0; i < amount; ++i) {
        heap.extractMin();
    }
    double endTime = getTime();
    cout << endTime - startTime << "\n";
}

//Times the amount of insertions and extracts from the heap
template <template <typename, typename> class HeapType>
void TimingTest3(int amount) {
    double startTime = getTime();
    HeapType<int, int> heap;
    for(int j = 0; j < amount; ++j) {
        for (int i = 0; i < 10; ++i) {
            heap.insert(i, i);
        }
        for (int i = 0; i < 10; ++i) {
            heap.extractMin();
        }
    }
    double endTime = getTime();
    cout << endTime - startTime << "\n";
}

int main() {
    int amount = 1000000;
    TimingTest3<FibonacciHeap>(amount);
    TimingTest3<PairingHeap>(amount);
    TimingTest3<Heap>(amount);
}
