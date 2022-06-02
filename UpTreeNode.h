//
// Created by ahmad on 1/3/2022.
//

#ifndef UNION_FIND_UPTREENODE_H
#define UNION_FIND_UPTREENODE_H

#include <stdlib.h>
template<class Key, class Data>
class Up_Tree_node {
public:
    Key key;
    Data data;
    Up_Tree_node<Key, Data> *parent;
    int size;
    double offset; // additional info - saleh

    Up_Tree_node(Key key, Data data,  Up_Tree_node<Key, Data> *parent, int size=1, int offset = 0) : key(key),
    data(data), parent(parent), size(size), offset(offset){}

    ~ Up_Tree_node();

    void setData(Data new_data);

};

template<class Key, class Data>
void  Up_Tree_node<Key, Data>::setData(Data new_data) {
    delete data;
    data = new_data;
}
template<class Key, class Data>
Up_Tree_node<Key, Data>::~Up_Tree_node<Key, Data>() {
    delete data;
    parent = nullptr;
}










#endif //UNION_FIND_UPTREENODE_H
