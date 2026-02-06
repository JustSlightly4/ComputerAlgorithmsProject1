#include "PrimsAlgorithm.h"
#include "DijkstrasAlgorithm.h"
#include "Heap.h"
#include "FibonacciHeap.h"
#include "PairingHeap.h"
#include <vector>
#include <ostream>
#include <bits/stdc++.h>
#include <chrono>
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
    int weight = 0;
    for (int i = 0; i < spanningTree.size(); ++i) {
        if (spanningTree[i] != -1) {
            cout << "{" << spanningTree[i] << " -> " << i << "}\n";
            weight += graph[i][spanningTree[i]];
        }
    }
    cout << "Weight: " << weight << endl;
}

vector<vector<int>> BuildGraph(int size, int seed = 0) {
    srand(seed);
    vector<vector<int>> graph(size, vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (graph[i][j] == 0) {
                int number = rand() % 11;
                graph[i][j] = number;
                graph[j][i] = number;
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

enum heapTypes {HEAP, FIB, PAIR};
int main(int argc, char **argv) {

    if (argc < 3) {
        cout << "Usage: ./a.out HeapType(Heap, Fib, Pair) GraphSize GraphSeed\n";
        return 1;
    }

    heapTypes type;
    if (strcmp(argv[1], "Heap") == 0) type = HEAP;
    else if (strcmp(argv[1], "Fib") == 0) type = FIB;
    else if (strcmp(argv[1], "Pair") == 0) type = PAIR;
    else {"Error: Heap Type not declared!\n"; return 2;}

    int graphSize = atoi(argv[2]);
    int graphSeed = (argc > 3) ? atoi(argv[3]) : 0;
    vector<vector<int>> myList = BuildGraph(graphSize, graphSeed);
    //cout << myList << endl;

    double startTime = getTime();
    switch(type) {
        case HEAP:
            PrimsAlgorithm<Heap>(myList);
            break;
        case FIB:
            PrimsAlgorithm<FibonacciHeap>(myList);
            break;
        case PAIR:
            PrimsAlgorithm<PairingHeap>(myList);
            break;
    }
    double endTime = getTime();
    
    //cout << spanningTree << endl;
    //interpretMinimumSpanningTree(spanningTree, myList);
    cout << endTime - startTime << endl;
    return 0;
}