//#include "PrimsAlgorithm.h"
#include "Heap.h"
#include "FibonacciHeap.h"
#include "PairingHeap.h"
#include <vector>
using namespace std;

int main() {

    //Adjacency Matrix (Undirected)
    vector<vector<int>> myList = {
        {0, 1, 3},
        {1, 0, 2},
        {3, 2, 0},
    };
    //cout << PrimsAlgorithm<Heap>(myList) << "\n";
    return 0;
}