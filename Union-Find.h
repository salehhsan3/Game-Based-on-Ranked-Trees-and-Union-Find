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
    Up_Tree_node<long long int ,Company*>** elements;
    // Company** elements_array; // saleh
    long long int size;

    explicit UnionFind(long long int size) : size(size) {
        elements = new Up_Tree_node<long long int ,Company*>*[size+1];
        // elements_array = new Company*[size+1]; // saleh
        for(long long int i=0; i <= size; i++){
            auto* new_group = new Company(i);
            // elements_array[i] = new_group; // saleh
            auto* new_node = new Up_Tree_node<long long int, Company*>(i, new_group, nullptr, 1);
            elements[i] = new_node;
        }
    }
    ~UnionFind(){
        for(long long int i = 0; i <= size; i++){
            delete elements[i];
            elements[i] = nullptr;
        }
        delete[](elements);
    }


    Up_Tree_node<long long int, Company*>* UnionGroups(long long int key1, long long int key2, long double val_inc){
        if(key1 > size || key2 > size || key1 == key2){
            return nullptr;
        }
        Up_Tree_node<long long int,Company*>* root1 = find(key1);
        Up_Tree_node<long long int,Company*>* root2 = find(key2);

        if(root1->parent != nullptr || root2->parent != nullptr || root2 == root1){
            return nullptr;
        }
        long long int size1 = root1->size;
        long long int size2 = root2->size;
        // merge trees in DS
        // if(size1 > size2 || (size1 == size2 && root1->key > root2->key)){
        if(size1 >= size2 ){
            root2->parent = root1;
            root2->offset += ( val_inc + root1->data->getCompanyValue() - root2->data->getCompanyValue());
            root1->data->updateEnterpriseValue( val_inc + root1->data->getEnterpriseValue() );
            root1->size = size1 + size2;
            return root1;
        }
        // otherwise size1 <= size2
        root1->parent = root2;
        // root1->offset += ( root2->data->getCompanyValue() - root1->data->getCompanyValue() ); // + val_inc - val_inc
        // root2->offset += val_inc;
        root1->offset += ( root2->data->getCompanyValue() - val_inc - root1->data->getCompanyValue() );
        root2->data->updateEnterpriseValue( val_inc + root1->data->getEnterpriseValue() );
        root2->size = size1 + size2;
        return root2;
    }

    Up_Tree_node<long long int, Company *> *find(long long int key){
        if(key > size) {
            return nullptr;
        }
        
        Up_Tree_node<long long int, Company*>* root = elements[key];
        Up_Tree_node<long long int, Company*>* new_parent = elements[key];
        long double sum = 0; // saleh
        while(root != nullptr){
            sum += root->offset; 
            if (root->parent == nullptr)
            {
                new_parent = root;
            }
            root = root->parent;
        }
        if (key != new_parent->key)
        {
            sum -= new_parent->offset;
        }
        
        Up_Tree_node<long long int, Company*>* curr_node = elements[key];
        long double tmp_offset = 0; // saleh
        while(curr_node->parent != nullptr) {
            Up_Tree_node<long long int, Company*> *tmp = curr_node->parent;
            curr_node->parent = new_parent;
            tmp_offset = curr_node->offset; // saleh 
            curr_node->offset = sum; // saleh
            sum -= tmp_offset; // saleh
            curr_node = tmp;
        }
        return new_parent;
    }

    long double findOffSet(long long int key){
        // this function assumes that the key is legal!
        // passing an illegal key will result in unusual behavior!
        
        Up_Tree_node<long long int, Company*>* root = elements[key];
        Up_Tree_node<long long int, Company*>* new_parent = elements[key];
        
        long double offset = 0; // saleh       
        long double sum = 0; // saleh
        while(root != nullptr){
            sum += root->offset; 
            if (root->parent == nullptr)
            {
                new_parent = root;
            }
            root = root->parent;
        }

        offset = sum ; // saleh, this is the value to return!
        if (key != new_parent->key)
        {
            offset -= new_parent->offset;
            sum -= new_parent->offset;
        }
        
        long double tmp_offset = 0; // saleh
        Up_Tree_node<long long int, Company*>* curr_node = elements[key];
        while(curr_node->parent != nullptr) {
            Up_Tree_node<long long int, Company*> *tmp = curr_node->parent;
            curr_node->parent = new_parent;
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
