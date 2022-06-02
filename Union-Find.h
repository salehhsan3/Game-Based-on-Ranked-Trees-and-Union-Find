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
    Company** elements_array; // saleh
    int size;

    explicit UnionFind(int size) : size(size) {
        elements = new Up_Tree_node<int ,Company*>*[size+1];
        // elements_array = new Company*[size+1]; // saleh
        for(int i=0; i <= size; i++){
            auto* new_group = new Company(i);
            // elements_array[i] = new_group; // saleh
            auto* new_node = new Up_Tree_node<int, Company*>(i, new_group, nullptr, 1);
            elements[i] = new_node;
        }
    }
    ~UnionFind(){
        for(int i = 0; i <= size; i++){
            delete elements[i];
            // delete elements_array[i]; // saleh
            elements[i] = nullptr;
            // elements_array[i] = nullptr; // saleh
        }
        delete[](elements);
        // delete[](elements_array); // saleh
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
            root2->offset += ( root1->data->getCompanyValue() ); // updating new info - saleh
            root1->size = size1 + size2;
            return root1;
        }
        // otherwise size1 <= size2
        root1->parent = root2;
        root1->offset += ( root2->data->getCompanyValue() ); // updating new info - saleh
        root2->size = size1 + size2;
        return root2;
    }

    Up_Tree_node<int, Company *> *find(int key){
        if(key > size) {
            return nullptr;
        }
        Up_Tree_node<int, Company*>* root = elements[key];
        double sum = 0; // saleh
        while(root->parent != nullptr){
            sum += root->offset; // saleh, the root should have an offset of 0!
            root = root->parent;
        }
        Up_Tree_node<int, Company*>* curr_node = elements[key];
        double tmp_offset = 0; // saleh
        while(curr_node->parent != nullptr) {
            Up_Tree_node<int, Company*> *tmp = curr_node->parent;
            curr_node->parent = root;
            tmp_offset = curr_node->offset; // saleh 
            curr_node->offset = sum; // saleh
            sum -= tmp_offset; // saleh
            curr_node = tmp;
        }
        return root;
    }

    double findOffSet(int key){
        // this function assumes that the key is legal!
        // passing an illegal key will result in unusual behavior!
        Up_Tree_node<int, Company*>* root = elements[key];
        double offset = 0; // saleh       
        double sum = 0; // saleh
        while(root->parent != nullptr){
            sum += root->offset; // saleh, the root should have an offset of 0!
            root = root->parent;
        }

        offset = sum; // saleh, this is the value to return!
        double tmp_offset = 0; // saleh
        Up_Tree_node<int, Company*>* curr_node = elements[key];
        
        while(curr_node->parent != nullptr) {
            Up_Tree_node<int, Company*> *tmp = curr_node->parent;
            curr_node->parent = root;
            tmp_offset = curr_node->offset; // saleh 
            curr_node->offset = sum; // saleh
            sum -= tmp_offset; // saleh
            curr_node = tmp;
        }
        // shrinking the paths shouldn't affect the offset therefore we're gooood!
        return offset;
    }
};
} // namespace ULIFB


#endif //UNION_FIND_UNION_FIND_H
