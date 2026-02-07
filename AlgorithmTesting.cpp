#include "Heap.h"
#include "FibonacciHeap.h"
#include "PairingHeap.h"
#include "PrimsAlgorithm.h"
#include "DijkstrasAlgorithm.h"
#include <cstring>
#include <iostream>
#include <ostream>
#include <vector>
#include <chrono>
#include <utility>
#include <algorithm>
using namespace std;

//Easy printing of a vector for myself
template <typename T>
ostream& operator<<(ostream &os, const vector<T> &vect) {

	//Safety Check
	if (vect.size() <= 0) return os;

	//Push vector contents into the ostream
	os << vect[0]; 
	for (unsigned int i = 1; i < vect.size(); ++i) {
		os << ", " << vect[i];
	}
    os << "\n";

	//Return the stream(?)
	return os;
}

//Easy printing of a 2D vector for myself
template <typename T>
ostream& operator<<(ostream &os, const vector<vector<T>> &vect) {

	//Safety Check
	if (vect.size() <= 0) return os;

    for (unsigned int i = 0; i < vect.size(); ++i) {
        for (unsigned int j = 0; j < vect[i].size(); ++j) {
            os << vect[i][j] << ", ";
        }
        os << "\n";
    }

	//Return the stream(?)
	return os;
}

/* chrono function to get wall clock time as double */
double getTime() {
    return chrono::duration<double>(
        chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}

void interpretMinimumSpanningTree(vector<int> const &spanningTree, vector<vector<int>> const &graph) {
    vector<std::pair<int, int>> list;
    int weight = 0;
    for (int i = 0; i < spanningTree.size(); ++i) {
        if (spanningTree[i] != -1) {
            //cout << "{" << spanningTree[i] << " -> " << i << "}\n";
            list.push_back({spanningTree[i], i});
            weight += graph[i][spanningTree[i]];
        }
    }

    sort(list.begin(), list.end());

    for (int i = 0; i < list.size(); ++i) {
        cout << "{" << list[i].first << " -> " << list[i].second << "}\n";
    }

    cout << "Weight: " << weight << endl;
}

// Builds an adjacency matrix.
// connectivityPercentage controls how many edges exist overall,
// but the graph is ALWAYS connected.
vector<vector<int>> BuildGraph(int size, int connectivityPercentage = 75, int seed = 0) {
    if (connectivityPercentage < 0) connectivityPercentage = 0;
    else if (connectivityPercentage > 100) connectivityPercentage = 100;

    srand(seed);

    vector<vector<int>> graph(size, vector<int>(size, 0));

    // 1) Build a spanning tree (guarantees connectivity)
    for (int i = 1; i < size; ++i) {
        int parent = rand() % i;         // connect i to some earlier node
        int weight = (rand() % 10) + 1;
        graph[i][parent] = weight;
        graph[parent][i] = weight;
    }

    // 2) Add extra edges randomly (skip ones already in spanning tree)
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {

            // If spanning tree already created this edge, don't overwrite it
            if (graph[i][j] != 0) continue;

            if ((rand() % 100) < connectivityPercentage) {
                int weight = (rand() % 10) + 1;
                graph[i][j] = weight;
                graph[j][i] = weight;
            }
        }
    }

    return graph;
}

void BalanceGraph(vector<vector<int>> &graph) {
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = i + 1; j < graph.size(); ++j) {
            graph[j][i] = graph[i][j];
        }
    }
}

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
    cout << graphSize << ": " << endTime - startTime << endl;
    return 0;
}