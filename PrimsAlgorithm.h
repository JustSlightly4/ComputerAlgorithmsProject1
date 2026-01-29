#ifndef PRIMSALGORITHMH
#define PRIMSALGORITHMH
#include <vector>
#include <limits>
using namespace std;

template <template <typename, typename> class HeapType>
int PrimsAlgorithm(const vector<vector<int>>& matrix) {
    if (matrix.size() < 1) return 0;

    //Set an infinity value to the maximum integer
    const int INF = numeric_limits<int>::max();

    //Save the size of the matrix
    int size = matrix.size();

    vector<bool> inMST(size, false);
    HeapType<int, int> heap;


    // Insert all vertices into heap
    heap.insert(0, 0); //Insert the starting node that cost 0 to travel to itself
    for (int i = 1; i < size; ++i) {
        heap.insert(i, INF); //Set all other nodes to infinity for now
    }

    int mstWeight = 0;

    while (!heap.empty()) {
        int minimumNodeKey = heap.GetMinKey();
        int minimumNodeValue = heap.GetMinValue();
        heap.extractMin();
        inMST[minimumNodeKey] = true;

        if (minimumNodeValue != INF) mstWeight += minimumNodeValue;

        // Relax edges from the minimum node
        for (int i = 0; i < size; ++i) {
            int weight = matrix[minimumNodeKey][i];

            if (weight != 0 && !inMST[i] && weight < key[i]) {
                key[i] = weight;
                heap.decreaseKey(i, weight);
            }
        }
    }

    return mstWeight;
}
#endif