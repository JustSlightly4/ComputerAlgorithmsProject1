#ifndef HEAPH
#define HEAPH
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class HeapNode {
    public:
    T data;
    int index;

    HeapNode(T value) {
        data = value;
    }
};

template <typename T>
class Heap {
    private:
    //The heap is stored as an array of pointers
    vector<HeapNode<T>*> heap;

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
    HeapNode<T>* insert(T value) {
        HeapNode<T> *node = new HeapNode<T>(value);
        heap.push_back(node);
        node->index = heap.size()-1;
        percolateUp(heap.size()-1);
        return node;
    }

    //Extracts the minimum value out of the heap
    void extractMin() {
        if (heap.size() < 1) return;
        swapNodes(0, heap.size()-1);
        delete heap[heap.size()-1];
        heap.pop_back();
        if (heap.size() > 0) percolateDown(0);
    }

    //Given a node in the heap decrease its value and percolate it up
    void decreaseKey(HeapNode<T> *node, T value) {
        if (!node || node->data < value) return; //Make sure this only decreases key
        node->data = value;
        percolateUp(node->index);
    }

    //Prints the entire heap
    void print() {
        for (int i = 0; i < heap.size(); ++i) {
            cout << heap[i]->data << " ";
        }
    }

    //Returns the current minimum value in the heap
    T min() const {
        return *heap[0];
    }
};
#endif