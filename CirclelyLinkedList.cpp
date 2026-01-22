#include <iostream>
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
    int size;
    node<T> *front;
    node<T> *back;

    //General pop function for popping any node
    void pop(node<T> *curr) {
        if (size < 1) return;
        node<T> *prev = curr->prevNode;
        node<T> *next = curr->nextNode;
        prev->nextNode = next;
        next->prevNode = prev;
        curr->prevNode = nullptr;
        curr->nextNode = nullptr;
        delete curr;
        --size;

        //If the list is now empty make sure the
        //front and back ptrs are not dangling
        //just in case
        if (size < 1) {
            front = nullptr;
            back = nullptr;
        }
    }

    //General push function for pushing any node
    void push() {

    }

    public:
    //Constructor
    CircularlyLinkedList() {
        size = 0;
        front = nullptr;
        back = nullptr;
    }

    //Deconstructor
    ~CircularlyLinkedList() {
        this->clear();
    }

    //Pushes a single node to the back of the list
    void push_back(T value) {

        //If the list is empty,
        //create a node and have it
        //point to itself both ways
        if (size < 1) {
            node<T> *ptr = new node<T>(value);
            ptr->nextNode = ptr;
            ptr->prevNode = ptr;
            front = ptr;
            back = ptr;

        //If the list have > 0 nodes,
        //1. Create the new node
        //2. Make the back node next ptr point to the new node
        //3. Make the new node prev ptr point to the back node
        //4. Make the new node next ptr point to the first node
        //5. Make the first node prev ptr point to the new node
        } else {
            node<T> *ptr = new node<T>(value);
            back->nextNode = ptr;
            ptr->prevNode = back;
            ptr->nextNode = front;
            front->prevNode = ptr;
            back = ptr;
        }
        ++size;
    }

    //Uses push_front then just moves the front and back ptrs
    void push_front(T value) {
        push_back(value);
        front = front->prevNode;
        back = back->prevNode;
    }

    //Destroys the entire list
    void clear() {
        if (size < 1) return;
        node<T> *currPtr = front;
        node<T> *nextPtr = front;
        front->prevNode->nextNode = nullptr;
        while(currPtr != nullptr) {
            nextPtr = nextPtr->nextNode;
            currPtr->prevNode = nullptr;
            currPtr->nextNode = nullptr;
            delete currPtr;
            currPtr = nextPtr;
        }
        size = 0;
    }

    //Prints the list from the front node to the last node
    void print() {
        if (size < 1) return;
        node<T> *ptr = front;
        do {
            cout << ptr->data << " ";
            ptr = ptr->nextNode;
        } while(ptr != front);
    }

    //Continues to print the list for a set amount of times
    //starting from the front
    void print(int amt) {
        if (size < 1) return;
        node<T> *ptr = front;
        for (int i = 0; i < amt; ++i) {
            cout << ptr->data << " ";
            ptr = ptr->nextNode;
        }
    }

    //Removes the last element in the list
    void pop_back() {
        if (size < 1) return;
        node<T> *nodeToDelete = back;
        back = back->prevNode;
        pop(nodeToDelete); //Delete the node
    }

    //Move the front and back ptrs then pops the back element
    void pop_front() {
        if (size < 1) return;
        node<T> *nodeToDelete = front;
        front = front->nextNode;
        pop(nodeToDelete); //Delete the node
    }

    //Pops a node by value
    void pop_value(T value) {

        //Handle if the value is in the front
        if (front->data == value) {
            pop_front();
            return;
        }

        //Handle if the value is in the back
        if (back->data == value) {
            pop_back();
            return;
        }

        //Start at the beginnning and traverse the list until
        //the correct value is reached then delete that node.
        //If the front of the list is reached then the value
        //is not in the list
        node<T> *currNode = front;
        for (int i = 0; i < size; ++i) {
            currNode = currNode->nextNode;
            if (currNode->data == value) break;
        }
        if (currNode == front) return; //No value is found
        pop(currNode); //Delete the node
    }

    //Pops a node by index
    void pop_index(int index) {
        if (size < 1 || index >= size) return; //If outside bounds return

        //Handle if index is the front
        if (index == 0) {
            pop_front();
            return;
        }

        //Handle if index is the back
        if (index == size-1) {
            pop_back();
            return;
        }

        //Start at the beginnning and traverse the list until
        //the correct index is reached then delete that node
        node<T> *currNode = front;
        for (int i = 0; i < index; ++i) {
            currNode = currNode->nextNode;
        }
        pop(currNode); //Delete the node
    }

    void shift_left() {
        front = front->prevNode;
        back = back->prevNode;
    }

    void shift_left(int amt) {
        for (int i = 0; i < amt; ++i) {
            front = front->prevNode;
            back = back->prevNode;
        }
    }

    void shift_right() {
        front = front->nextNode;
        back = back->nextNode;
    }

    void shift_right(int amt) {
        for (int i = 0; i < amt; ++i) {
            front = front->nextNode;
            back = back->nextNode;
        }
    }
};

int main() {
    CircularlyLinkedList<int> myList;
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i);
    }
    myList.shift_right();
    myList.print();
}