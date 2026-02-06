#ifndef DIJKSTRASALGORITHMH
#define DIJKSTRASALGORITHMH
#include <vector>
#include <limits>
#include <utility>
using namespace std;

template <template <typename, typename> class HeapType>
vector<int> DijkstrasAlgorithm(const vector<vector<int>>& graph) {
    if (graph.empty()) return {};

    HeapType<int, int> minimumEdges;
    vector<int> minimumSpanningTree(graph.size(), -1);
    const int INF = numeric_limits<int>::max();

    minimumEdges.insert(0, 0);
    for (int i = 1; i < graph.size(); ++i) {
        minimumEdges.insert(i, INF);
    }

    while(!minimumEdges.empty()) {
        int minimumValue = minimumEdges.GetMinValue();
        int minimumKey = minimumEdges.GetMinKey();
        minimumEdges.extractMin();
        if (minimumValue == INF) break;

        for (int i = 0; i < graph.size(); ++i) {
            if (graph[minimumKey][i] != 0) {
                if (minimumEdges.decreaseKey(i, minimumValue + graph[minimumKey][i])) {
                    minimumSpanningTree[i] = minimumKey;
                }
            }
        }
    }
    return minimumSpanningTree;
}
#endif