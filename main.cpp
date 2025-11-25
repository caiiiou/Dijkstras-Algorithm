//James Ma U52519908
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "Graph.hpp"

//helper function that just prints a path vector nicely
void printPath(const std::vector<std::string> &path) {
    for (size_t i =0; i < path.size();i++) {
        std::cout << path[i];
        if (i + 1 < path.size()) std::cout << " -> ";
    }
    std::cout << "\n";
}

// test case 1: the same example from the projecthandout
void testCase1() {
    std::cout << "\nTest 1: example graph\n";

    Graph g;
    // make verticez
    std::vector<std::string> v = {"1","2","3","4","5","6"};
    for (auto &x : v)
        g.addVertex(x);
    // add edges with weights
    std::vector<std::tuple<std::string, std::string, unsigned long>> e = {
        {"1","2",7}, {"1","3",9}, {"1","6",14},
        {"2","3",10}, {"2","4",15},
        {"3","4",11}, {"3","6",2},
        {"4","5",6}, {"5","6",9}
    };

    for (auto &x : e)
        g.addEdge(std::get<0>(x), std::get<1>(x), std::get<2>(x));

    // find shortest path from 1 to 5
    std::vector<std::string> path;
    unsigned long cost = g.shortestPath("1","5",path);

    // output result
    std::cout << "cost: " << cost << "\npath: ";
    printPath(path);
}

// test case 2: a graph with a disconnected vertex
void testCase2() {
    std::cout << "\nTest 2: disconnected graph\n";
    Graph g;
    // make 4 vertices, D is isolated
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    // only A-B-C are connected
    g.addEdge("A","B",5);
    g.addEdge("B","C",3);

    // test shortest path to the isolated vertex
    std::vector<std::string> path;
    unsigned long cost = g.shortestPath("A","D",path);

    // check if there's no path theunt
    if (cost == std::numeric_limits<unsigned long>::max()) {
        std::cout << "no path from A to D\n";
    } else {
        std::cout << "cost: " << cost << " path: ";
        printPath(path);
    }
}

// test case 3: remove edge and vertex and see how shortest path changes
void testCase3() {
    std::cout << "\nTest 3: remove edge and vertex\n";

    Graph g;
    for (auto v : {"A","B","C","D"})
        g.addVertex(v);

    // connect all in a small network
    g.addEdge("A","B",1);
    g.addEdge("B","C",2);
    g.addEdge("C","D",3);
    g.addEdge("A","D",10);

    std::vector<std::string> path;
    unsigned long cost = g.shortestPath("A","D",path);
    std::cout << "before remove, cost=" << cost << " path=";
    printPath(path);

    // remove an important edge
    g.removeEdge("B","C");
    cost = g.shortestPath("A","D",path);
    std::cout << "after removing edge, cost=" << cost << " path=";
    printPath(path);

    // now remove a whole vertex
    g.removeVertex("C");
    cost =g.shortestPath("A","D",path);
    std::cout << "after removing vertex, cost=" << cost << " path=";
    printPath(path);
}

// test case 4: multiple shortest paths with same cost
void testCase4() {
    std::cout << "\nTest 4: equal-length paths\n";

    Graph g;

    //build a small diamond shape graph
    for (auto v : {"A","B","C","D","E"})
        g.addVertex(v);

    g.addEdge("A","B",2);
    g.addEdge("B","E",2);
    g.addEdge("A","C",2);
    g.addEdge("C","E",2);
    g.addEdge("B","C",3); // longer middle connection

    // both A->B->E and A->C->E have same cost 4
    std::vector<std::string> path;
    unsigned long cost = g.shortestPath("A","E",path);
    std::cout << "cost: " << cost << " path: ";
    printPath(path);
}

// test case : single vertex graph (start and end are same)
void testCase5() {
    std::cout << "\nTest 5: single vertex\n";

    Graph g;
    g.addVertex("X");
    std::vector<std::string> path;
    unsigned long cost = g.shortestPath("X","X",path);

    // should be 0 cost and path is just X
    std::cout << "cost: " << cost << " path: ";
    printPath(path);
}

// maun runs all test cases
int main() {
    std::cout << "*Running...*\n";

    testCase1(); // normal working graph
    testCase2(); //noconnection
    testCase3(); // removal test
    testCase4(); // equal path test
    testCase5(); // single vertex
    std::cout<<"\n*Finished*\n";
    return 0;
}
