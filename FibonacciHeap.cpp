#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <typename T>
class FibonacciNode {
    public:
    T data;
    int degree;
    bool marked;
    bool printed;
    FibonacciNode<T> *parent;
    FibonacciNode<T> *child;
    FibonacciNode<T> *rightNode;
    FibonacciNode<T> *leftNode;

    FibonacciNode(T key) {
        data = key;
        degree = 0;
        marked = false;
        printed = false;
        parent = nullptr;
        child = nullptr;
        rightNode = this;
        leftNode = this;
    }
};

template <typename T>
class FibonacciHeap {
    private:
    FibonacciNode<T> *minNode;
    int size_;

    void merge(FibonacciNode<T> *x, FibonacciNode<T> *y) {
        //If x > y then swap the pointers
        //So that x < y and can be the parent
        //always
        if (x->data > y->data) swap(x, y);

        //Remove y from this list so it can be the child of x
        y->leftNode->rightNode = y->rightNode;
        y->rightNode->leftNode = y->leftNode;
        y->leftNode = y;
        y->rightNode = y;

        //If x already has a child do some extra work
        if (x->child != nullptr) {
            y->rightNode = x->child;
            y->leftNode = x->child->leftNode;
            x->child->leftNode->rightNode = y;
            x->child->leftNode = y;
        }
        x->child = y;
        y->parent = x;
        x->degree++;

    }

    public:
    FibonacciHeap() {
        minNode = nullptr;
        size_ = 0;
    }

    FibonacciNode<T> *GetMin() {
        if (minNode == nullptr) exit(1);
        return minNode;
    }

    void insert(T key) {
        FibonacciNode<T> *node = new FibonacciNode<T>(key);
        if (minNode == nullptr) {
            minNode = node;
        } else {
            node->rightNode = minNode;
            node->leftNode = minNode->leftNode;
            minNode->leftNode->rightNode = node;
            minNode->leftNode = node;
            if (node->data < minNode->data) {
                minNode = node;
            }
        }
        size_++;
    }

    void printTree(FibonacciNode<T> *x) {
        if (x->printed == true) {
            if (x->parent != nullptr) cout << "] ";
            return;
        }
        x->printed = true;
        cout << x->data << " ";
        if (x->child != nullptr) { //If x has a child
            cout << "[ ";
            printTree(x->child);
        }
        printTree(x->rightNode);
    }
};

int main() {
    FibonacciHeap<int> myList;
    myList.insert(5);
    myList.insert(99);
    myList.insert(77);
    myList.insert(0);
    myList.insert(7);

    FibonacciNode<int> *x = myList.GetMin();
    FibonacciNode<int> *y = x->rightNode;
    myList.mergeRoots(x, y);

    x = myList.GetMin();
    y = x->rightNode;
    myList.mergeRoots(x, y);

    FibonacciNode<int> *z = myList.GetMin();
    myList.printTree(z);
}