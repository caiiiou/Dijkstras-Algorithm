// James Ma U52519908
#include "Graph.hpp"
#include <limits>        // for numeric_limits
#include <unordered_set> // for visited set
#include <algorithm>     // for std::remove_if, std::reverse

// constructor and destructor
Graph::Graph() = default;
Graph::~Graph()= default;

// check if a vertex exists in the map
bool Graph::vertexExists(const std::string &label) const {
    return adj.find(label) != adj.end();
}
/* add a vertex to the graph            theertex
 if it already exists, we just ignore it*/
void Graph::addVertex(std::string label) {
    if (!vertexExists(label)) {
        adj[label] = {}; // make an empty list of edges
    }
}

// remove a vertex and all the edges connected to it
void Graph::removeVertex(std::string label) {
    if (!vertexExists(label)) return;

    // first remove all edges that go to this vertex
    for (auto &entry : adj) {
        auto &neighbors = entry.second;
        neighbors.erase(
            std::remove_if(neighbors.begin(), neighbors.end(),
                           [&](const std::pair<std::string, unsigned long> &p) {
                               return p.first == label;
                           }),
            neighbors.end()
        );
    }

    // now remove the vertex itself
    adj.erase(label);
}

// add an undirected edge between two vertices
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    // make sure both vertices exist and are different
    if (!vertexExists(label1) || !vertexExists(label2) || label1 == label2) {
        return;
    }

    // check if the edge already exists(so we don't duplicate)
    auto &neighbors1 = adj[label1];
    for (const auto &p : neighbors1) {
        if (p.first ==label2) {
            return; // edge already there
        }
    }
    // add the edge in both directions since this is undirected
    neighbors1.emplace_back(label2, weight);
    adj[label2].emplace_back(label1, weight);
}

// remove an undirected edge
void Graph::removeEdge(std::string label1, std::string label2) {
    if (!vertexExists(label1) || !vertexExists(label2)) return;

    // remove label2 from label1's neighbor list
    auto &neighbors1 = adj[label1];
    neighbors1.erase(
        std::remove_if(neighbors1.begin(), neighbors1.end(),
                       [&](const std::pair<std::string, unsigned long> &p) {
                           return p.first == label2;
                       }),
        neighbors1.end()
    );

    // also remove label1 from label2's list
    auto &neighbors2 = adj[label2];
    neighbors2.erase(
        std::remove_if(neighbors2.begin(), neighbors2.end(),
                       [&](const std::pair<std::string, unsigned long> &p) {
                           return p.first == label1;
                       }),
        neighbors2.end()
    );
}

// finds the shortest path using dijkstra's algorithm
// stores the path in 'path' and returns total cost
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel,std::vector<std::string> &path) {
    path.clear();

    // check that both vertices are real
    if (!vertexExists(startLabel) || !vertexExists(endLabel)) {
        return std::numeric_limits<unsigned long>::max();
    }

    // dist map holds shortest distance from start
    std::unordered_map<std::string, unsigned long>dist;
    // prev helps rebuild the final path
    std::unordered_map<std::string, std::string> prev;

    const unsigned long INF = std::numeric_limits<unsigned long>::max();

    // initialize all distances to infinity
    for (const auto &entry : adj) {
        dist[entry.first] = INF;
    }
    dist[startLabel] = 0; // start has distance 0

    // our custom min priority queue
    MinPriorityQueue<std::string> pq;
    pq.push(startLabel, 0);

    std::unordered_set<std::string>visited;

    // main dijkstra loop
    while (!pq.empty()) {
        std::string u =pq.topValue();      // current vertex
        unsigned long d = pq.topPriority(); // its distance
        pq.pop();

        // if we already saw this vertex, skip it
        if (visited.find(u) != visited.end()) continue;
        visited.insert(u);

        //if we ggot to the end, we can stop early
        if (u == endLabel) break;

        // ignore outdated entries
        if (d > dist[u]) continue;

        // check all its neighbors
        for (const auto &edge : adj[u]) {
            const std::string &v = edge.first;
            unsigned long w = edge.second;

            // if we foundaaa shorter path to v through u
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w; // update distance
                prev[v] = u;
                pq.push(v, dist[v]);   // add neighbor to queue
            }
        }
    }

    //if endLabel is still INF, there’s no path
    if (dist[endLabel] == INF) {
        return INF;
    }
    // rebuild path by going backwards
    std::string current = endLabel;
    while (current != startLabel) {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(startLabel);

    // reverseso it goes from start to end
    std::reverse(path.begin(), path.end());

    // return total cost (shortest distance)
    return dist[endLabel];
}
