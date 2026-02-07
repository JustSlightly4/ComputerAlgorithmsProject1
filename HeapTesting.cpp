#include <iostream>
#include <chrono>
#include "Heap.h"
#include "FibonacciHeap.h"
#include "PairingHeap.h"
using namespace std;

/* chrono function to get wall clock time as double */
double getTime() {
    return chrono::duration<double>(
        chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}

template <template <typename, typename> class HeapType>
void insert(int size) {
    HeapType<int, int> heap;
    double startTime = getTime();
    for (int i = 0; i < size; ++i) {
        heap.insert(i, i);
    }
    double endTime = getTime();
    cout << size << ": " << endTime - startTime << endl;
}

template <template <typename, typename> class HeapType>
void extractMin(int size) {
    HeapType<int, int> heap;
    for (int i = 0; i < size; ++i) {
        heap.insert(i, i);
    }
    double startTime = getTime();
    for (int i = 0; i < size; ++i) {
        heap.extractMin();
    }
    double endTime = getTime();
    cout << size << ": " << endTime - startTime << endl;
}

template <template <typename, typename> class HeapType>
void decreaseKey(int size) {
    HeapType<int, int> heap;
    for (int i = 0; i < size; ++i) {
        heap.insert(i, i + 1);
    }
    double startTime = getTime();
    for (int i = 0; i < size; ++i) {
        heap.decreaseKey(i, 0);
    }
    double endTime = getTime();
    cout << size << ": " << endTime - startTime << endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: ./a.out size(int)\n";
        return 1;
    }
    int heapSize = atoi(argv[1]);
    decreaseKey<PairingHeap>(heapSize); //This is the line to change for testing
    return 0;
}