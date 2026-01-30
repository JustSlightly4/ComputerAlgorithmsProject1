#ifndef PRIMSALGORITHMH
#define PRIMSALGORITHMH
#include <vector>
#include <limits>
#include <utility>
using namespace std;

template <template <typename, typename> class HeapType>
vector<vector<int>> PrimsAlgorithm(const vector<vector<int>>& graph) {
    if (graph.empty()) return {};

    HeapType<int, int> minimumEdges;
    vector<vector<int>> minimumSpanningTree(graph.size(), vector<int>(graph.size(), 0));
    const int INF = numeric_limits<int>::max();

    minimumEdges.insert(0, 0);
    for (int i = 1; i < graph.size(); ++i) {
        minimumEdges.insert(i, INF);
    }

    while(!minimumEdges.empty()) {
        int minimumValue = minimumEdges.GetMinValue();
        int minimumKey = minimumEdges.GetMinKey();
        minimumEdges.extractMin();
        if (minimumValue == INF) continue;

        for (int i = 0; i < graph.size(); ++i) {
            if (graph[minimumKey][i] != 0) minimumEdges.decreaseKey(i, graph[minimumKey][i]);
        }

        if (!minimumEdges.empty()) minimumSpanningTree[minimumKey][minimumEdges.GetMinKey()] = minimumEdges.GetMinValue();
    }
    return minimumSpanningTree;
}
#endif