//
// Created by ahmad on 1/3/2022.
//

#ifndef UNION_FIND_UNION_FIND_H
#define UNION_FIND_UNION_FIND_H

#include "UpTreeNode.h"
#include "Company.h"

namespace ULIFB
{
    class UnionFind {
public:
    Up_Tree_node<int ,Company*>** elements;
    int size;

    explicit UnionFind(int size) : size(size) {
        elements = new Up_Tree_node<int ,Company*>*[size+1];
        for(int i=0; i <= size; i++){
            auto* new_group = new Company(i);
            auto* new_node = new Up_Tree_node<int, Company*>(i, new_group, nullptr, 1);
            elements[i] = new_node;
        }
    }
    ~UnionFind(){
        for(int i = 0; i <= size; i++){
            delete elements[i];
            elements[i] = nullptr;
        }
        delete[](elements);
    }

    Up_Tree_node<int, Company*>* UnionGroups(int key1, int key2){
        if(key1 > size || key2 > size || key1 == key2){
            return nullptr;
        }
        Up_Tree_node<int,Company*>* root1 = find(key1);
        Up_Tree_node<int,Company*>* root2 = find(key2);

        if(root1->parent != nullptr || root2->parent != nullptr || root2 == root1){
            return nullptr;
        }
        int size1 = root1->size;
        int size2 = root2->size;
        // merge trees in DS
        if(size1 > size2 || (size1 == size2 && root1->key > root2->key)){
            root2->parent = root1;
            root1->size = size1 + size2;
            return root1;
        }
        root1->parent = root2;
        root2->size = size1 + size2;
        return root2;
    }

    Up_Tree_node<int, Company *> *find(int key){
        if(key > size) {
            return nullptr;
        }
        Up_Tree_node<int, Company*>* root = elements[key];
        while(root->parent != nullptr){
            root = root->parent;
        }
        Up_Tree_node<int, Company*>* curr_node = elements[key];
        while(curr_node->parent != nullptr) {
            Up_Tree_node<int, Company*> *tmp = curr_node->parent;
            curr_node->parent = root;
            curr_node = tmp;
        }
        return root;
    }
};
} // namespace ULIFB


#endif //UNION_FIND_UNION_FIND_H
