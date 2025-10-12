#pragma once
#include <optional>

template<typename V>
struct QueueListNode {
    V value;
    QueueListNode *next;
    QueueListNode *prev;

    explicit QueueListNode(const V &val): value(val), next(nullptr), prev(nullptr) {
    }
};

template<typename V>
struct Queue {
    QueueListNode<V> *front;
    QueueListNode<V> *back;

    Queue(): front(nullptr), back(nullptr) {}
    
    ~Queue() {
        while (front != nullptr) {
            QueueListNode<V>* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

template<typename V>
void Enqueue(Queue<V>& q, const V& value);

template<typename V>
std::optional<V> Dequeue(Queue<V>& q);

template<typename V>
void RemoveNode(Queue<V>& q, QueueListNode<V>* node);

#include "queue.tpp"
