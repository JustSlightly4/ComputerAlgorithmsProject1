By Eric Ryan Montgomery, Randy Hannah, and André Bodge  
CS 470: Comparative Analysis of Priority Queues in Graph Algorithms

# Table of Contents
- [Introduction](#introduction)
- [Heap Information](#heap-information)
  - [Insert](#insertion-into-the-heaps)
  - [Extract Minimum](#extract-minimum-from-the-heaps)
  - [Get Minimum Value](#retrieve-the-minimum-nodes-value-from-the-heaps)
  - [Get Minimum Key](#retrieve-the-minimum-nodes-key-from-the-heaps)
  - [Decrease Key](#decrease-a-nodes-value-in-the-heaps)
  - [Is Empty?](#check-to-see-if-a-heap-is-empty)
- [Testing Information](#testing-information)
- [Coding Conventions](#coding-conventions)
<br>
<br>

# Introduction
The goal of this project is to understand the theoretical complexities of different heaps, their practical performance, implementation complexity, and trade-offs. To achieve this goal, a Fibonacci heap, a Pairing heap, and a binary heap has been constructed along with both Prim's and Dijkstra's algorithms in C++. The file "HeapTesting.cpp" is used to test a standalone version of the heaps while "AlgorithmTesting.cpp" is used to test the heap within both Prim's and Dijkstra's algorithms.
<br>
<br>

# Heap Information
Within this project, all three heaps have been designed to be modular with each other. So, their primary functions will be described for all three not specific to a single heap.
<br>

### Insertion into the heaps:
To insert into one of the heaps, the function declaration is as follows:
```
void insert(K key, T value)
```
<br>

### Extract Minimum from the heaps:
To extract the minimum value from one of the heaps, the function declaration is as follows:
```
void extractMin()
```
Importantly, the extractMin function does not return the node, its key, or its value. The GetMinValue or GetMinKey functions must be used to retrieve the minimum nodes information.
<br>
<br>

### Retrieve the minimum nodes value from the heaps:
To retrieve the minimum nodes value (the node that has a value less than all the other nodes in the heap), the function declaration is as follows:
```
T GetMinValue()
```
<br>

### Retrieve the minimum nodes key from the heaps:
To retrieve the minimum nodes key (the node that has a value less than all the other nodes in the heap), the function declaration is as follows:
```
K GetMinKey()
```
<br>

### Decrease a nodes value in the heaps:
To decrease a nodes value in the heap, the function declaration is as follows:
```
bool decreaseKey(K key, T value)
```
The decrease key function will return false if the given key was not found in the heaps unordered map or if the new value provided is greater than the previous value. Otherwise, the decrease key function will return true.
<br>
<br>

### Check to see if a heap is empty:
To check to see if a heap is empty or not, the function declaration is as follows:
```
bool empty()
```
Returns true if the heap is empty and returns false if the heap has at least one node.
<br>
<br>

# Testing Information
To test all the heaps the file "HeapTesting.cpp" is used to test a standalone version of each of them while "AlgorithmTesting.cpp" is used to test the heap within both Prim's and Dijkstra's algorithms. All testing data collected within this project is stored in the "TestingData" folder and the numbers beside the algorithms name stand for the density of the graph used.

### Heap Testing
To use the heap testing C++ file, the function needed along with the heap type must be swapped out on line 60. Once that is the following command is used to compile the file:
```
g++ HeapTesting.cpp
```
To run the file, the following command must then be provided to the terminal:
```
./a.out size(int)
```
<br>

### Algorithm Testing
To use algorithm testing C++ file, the file needs to be compiled with the following command:
```
g++ AlgorithmTest.cpp
```
To run the file, the following command must then be provided to the terminal:
```
./a.out HeapType(Heap, Fib, Pair) AlgorithmType(Prim, Dijk) GraphSize(int) GraphConnectivity(int) GraphSeed(int)
```
<br>
<br>

# Coding Conventions
### Variables: camelCase
```
int myInteger;
string myStringForMyProgram;
```
<br>

### Functions: UpperCase  
```
void MyFunction() {}
int MySecondFunction() {}
```
<br>

### Classes: UpperCase

```
//Vector3D.h
class Vector3D {
    private:
        int x;
        int y;
        int z;
    public:
        Vector3D::Vector3D(int i, int j, int k) {
          ...
        }

        void PrintComponents() {
          ...
        }
}
```
