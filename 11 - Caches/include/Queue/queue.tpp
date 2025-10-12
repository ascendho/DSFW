#pragma once

template<typename V>
void Enqueue(Queue<V>& q, const V& value) {
    auto* node = new QueueListNode<V>(value);
    if (q.back == nullptr) {
        q.front = node;
        q.back = node;
    } else {
        q.back->next = node;
        node->prev = q.back;
        q.back = node;
    }
}

template<typename V>
std::optional<V> Dequeue(Queue<V>& q) {
    if (q.front == nullptr)
        return std::nullopt;

    auto value = q.front->value;
    QueueListNode<V>* temp = q.front;
    q.front = q.front->next;
    if (q.front == nullptr)
        q.back = nullptr;
    else
        q.front->prev = nullptr;
    
    delete temp;
    return value;
}

template<typename V>
void RemoveNode(Queue<V>& q, QueueListNode<V>* node) {
    if (node == nullptr)
        return;
        
    if (node->prev != nullptr)
        node->prev->next = node->next;
    if (node->next != nullptr)
        node->next->prev = node->prev;
    if (node == q.front)
        q.front = q.front->next;
    if (node == q.back)
        q.back = q.back->prev;
    
    delete node;
}
