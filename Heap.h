#ifndef HEAPH
#define HEAPH
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

template <typename K, typename T>
class HeapNode {
    public:
    K key;
    T data;
    int index;

    HeapNode(K key, T value) {
        this->key = key;
        this->data = value;
    }
};

template <typename K, typename T>
class Heap {
    private:
    //The heap is stored as an array of pointers
    vector<HeapNode<K, T>*> heap;
    unordered_map<K, HeapNode<K, T>*> nodeMap;

    void swapNodes(int i, int j) {
        swap(heap[i], heap[j]);
        heap[i]->index = i;
        heap[j]->index = j;
    }

    //Continously compares a node with its parent and moves it up the tree
    void percolateUp(int index) {
        int parent = (index - 1) / 2;
        if (parent < 0) return;

        //If the current node is smaller than its parent move it up
        if (heap[index]->data < heap[parent]->data) {
            swapNodes(index, parent);
            percolateUp(parent);
        }
    }

    //Continously compares a node with its children and moves it down the tree
    void percolateDown(int index) {
        int leftChildIndex = (2 * index) + 1;
        int rightChildIndex = (2 * index) + 2;

        //Sets the current smallest node to be the node we're percolating down
        int smallest = index;

        //If the left child is within the heap and its smaller than the current smallest node
        //Set smallest to be the left childs index
        if (leftChildIndex < heap.size() && heap[leftChildIndex]->data < heap[smallest]->data) {
            smallest = leftChildIndex;
        }

        //If the right child is within the heap and its smaller than the current smallest node
        //Set smallest to be the right childs index
        if (rightChildIndex < heap.size() && heap[rightChildIndex]->data < heap[smallest]->data) {
            smallest = rightChildIndex;
        }

        //If the smallest node is not the current node we're evaluating but one of its
        //children swap the current node and the smallest child
        if (smallest != index) {
            swapNodes(index, smallest);
            percolateDown(smallest);
        }
    }

    public:
    //Deconstructor
    ~Heap() {
        for (int i = 0; i < heap.size(); ++i) {
            extractMin();
        }
    }

    //Inserts a value into the heap by value
    void insert(K key, T value) {
        HeapNode<K, T> *node = new HeapNode<K, T>(key, value);
        nodeMap[key] = node;
        heap.push_back(node);
        node->index = heap.size()-1;
        percolateUp(heap.size()-1);
    }

    //Extracts the minimum value out of the heap
    void extractMin() {
        if (heap.size() < 1) return;
        nodeMap.erase(heap[0]->key);
        swapNodes(0, heap.size()-1);
        delete heap[heap.size()-1];
        heap.pop_back();
        if (heap.size() > 0) percolateDown(0);
    }

    //Given a node in the heap decrease its value and percolate it up
    void decreaseKey(K key, T value) {
        HeapNode<K, T> *node = nullptr;

        auto it = nodeMap.find(key); //Try to get an iterator to the node if it exist
        if (it == nodeMap.end()) return; //If it does not exist return
        node = it->second; //Set node ptr equal to the found node
        if (node->data < value) return; //Make sure this only decreases key
        node->data = value; //Update value

        //Move the value up the tree if needed
        percolateUp(node->index);
    }

    //Prints the entire heap
    void print() {
        for (int i = 0; i < heap.size(); ++i) {
            cout << heap[i]->data << " ";
        }
    }

    //Returns the current minimum value in the heap
    T GetMinValue() const {
        return heap[0]->data;
    }

    //Returns the current minimum value in the heap
    T GetMinKey() const {
        return heap[0]->key;
    }

    //Get whether the heap is empty or not
    bool empty() {
        return (!heap.size());
    }

    const T& operator[](const K& key) const {
        return nodeMap.find(key)->second->data;
    }
};
#endif