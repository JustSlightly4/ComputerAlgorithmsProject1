#ifndef PAIRINGHEAPH
#define PAIRINGHEAPH
#include <iostream>
using namespace std;

template <typename T>
class PairingHeapNode {
    public:
    T data;
    PairingHeapNode<T> *parent;
    PairingHeapNode<T> *child;
    PairingHeapNode<T> *leftSibling;
    PairingHeapNode<T> *rightSibling;

    PairingHeapNode(T value) {
        data = value;
        parent = nullptr;
        child = nullptr;
        leftSibling = nullptr;
        rightSibling = nullptr;
    }
};

template <typename T>
class PairingHeap {
    private:
    PairingHeapNode<T> *minNode;

    //Merges two root nodes together
    PairingHeapNode<T>* merge(PairingHeapNode<T>* x, PairingHeapNode<T>* y) {
        //If one of the nodes is null return the other node
        if (!x) return y;
        if (!y) return x;

        //Make sure x is always the top value
        if (y->data < x->data) swap(x, y);

        //Move pointers around
        y->parent = x;
        y->leftSibling = nullptr;
        y->rightSibling = x->child;

        //Handle if x has a child
        if (x->child) x->child->leftSibling = y;

        x->child = y;

        return x;
    }

    PairingHeapNode<T>* twoPassMerge(PairingHeapNode<T>* x) {
        //Base case
        if (!x || !x->rightSibling) return x;

        PairingHeapNode<T>* A = x;
        PairingHeapNode<T>* B = x->rightSibling;
        PairingHeapNode<T>* restOfList = x->rightSibling->rightSibling;

        // Detach A and B
        A->rightSibling = nullptr;
        A->leftSibling = nullptr;

        B->rightSibling = nullptr;
        B->leftSibling = nullptr;

        if (restOfList) restOfList->leftSibling = nullptr;

        return merge(merge(A, B), twoPassMerge(restOfList));
    }

    public:
    //Constructor
    PairingHeap() {
        minNode = nullptr;
    }

    //Deconstructor
    ~PairingHeap() {
        while(minNode) {
            extractMin();
        }
    }

    //Insert a new value into the tree
    PairingHeapNode<T>* insert(T value) {
        PairingHeapNode<T> *node = new PairingHeapNode<T>(value);
        minNode = merge(minNode, node);
        return node;
    }

    //Extracts the minimum value from the heap
    void extractMin() {
        if (!minNode) return;

        PairingHeapNode<T>* old = minNode;
        PairingHeapNode<T>* children = minNode->child;

        // Clear parent pointers
        PairingHeapNode<T>* currNode = children;
        while (currNode) {
            currNode->parent = nullptr;
            currNode = currNode->rightSibling;
        }

        delete old;
        minNode = twoPassMerge(children);
    }

    void decreaseKey(PairingHeapNode<T>* node, T value) {
    if (!node || value > node->data) return; // only decrease
    node->data = value;

    PairingHeapNode<T>* parent = node->parent;

        if (!parent) return; // already root

        // Cut the node out of its sibling list
        if (node->leftSibling) node->leftSibling->rightSibling = node->rightSibling; //If the node has a left sibling
        else parent->child = node->rightSibling; //If the node is the left most sibling

        if (node->rightSibling) node->rightSibling->leftSibling = node->leftSibling;

        // Detach node completely
        node->parent = nullptr;
        node->leftSibling = nullptr;
        node->rightSibling = nullptr;

        // Merge node back into the root list
        minNode = merge(minNode, node);
    }

    void print_(PairingHeapNode<T> *node) {
        cout << node->data << " ";
        if (node->child) print_(node->child);
        if (node->rightSibling) print_(node->rightSibling);
    }

    void print() {
        if (!minNode) return;
        print_(minNode);
        cout << "\n";
    }

    //Returns the current minimum value in the heap
    T min() const {
        return minNode->data;
    }

};
#endif