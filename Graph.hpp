// James Ma U52519908
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include "PriorityQueue.hpp"
#include <unordered_map>
#include <vector>
#include <string>

// graph class that use adjacency list (undirected weighted)
class Graph : public GraphBase {
public:
    Graph();
    virtual ~Graph();

    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string startLabel,
                               std::string endLabel,
                               std::vector<std::string> &path) override;
private:
    // map vertex to lis of (neighbor, weight)
    std::unordered_map<std::string, std::vector<std::pair<std::string, unsigned long>>> adj;

    bool vertexExists(const std::string &label) const;
};

#endif
