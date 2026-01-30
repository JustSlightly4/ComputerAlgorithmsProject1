#include "PrimsAlgorithm.h"
#include "Heap.h"
#include "FibonacciHeap.h"
#include "PairingHeap.h"
#include <vector>
#include <ostream>
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

template <typename T>
void interpretMinimumSpanningTree(vector<vector<T>> const &graph) {
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            if (graph[i][j] != 0) cout << "{" << i << " -> " << j << " = " << graph[i][j] << "} ";
        }
        cout << "\n";
    }
}

int main() {

    //Adjacency Matrix (Undirected)
    vector<vector<int>> myList = {
        {0, 1, 3},
        {1, 0, 2},
        {3, 2, 0},
    };
    interpretMinimumSpanningTree(PrimsAlgorithm<Heap>(myList));
    return 0;
}