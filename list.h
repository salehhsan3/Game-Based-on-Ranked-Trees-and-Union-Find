//
// Created by Smart on 04/01/2022.
//

#ifndef HASHTABLE_LIST_H
#define HASHTABLE_LIST_H


template<class Key, class Data>
class Node{
public:
    Key key;
    Data* data;
    Node<Key, Data>* next;
    Node<Key, Data>* prev;
    Node();
    Node(Key key, Data data);
    Node(Key key, Data data, Node *next, Node *prev);
    ~Node();
    bool operator==(const Node &other) const;
    bool operator!=(const Node &other) const;
    bool operator>(const Node &other) const;
    bool operator<(const Node &other) const;
    bool operator>=(const Node &other) const;
    bool operator<=(const Node &other) const;
};

template<class Key, class Data>
Node<Key,Data>::~Node<Key, Data>() {
    delete data;
    data = nullptr;
    next = nullptr;
    prev = nullptr;
}

template<class Key, class Data>
Node<Key, Data>::Node(): key(0) {
    data = nullptr;
    next = nullptr;
    prev = nullptr;
}

template<class Key, class Data>
Node<Key, Data>::Node(Key key, Data data): key(key), data(new Data(data)){
    next = nullptr;
    prev = nullptr;
}

template<class Key, class Data>
Node<Key, Data>::Node(Key key, Data data, Node<Key, Data> *next, Node<Key, Data> *prev):
        key(key), data(new Data(data)), next(next), prev(prev){}

template<class Key, class Data>
bool Node<Key, Data>::operator==(const Node<Key, Data> &other) const {
    return (other.key == key);
}

template<class Key, class Data>
bool Node<Key, Data>::operator!=(const Node<Key, Data> &other) const {
    return (!(*this == other));
}

template<class Key, class Data>
bool Node<Key, Data>::operator>(const Node<Key, Data> &other) const {
    return (key > other.key);
}

template<class Key, class Data>
bool Node<Key, Data>::operator<(const Node<Key, Data> &other) const {
    return (other > *this);
}

template<class Key, class Data>
bool Node<Key, Data>::operator>=(const Node<Key, Data> &other) const {
    return (!(key < other.key));
}

template<class Key, class Data>
bool Node<Key, Data>::operator<=(const Node<Key, Data> &other) const {
    return (other >= *this);
}



template<class Key, class Data>
class LList{
public:
    Node<Key, Data>* head;
    Node<Key, Data>* tail;
    long long int list_size;
    LList();
    LList(Node<Key, Data> *head, Node<Key, Data> *tail, long long int size);
    ~LList();
    Node<Key, Data> *findNode(Key key);
    void addNode(Key key, Data data);
    void deleteNode(Key key);
};

template<class Key, class Data>
LList<Key, Data>::LList(): list_size(0){
    head = new Node<Key, Data>();
    tail = new Node<Key, Data>();
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;
}

template<class Key, class Data>
LList<Key, Data>::LList(Node<Key, Data> *head, Node<Key, Data> *tail, long long int size):
        head(head), tail(tail), list_size(size){}

template<class Key, class Data>
Node<Key, Data>* LList<Key, Data>::findNode(Key key) {
    Node<Key, Data>* tmp = this->head->next;
    while (tmp != this->tail){
        if(tmp->key == key){
            return tmp;
        }
    tmp = tmp->next;
    }
    return nullptr;
}


template<class Key, class Data>
void LList<Key, Data>::addNode(Key key, Data data) {
    if(findNode(key)){
        return;
    }
    Node<Key, Data>* new_node =  new Node<Key, Data>(key, data);
    tail->prev->next = new_node;
    new_node->prev = tail->prev;
    new_node->next = tail;
    tail->prev = new_node;
    list_size++;
}


template<class Key, class Data>
void LList<Key, Data>::deleteNode(Key key) {
    if (!findNode(key)){
        return;
    }
    Node<Key, Data>* tmp = findNode(key);
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    delete(tmp);
    list_size--;
}

template<class Key, class Data>
LList<Key, Data>::~LList() {
    Node<Key, Data> *tmp = head->next;
    while (tmp != tail) {
        Node<Key, Data> *to_delete = tmp;
        tmp = tmp->next;
        deleteNode(to_delete->key);
    }
    delete (tail);
    delete (head);
}





#endif //HASHTABLE_LIST_H
