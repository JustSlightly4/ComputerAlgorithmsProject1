#include <iostream>
using namespace std;

template <typename T>
class PairingHeapNode {
    public:
    T data;
    PairingHeapNode<T> *child;
    PairingHeapNode<T> *rightSibling;

    PairingHeapNode(T value) {
        data = value;
        child = nullptr;
        rightSibling = nullptr;
    }
};

template <typename T>
class PairingHeap {
    private:
    PairingHeapNode<T> *minNode;

    //Merges two root nodes together
    PairingHeapNode<T>* merge(PairingHeapNode<T> *x, PairingHeapNode<T> *y) {
        //If one of the values is null return the other
        if (!x) return y;
        if (!y) return x;

        //Make sure x is the minimum value
        if (y->data < x->data) swap(x, y);

        //The merge operation
        x->rightSibling = nullptr;
        y->rightSibling = x->child;
        x->child = y;

        //Return root of temp tree
        return x;
    }

    PairingHeapNode<T>* twoPassMerge(PairingHeapNode<T> *x) {
        if(x == nullptr || x->rightSibling == nullptr) return x;
        HeapNode *A, *B, *newNode;
        A = x;
        B = x->rightSibling;
        newNode = x->rightSibling->rightSibling;

        A->rightSibling = NULL;
        B->rightSibling = NULL;

        return merge(merge(A, B), twoPassMerge(newNode));
    }

    public:
    //Insert a new value into the tree
    void insert(T value) {
        PairingHeapNode<T> *node = new PairingHeapNode<T>(value);
        if (minNode) { //If the heap is not empty
            if (other->data < minNode->data) swap(minNode, other);
            other->rightSibling = minNode->child;
            minNode->child = other;
        } else { //If the heap is empty
            minNode = node;
        }
    }

    //Extracts the minimum value from the heap
    void extractMin() {
        if (!minNode) return; //If the heap is empty
        PairingHeapNode<T> *old = minNode;
        minNode = minNode->child;
        delete minNode;
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

};


int main() {
    PairingHeap<int> myList;
    for (int i = 0; i < 5; ++i) {
        myList.insert(i);
    }
    myList.print();
    return 0;
}