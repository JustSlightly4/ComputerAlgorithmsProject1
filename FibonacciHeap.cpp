#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <set>
#include <string>
#include <sstream>
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

    //Prints the entire tree but only works once :)
    void printTree_(FibonacciNode<T> *x) {
        if (x->printed == true) {
            if (x->parent != nullptr) cout << "] ";
            return;
        }
        x->printed = true;
        cout << x->data << " ";
        if (x->child != nullptr) { //If x has a child
            cout << "[ ";
            printTree_(x->child);
        }
        printTree_(x->rightNode);
    }

    //Merges two nodes together
    FibonacciNode<T>* merge(FibonacciNode<T> *x, FibonacciNode<T> *y) {
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
        return x;
    }

    //Merges the entire root list
    //The min pointer should always be maintained since
    //it'll always be pushed to the top
    void mergeRootList() {
        int maxDegree = floor(log2(size_)) + 1;
        vector<vector<FibonacciNode<T>*>> degreeList(maxDegree);
        FibonacciNode<T> *start = minNode;
        FibonacciNode<T> *currNode = minNode;

        do {
            degreeList[currNode->degree].push_back(currNode);
            currNode = currNode->rightNode;
        } while(currNode != start);

        for(int i = 0; i < degreeList.size(); ++i) {
            for (int j = 0; j+1 < degreeList[i].size(); j += 2) {
                currNode = merge(degreeList[i][j], degreeList[i][j+1]);
                degreeList[currNode->degree].push_back(currNode);
            }
        }
    }

    public:

    //Constructor
    FibonacciHeap() {
        minNode = nullptr;
        size_ = 0;
    }

    //Inserts a new node into the heap by value
    void insert(T key) {
        FibonacciNode<T> *node = new FibonacciNode<T>(key);
        if (minNode == nullptr) { //If list is empty
            minNode = node;
        } else { //If the list already has a node
            node->rightNode = minNode;
            node->leftNode = minNode->leftNode;
            minNode->leftNode->rightNode = node;
            minNode->leftNode = node;
            if (node->data < minNode->data) { //If the new node is less than the current min
                minNode = node;
            }
        }
        size_++;
    }

    void printTree() {
        if (size_ < 1) return;
        printTree_(minNode);
    }

    //Extracts the minimum values in the heap
    void extractMin() {
        if (!minNode) return;

        //If the minNode has child do a little extra work
        if (minNode->child != nullptr) {
            FibonacciNode<T> *heir = minNode->child;
            FibonacciNode<T> *currNode = minNode->child;

            //Disconnects the childs list from the parent
            minNode->child = nullptr;
            do {
                currNode->parent = nullptr;
                currNode->marked = false;
                currNode = currNode->rightNode;
            } while(currNode != heir);

            //Put the heirs list together with the root list
            FibonacciNode<T> *A = minNode->leftNode;
            FibonacciNode<T> *B = heir->leftNode;
            A->rightNode = heir;
            heir->leftNode = A;
            minNode->leftNode = B;
            B->rightNode = minNode;
        }

        //Keep a pointer to the node next to the minNode
        //So that we dont delete the minNode ptr
        //and then lose access to the list because
        //we don't have a pointer to it anymore
        FibonacciNode<T> *rightNode = minNode->rightNode;

        //Now that the children are taken care of
        //extract the minNode
        minNode->leftNode->rightNode = minNode->rightNode;
        minNode->rightNode->leftNode = minNode->leftNode;
        delete minNode;
        minNode = nullptr;
        --size_;

        if (size_ < 1) return;

        //From the ptr we kept before, find the next min
        minNode = rightNode;
        FibonacciNode<T> *currNode = rightNode;
        do {
            if (currNode->data < minNode->data) minNode = currNode;
            currNode = currNode->rightNode;
        } while(currNode != rightNode);
        
        mergeRootList();
    }

    void generateDot(FibonacciNode<T>* node, std::set<FibonacciNode<T>*>& visited, std::stringstream& ss) {
        if (!node || visited.count(node)) return;
        visited.insert(node);

        // Create the node label
        ss << "  node" << node << " [label=\"" << node->data << "\"];\n";

        // Link to Right Sibling (Circular)
        if (node->rightNode) {
            ss << "  node" << node << " -> node" << node->rightNode << " [color=blue, label=\"next\"];\n";
            generateDot(node->rightNode, visited, ss);
        }

        // Link to Child
        if (node->child) {
            ss << "  node" << node << " -> node" << node->child << " [style=bold, label=\"child\"];\n";
            generateDot(node->child, visited, ss);
        }
    }

    void printDot() {
        std::stringstream ss;
        std::set<FibonacciNode<T>*> visited;
        ss << "digraph G {\n";
        ss << "  rankdir=TB;\n";
        if (minNode) generateDot(minNode, visited, ss);
        ss << "}\n";
        cout << ss.str() << endl;
    }
};

int main() {
    FibonacciHeap<int> myList;
    for (int i = 0; i < 6; ++i) {
        myList.insert(0);
    }
    /*
    for (int i = 0; i < 6; ++i) {
        myList.extractMin();
    }
    */
    myList.extractMin();
    myList.extractMin();
    myList.printDot();
}