#ifndef CIRCULARLYLINKEDLIST
#define CIRCULARLYLINKEDLIST
#include <iostream>
#include <vector>
using namespace std;

//This is a single node for a doubly linked list
template <typename T>
class node {
    public:
    node *prevNode;
    node *nextNode;
    T data;

    //Constructor
    node(T value) {
        prevNode = nullptr;
        nextNode = nullptr;
        data = value;
    }
};

//The definition for a circlely
template <typename T>
class CircularlyLinkedList {
    private:
    int size_;
    node<T> *frontPtr;
    node<T> *backPtr;

    public:
    //Constructor
    CircularlyLinkedList() {
        size_ = 0;
        frontPtr = nullptr;
        backPtr = nullptr;
    }

    //Deconstructor
    ~CircularlyLinkedList() {
        this->clear();
    }

    //Pushes a single node to the backPtr of the list
    void push_back(T value) {

        //If the list is empty,
        //create a node and have it
        //point to itself both ways
        if (size_ < 1) {
            node<T> *ptr = new node<T>(value);
            ptr->nextNode = ptr;
            ptr->prevNode = ptr;
            frontPtr = ptr;
            backPtr = ptr;

        //If the list have > 0 nodes,
        //1. Create the new node
        //2. Make the backPtr node next ptr point to the new node
        //3. Make the new node prev ptr point to the backPtr node
        //4. Make the new node next ptr point to the first node
        //5. Make the first node prev ptr point to the new node
        } else {
            node<T> *ptr = new node<T>(value);
            backPtr->nextNode = ptr;
            ptr->prevNode = backPtr;
            ptr->nextNode = frontPtr;
            frontPtr->prevNode = ptr;
            backPtr = ptr;
        }
        ++size_;
    }

    //Uses push_front then just moves the frontPtr and backPtr ptrs
    void push_front(T value) {
        push_back(value);
        frontPtr = frontPtr->prevNode;
        backPtr = backPtr->prevNode;
    }

    //Destroys the entire list
    void clear() {
        if (size_ < 1) return;
        while(size_ > 0) {
            pop_back();
        }
    }

    //Prints the list from the frontPtr node to the last node
    void print() {
        if (size_ < 1) return;
        node<T> *ptr = frontPtr;
        do {
            cout << ptr->data << " ";
            ptr = ptr->nextNode;
        } while(ptr != frontPtr);
    }

    //Continues to print the list for a set amount of times
    //starting from the frontPtr
    void print(int amt) {
        if (size_ < 1) return;
        node<T> *ptr = frontPtr;
        for (int i = 0; i < amt; ++i) {
            cout << ptr->data << " ";
            ptr = ptr->nextNode;
        }
    }

    //General pop function for popping any node
    void pop(node<T> *curr) {
        if (size_ < 1) return;
        node<T> *prev = curr->prevNode;
        node<T> *next = curr->nextNode;
        prev->nextNode = next;
        next->prevNode = prev;
        curr->prevNode = nullptr;
        curr->nextNode = nullptr;
        delete curr;
        curr = nullptr;
        --size_;

        //If the list is now empty make sure the
        //frontPtr and backPtr ptrs are not dangling
        //just in case
        if (size_ < 1) {
            frontPtr = nullptr;
            backPtr = nullptr;
        }
    }

    //Removes the last element in the list
    void pop_back() {
        if (size_ < 1) return;
        node<T> *nodeToDelete = backPtr;
        backPtr = backPtr->prevNode;
        pop(nodeToDelete); //Delete the node
    }

    //Move the frontPtr and backPtr ptrs then pops the backPtr element
    void pop_front() {
        if (size_ < 1) return;
        node<T> *nodeToDelete = frontPtr;
        frontPtr = frontPtr->nextNode;
        pop(nodeToDelete); //Delete the node
    }

    //Pops a node by value
    void pop_value(T value) {
        if (size_ < 1) return;

        //Handle if the value is in the frontPtr
        if (frontPtr->data == value) {
            pop_front();
            return;
        }

        //Handle if the value is in the backPtr
        if (backPtr->data == value) {
            pop_back();
            return;
        }

        //Start at the beginnning and traverse the list until
        //the correct value is reached then delete that node.
        //If the frontPtr of the list is reached then the value
        //is not in the list
        node<T> *currNode = frontPtr;
        for (int i = 0; i < size_; ++i) {
            currNode = currNode->nextNode;
            if (currNode->data == value) break;
        }
        if (currNode == frontPtr) return; //No value is found
        pop(currNode); //Delete the node
    }

    //Pops a node by index
    void pop_index(int index) {
        if (size_ < 1 || index >= size_) return; //If outside bounds return

        //Handle if index is the frontPtr
        if (index == 0) {
            pop_front();
            return;
        }

        //Handle if index is the backPtr
        if (index == size_-1) {
            pop_back();
            return;
        }

        //Start at the beginnning and traverse the list until
        //the correct index is reached then delete that node
        node<T> *currNode = frontPtr;
        for (int i = 0; i < index; ++i) {
            currNode = currNode->nextNode;
        }
        pop(currNode); //Delete the node
    }

    void shift_left() {
        if (size_ < 1) return;
        frontPtr = frontPtr->prevNode;
        backPtr = backPtr->prevNode;
    }

    void shift_right() {
        if (size_ < 1) return;
        frontPtr = frontPtr->nextNode;
        backPtr = backPtr->nextNode;
    }

    node<T>* front() {
        if (size_ < 1) {
            throw std::runtime_error("Error: Circularly linked list is empty when accessing frontPtr!");
        }
        return frontPtr;
    }

    node<T>* back() {
        if (size_ < 1) {
            throw std::runtime_error("Error: Circularly linked list is empty when accessing backPtr!");
        }
        return backPtr;
    }

    //Overloads the [] operator for read and write access
    T& operator[](int index) {
        if (size_ < 1) {
            throw std::runtime_error("Error: Circularly linked list is empty when accessed by index!");
        }
        if (index < 0 || index >= size_) {
            throw std::runtime_error("Error: Circularly linked list accessed out of range!");
        }
        if (index == 0) return front();
        if (index == size_-1) return back();
        node<T> *ptr = frontPtr;
        for (int i = 0; i < index; ++i) {
            ptr = ptr->nextNode;
        }
        return ptr;
    }

    //Returns the size_ of the linked list
    int size() {
        return size_;
    }
};
#endif