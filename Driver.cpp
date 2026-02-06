#include "Heap.h"
#include "FibonacciHeap.h"
#include "PairingHeap.h"
#include "PrimsAlgorithm.h"
#include "DijkstrasAlgorithm.h"
#include "HelperFunctions.h"
#include <cstring>
using namespace std;

enum HeapTypes {HEAP = 0, FIB = 1, PAIR = 2};
enum AlgTypes {PRIMS = 0, DIJKSTRAS = 1};
int main(int argc, char **argv) {

    if (argc < 5) {
        cout << "Usage: ./a.out HeapType(Heap, Fib, Pair) AlgorithmType(Prim, Dijk) GraphSize(int) GraphConnectivity(int) GraphSeed(int)\n";
        return 1;
    }

    HeapTypes heapType;
    AlgTypes algType;

    if (strcmp(argv[1], "Heap") == 0) heapType = HEAP;
    else if (strcmp(argv[1], "Fib") == 0) heapType = FIB;
    else if (strcmp(argv[1], "Pair") == 0) heapType = PAIR;
    else {cout << "Error: Heap Type not declared!\n"; return 2;}

    if (strcmp(argv[2], "Prim") == 0) algType = PRIMS;
    else if (strcmp(argv[2], "Dijk") == 0) algType = DIJKSTRAS;
    else {cout << "Error: Algorithm Type not declared!\n"; return 3;}

    int graphSize = atoi(argv[3]);
    int graphConnectivity = atoi(argv[4]);
    int graphSeed = (argc > 5) ? atoi(argv[5]) : 0;
    vector<vector<int>> graph = BuildGraph(graphSize, graphConnectivity, graphSeed);
    vector<int> spanningTree;
    //cout << graph << endl;

    double startTime = getTime();
    switch(heapType) {
        case HEAP:
            spanningTree = (algType) ? DijkstrasAlgorithm<Heap>(graph) : PrimsAlgorithm<Heap>(graph);
            break;
        case FIB:
            spanningTree = (algType) ? DijkstrasAlgorithm<FibonacciHeap>(graph) : PrimsAlgorithm<FibonacciHeap>(graph);
            break;
        case PAIR:
            spanningTree = (algType) ? DijkstrasAlgorithm<PairingHeap>(graph) : PrimsAlgorithm<PairingHeap>(graph);
            break;
    }
    double endTime = getTime();
    
    //interpretMinimumSpanningTree(spanningTree, graph);
    cout << endTime - startTime << endl;
    return 0;
}