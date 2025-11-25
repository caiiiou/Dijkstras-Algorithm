# COP 4530 – Programming Project 4 - James Ma
**Dijkstra’s Algorithm and Graph ADT**

This project implements an **undirected weighted Graph Abstract Data Type (ADT)** and performs **Dijkstra’s Algorithm** to find the shortest path between two vertices.  
It also includes a simple **priority queue (min-heap)** that I wrote instead of using STL’s `priority_queue`
---

## Files in This Project

### 1. `GraphBase.hpp`
This was the base class given by the professor.  
It defines the abstract interface that the `Graph` class must implement:
- `addVertex(label)`
- `removeVertex(label)`
- `addEdge(label1, label2, weight)`
- `removeEdge(label1, label2)`
- `shortestPath(startLabel, endLabel, path)`

My graph class inherits from this file.

---

### 2. `Graph.hpp`
This file declares the main `Graph` class.  
It uses an **adjacency list** to represent the graph and supports all basic operations.  
The methods are:
- `addVertex()` – adds a vertex if it doesn’t already exist  
- `removeVertex()` – removes a vertex and any edges connected to it  
- `addEdge()` – creates an edge between two existing vertices (undirected)  
- `removeEdge()` – deletes an edge between two vertices  
- `shortestPath()` – runs Dijkstra’s algorithm to compute the shortest distance and rebuilds the path

The adjacency list is stored as a `std::unordered_map<std::string, std::vector<std::pair<std::string, unsigned long>>>`.
---

### 3. `Graph.cpp`
Implements all methods declared in `Graph.hpp`.

- The graph stores vertices as strings and edge weights as unsigned longs.  
- The shortest path is computed with **Dijkstra’s Algorithm**, using the custom min-heap from `PriorityQueue.hpp`.  
- A `dist` map keeps track of the shortest known distance to each vertex.  
- A `prev` map stores the previous vertex in the path for reconstruction later.  
- The `shortestPath()` function also fills a vector `path` that contains the sequence of vertices from start to end.

I used a `visited` set to avoid revisiting nodes and to skip old queue entries when a better path was already found.

---

### 4. `PriorityQueue.hpp`
This is my custom **min priority queue** (basically a binary heap).  
It doesn’t use any STL priority queue.  
It stores nodes as pairs of `(priority, value)`.

Main functions:
- `push(value, priority)` – adds a new node  
- `pop()` – removes the smallest one  
- `topValue()` – returns the current top element  
- `topPriority()` – returns the smallest priority number  
- `empty()` – checks if the queue is empty  

The queue uses two helper functions:
- `heapifyUp()` and `heapifyDown()` to maintain the heap property.  
The heap is stored in a `std::vector`.

---

### 5. `main.cpp`
This file is for testing.  
It creates multiple graphs and runs Dijkstra to verify that everything works.

It includes **five test cases**:

#### Test 1 – Example from assignment
Uses the same vertices and edges from the project handout.  
Expected result: path `1 -> 3 -> 6 -> 5` with total cost **20**.

#### Test 2 – Disconnected graph
Graph where one vertex (`D`) has no connection.  
Checks if the function correctly returns “no path”.

#### Test 3 – Edge and vertex removal
Tests how removing an edge or vertex affects shortest path results.

#### Test 4 – Multiple shortest paths
Two equal-length routes from `A` to `E`.  
Makes sure the algorithm still finds one valid shortest path.

#### Test 5 – Single vertex graph
One vertex `X`, path from `X` to itself.  
Should return path `[X]` and cost **0**.

Each test prints the path and total cost to console.

---

## How To Compile

Use any standard C++17 or newer compiler.  
Example with `g++`:

```bash
g++ -std=c++17 main.cpp Graph.cpp -o dijkstra

