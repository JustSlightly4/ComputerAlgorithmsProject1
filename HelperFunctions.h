#ifndef HELPERFUNCTIONSH
#define HELPERFUNCTIONSH
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

//Builds an adj matrix. ConnectivityPercentage determines roughly how connected the graph is.
vector<vector<int>> BuildGraph(int size, int connectivityPercentage = 75, int seed = 0) {
    if (connectivityPercentage < 0) connectivityPercentage = 0;
    else if (connectivityPercentage > 100) connectivityPercentage = 100;
    srand(seed);
    vector<vector<int>> graph(size, vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (graph[i][j] == 0) {
                int number = ((rand() % 100) < connectivityPercentage) ? ((rand() % 10) + 1) : 0;
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

#endif