#ifndef FIBONACCIHEAPH
#define FIBONACCIHEAPH
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
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
    FibonacciNode<T> *minNode; //The minimum node in the heap
    int size_; //How many nodes are currently in the heap

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

    //Writes the entire tree but only works once :)
    void writeTree_(ofstream& out, FibonacciNode<T> *x) {
        if (x->printed == true) {
            return;
        }
        out << x->data << " -> " << x->rightNode->data << " [tailport=e, headport=w];\n";
        //out << x->leftNode->data << " -> " << x->data << " [tailport=w, headport=w];\n";
        out << "{rank = same; " << x->data << "; " << x->leftNode->data << "; " << x->rightNode->data << "; }\n";
        if (x->parent != nullptr) out << x->data << " -> " << x->parent->data << "\n";
        x->printed = true;
        if (x->child != nullptr) { //If x has a child
            out << x->data << " -> " << x->child->data << "\n";
            writeTree_(out, x->child);
        }
        writeTree_(out, x->rightNode);
    }

    //Inserts a node into the tree by ptr
    //DOES NOT INCREASE THE SIZE!!
    void insert(FibonacciNode<T> *node) {
        if (minNode == nullptr) { //If list is empty
            minNode = node;
            minNode->rightNode = minNode;
            minNode->leftNode = minNode;
        } else { //If the list already has a node
            node->rightNode = minNode;
            node->leftNode = minNode->leftNode;
            minNode->leftNode->rightNode = node;
            minNode->leftNode = node;
            if (node->data < minNode->data) { //If the new node is less than the current min
                minNode = node;
            }
        }
    }

    //Cuts the given node out of the root list
    //User should still have pointer even
    //though its been removed from list
    //This is not meant to be used for anything
    //other than the root list!
    void cut(FibonacciNode<T> *y) {
        y->marked = false;
        y->leftNode->rightNode = y->rightNode;
        y->rightNode->leftNode = y->leftNode;
        y->leftNode = y;
        y->rightNode = y;
    }

    //Cuts the give node out of the list
    //where ever it may be and adds it back
    //to the root list
    void cascadingCut(FibonacciNode<T> *y) {

        //If y has a parent
        //There are three senarios
        //1: the parents direct child is y and y has no siblings
        //2: the parents direct child is y and y has siblings
        //3: the parents direct child is not y
        FibonacciNode<T>* parent = y->parent; //ptr to y's parent
        if (y->parent) {
            if (y->parent->child == y && y->rightNode == y) { //1: the parents direct child is y and y has no siblings
                y->parent->child = nullptr;
            } else if (y->parent->child == y) { //2: the parents direct child is y and y has siblings
                y->parent->child = y->rightNode;
            }
            --y->parent->degree;
            y->parent = nullptr;
        }

        //Cut out node and insert it into root list
        cut(y);
        insert(y);

        //Mark or cut parent
        if (parent) {
            if (!parent->marked) {
                parent->marked = true;
            } else {
                cascadingCut(parent);
            }
        }
    }

    //Merges two nodes together
    //Returns a ptr to the top level node
    FibonacciNode<T>* merge(FibonacciNode<T> *x, FibonacciNode<T> *y) {
        //If x > y then swap the pointers
        //So that x < y and can be the parent
        //always
        if (x->data > y->data) swap(x, y);

        //Cut y (the larger one) out of the list
        cut(y);

        //If x already has a child do some extra work
        if (x->child != nullptr) {
            y->rightNode = x->child;
            y->leftNode = x->child->leftNode;
            x->child->leftNode->rightNode = y;
            x->child->leftNode = y;
        }

        x->child = y;
        y->parent = x;
        ++x->degree;
        return x;
    }

    //Merges all the root nodes of the same degree together
    void mergeRootList() {

        //If the list is empty or if the list
        //only has one node do nothing
        if (size_ < 2) return;

        //Get the max degree of the list and make a
        //vector of fibonacci nodes that all all init to
        //nullptr
        int maxDegree = floor(log2(size_)) + 2;
        vector<FibonacciNode<T>*> degreeList(maxDegree, nullptr);

        //Get the number of roots that currently exist
        int rootCount = 0;
        FibonacciNode<T>* temp = minNode;
        do {
            rootCount++;
            temp = temp->rightNode;
        } while (temp != minNode);

        //Main loop. Loops through all original root nodes
        FibonacciNode<T>* currNode = minNode;
        for (int i = 0; i < rootCount; ++i) {

            //Advance the nextNode so that we always maintain a ptr
            //to the original root list
            FibonacciNode<T>* nextNode = currNode->rightNode;

            //Cut out the current node
            cut(currNode);

            //Check the current node against the degree list.
            //If a collision occurs, merge the two nodes.
            //Then, move the new node group up the table and repeat
            //until a free space in the list is found to put the group.
            while (degreeList[currNode->degree] != nullptr) {
                FibonacciNode<T>* other = degreeList[currNode->degree];
                degreeList[currNode->degree] = nullptr;
                currNode = merge(currNode, other);
            }

            //Place the new node group into the newly found free space
            //in the degree list.
            degreeList[currNode->degree] = currNode;

            //Advance the current node to be the next node
            //we kept before
            currNode = nextNode;
        }

        //All nodes should now be in the degree list and compacted consolodated together
        //So, simplely insert each index back into the tree if its not null.
        minNode = nullptr;
        for (auto* node : degreeList) {
            if (node) insert(node);
        }
    }

    public:
    //Constructor
    FibonacciHeap() {
        minNode = nullptr;
        size_ = 0;
    }

    //Deconstructor
    ~FibonacciHeap() {
        while(minNode) {
            extractMin();
        }
    }

    //Returns the size of the list
    int size() {
        return size_;
    }

    //Inserts a new node into the heap by value/key
    FibonacciNode<T>* insert(T value) {
        FibonacciNode<T>* node = new FibonacciNode<T>(value);
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
        return node;
    }

    void print() {
        if (size_ < 1) return;
        printTree_(minNode);
        cout << "\n";
    }

    //This writes the structure of the tree to a .dot file.
    //This file can then be copy and pasted to GraphvizOnline
    //to be able to visualize the tree
    void writeTree() {
        if (size_ < 1) return;
        ofstream out("heap.dot");
        out << "digraph FibonacciHeap {\n";
        out << "  node [shape=circle];\n";
        out << "  minNode -> " << minNode->data << "\n";
        writeTree_(out, minNode);
        out << "\n}";
    }

    //Returns the current minimum value in the heap
    T min() const {
        return minNode->data;
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

    void decreaseKey(FibonacciNode<T> *y, T value) {
        if (y->data < value) return; //Make sure this only decreases key
        y->data = value;
        if (y->parent) { //If y has a parent
            if (y->parent->data > y->data) { //If y is now less than its parent
                cascadingCut(y);
            }
        } else { //If y has no parent is it less than the minNode?
            if (y->data < minNode->data) minNode = y;
        }
    }
};
#endif