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
    FibonacciNode<T> *parent;
    FibonacciNode<T> *child;
    FibonacciNode<T> *rightNode;
    FibonacciNode<T> *leftNode;

    FibonacciNode(T key) {
        data = key;
        degree = 0;
        marked = false;
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

    void mergeRoots(FibonacciNode<T> *x, FibonacciNode<T> *y) {
        //If x > y then swap the pointers
        //So that x < y and can be the parent
        //always
        if (x->data > y->data) swap(x, y);

        //Remove y from this list so it can be the child of x
        y->leftNode->rightNode = y->rightNode;
        y->rightNode->leftNode = y->leftNode;
    }

    public:
    FibonacciHeap() {
        minNode = nullptr;
        size_ = 0;
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



    void print() {
        FibonacciNode<T> *currNode = minNode;
        for (int i = 0; i < size_; ++i) {
            cout << currNode->data << " ";
            currNode = currNode->rightNode;
        }
        cout << "\n";
    }
};

int main() {
    FibonacciHeap<int> myList;
    myList.insert(99);
    myList.insert(888);
    myList.insert(1);
    myList.print();
}