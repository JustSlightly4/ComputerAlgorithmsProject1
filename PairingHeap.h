#ifndef PAIRINGHEAPH
#define PAIRINGHEAPH
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

template <typename K, typename T>
class PairingNode {
    public:
    K key;
    T data;
    PairingNode<K, T> *parent;
    PairingNode<K, T> *child;
    PairingNode<K, T> *leftSibling;
    PairingNode<K, T> *rightSibling;

    PairingNode(K key, T value) {
        this->key = key;
        this->data = value;
        this->parent = nullptr;
        this->child = nullptr;
        this->leftSibling = nullptr;
        this->rightSibling = nullptr;
    }
};

template <typename K,typename T>
class PairingHeap {
    private:
    PairingNode<K, T> *minNode;
    unordered_map<K, PairingNode<K, T>*> nodeMap;


    //Merges two root nodes together
    PairingNode<K, T>* merge(PairingNode<K, T>* x, PairingNode<K, T>* y) {

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

    PairingNode<K, T>* twoPassMerge(PairingNode<K, T>* first) {
        if (!first) return nullptr;

        // First pass: pair siblings left to right
        std::vector<PairingNode<K, T>*> mergedPairs;

        PairingNode<K, T>* curr = first;
        while (curr) {
            PairingNode<K, T>* a = curr;
            PairingNode<K, T>* b = curr->rightSibling;
            PairingNode<K, T>* next = nullptr;
            if (b) next = b->rightSibling;

            // Detach
            a->leftSibling = a->rightSibling = nullptr;
            if (b) b->leftSibling = b->rightSibling = nullptr;

            // Merge a and b
            mergedPairs.push_back(merge(a, b));

            curr = next;
        }

        // Second pass: merge right to left
        PairingNode<K, T>* result = nullptr;
        for (int i = mergedPairs.size() - 1; i >= 0; --i) {
            result = merge(result, mergedPairs[i]);
        }

        return result;
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
    void insert(K key, T value) {
        PairingNode<K, T> *node = new PairingNode<K, T>(key, value);
        nodeMap[key] = node;
        minNode = merge(minNode, node);
    }

    //Extracts the minimum value from the heap
    void extractMin() {
        if (!minNode) return;

        nodeMap.erase(minNode->key);

        PairingNode<K, T>* old = minNode;
        PairingNode<K, T>* children = minNode->child;

        // Clear parent pointers
        PairingNode<K, T>* currNode = children;
        while (currNode) {
            currNode->parent = nullptr;
            currNode = currNode->rightSibling;
        }

        delete old;
        minNode = twoPassMerge(children);
    }

    bool decreaseKey(K key, T value) {
        PairingNode<K, T> *node = nullptr;

        auto it = nodeMap.find(key); //Try to get an iterator to the node if it exist
        if (it == nodeMap.end()) return false; //If it does not exist return
        node = it->second; //Set node ptr equal to the found node
        if (node->data < value) return false; //Make sure this only decreases key
        node->data = value; //Update value

        PairingNode<K, T>* parent = node->parent;

        if (!parent) return true; // already root

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
        return true;
    }

    void print_(PairingNode<K, T> *node) {
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
    T GetMinValue() const {
        return minNode->data;
    }

    //Returns the current minimum value in the heap
    T GetMinKey() const {
        return minNode->key;
    }

    bool empty() {
        return (!minNode);
    }

    const T& operator[](const K& key) const {
        return nodeMap.find(key)->second->data;
    }

};
#endif