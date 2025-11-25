// James Ma U52519908
#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <vector>
#include <stdexcept>

// simple min heap priorit queue, not using STL pq
template <typename T>
class MinPriorityQueue {
private:
    struct Node {
        unsigned long priority;
        T value;
    };
    std::vector<Node> heap;

    // move item up until heap is correct
    void heapifyUp(std::size_t idx) {
        while (idx > 0) {
            std::size_t parent = (idx - 1) / 2;
            if (heap[idx].priority >= heap[parent].priority) break;
            std::swap(heap[idx], heap[parent]);
            idx = parent;
        }
    }

    // move item down to keeo heap property
    void heapifyDown(std::size_t idx) {
        std::size_t n = heap.size();
        while (true) {
            std::size_t left = 2 * idx + 1;
            std::size_t right = 2 * idx + 2;
            std::size_t smallest = idx;

            if (left < n && heap[left].priority < heap[smallest].priority)
                smallest = left;
            if (right < n && heap[right].priority < heap[smallest].priority)
                smallest = right;
            if (smallest == idx) break;

            std::swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
    }
public:
    MinPriorityQueue() = default;

    bool empty() const {
        return heap.empty();
    }

    std::size_t size() const {
        return heap.size();
    }

    // add new value and priority
    void push(const T &value, unsigned long priority) {
        Node node{priority, value};
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }
    // get top value (smallest priority)
    const T &topValue() const {
        if (heap.empty()) throw std::runtime_error("priority queue empty");
        return heap.front().value;
    }
    unsigned long topPriority() const {
        if (heap.empty()) throw std::runtime_error("priority queue empty");
        return heap.front().priority;
    }

    // remove smallestelement
    void pop() {
        if (heap.empty()) throw std::runtime_error("priority queue empty");
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
    }
};

#endif
