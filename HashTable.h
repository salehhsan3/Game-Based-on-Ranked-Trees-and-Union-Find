//
// Created by ahmad on 1/4/2022.
//

#ifndef UNION_FIND_H_HASHTABLE_H
#define UNION_FIND_H_HASHTABLE_H

#include "list.h"
#define ARR_INITIAL_SIZE 50

template<class Data>
class hash_table{
public:
    int arr_size;
    int elements_num;
    LList<int,Data>** arr;

    hash_table():arr_size(ARR_INITIAL_SIZE), elements_num(0), arr(new LList<int, Data>*[ARR_INITIAL_SIZE]){
        for(int i=0; i<ARR_INITIAL_SIZE; i++){
            arr[i] = new LList<int, Data>();
        }
    }

    void addElement(int id, Data data){
        arr[id % arr_size]->addNode(id, data);
        elements_num++;
        if(elements_num >= arr_size){
            int new_size = arr_size * 2;
            auto** new_arr = new LList<int, Data>*[new_size];
            for(int i=0; i<new_size; i++){
                new_arr[i] = new LList<int, Data>();
            }
            for(int i = 0; i<arr_size; i++){
                Node<int, Data>* tmp = arr[i]->head->next;
                while(tmp != arr[i]->tail){
                    int id = tmp->key;
                    new_arr[id % new_size]->addNode(id, *tmp->data);
                    tmp = tmp->next;
                }
            }
            for(int i = 0; i < arr_size; i++){
                delete(arr[i]);
            }
            delete[](arr);
            arr = new_arr;
            arr_size = new_size;
        }
    }

    void deleteElement(int id){
        arr[id % arr_size]->deleteNode(id);
        elements_num--;
        if(elements_num <= arr_size/2 && arr_size>ARR_INITIAL_SIZE){
            int new_size = arr_size / 2;
            auto** new_arr = new LList<int, Data>*[new_size];
            for(int i=0; i<new_size; i++){
                new_arr[i] = new LList<int, Data>();
            }
            for(int i = 0; i<arr_size; i++){
                Node<int, Data>* tmp = arr[i]->head->next;
                while(tmp != arr[i]->tail){
                    int id = tmp->key;
                    new_arr[id % new_size]->addNode(id, *tmp->data);
                    tmp = tmp->next;
                }
            }
            for(int i = 0; i < arr_size; i++){
                delete(arr[i]);
            }
            delete[](arr);
            arr = new_arr;
            arr_size = new_size;
        }
    }

    Node<int, Data> *Find(int id){
        return arr[id%arr_size]->findNode(id);
    }

    void DeleteHashTable()
    {
        for (int i = 0; i < arr_size; ++i) {
            delete(arr[i]);
            arr[i] = nullptr; // saleh
        }
        delete[](arr);
        arr = nullptr; // saleh
        arr_size = 0; // saleh
        elements_num = 0; // saleh
    }

    ~hash_table(){
        DeleteHashTable(); // used to have the lines within DeleteHashTable()
    }

    // void MergeHashTable(hash_table<Data> *other) // saleh
    // {
    //     LList<int,Data>* current_list = other->arr[0];
    //     for (int i = 0; i < other->arr_size; i++) // maybe arr_size+1
    //     {
    //         current_list = other->arr[i];
    //         Node<int, Data>* current_node = current_list->head->next;
    //         while (current_node != current_list->tail)
    //         {
    //             this->addElement(current_node->key,*current_node->data);
    //             current_node = current_node->next;
    //         }
    //     }
    // }

    // void MoveHashTableIntoArray(Data* data_array,int index) // saleh
    // {
    //     LList<int,Data>* current_list = this->arr[0];
    //     for (int i = 0; i < this->arr_size; i++) // maybe arr_size+1
    //     {
    //         current_list = this->arr[i];
    //         Node<int, Data>* current_node = current_list->head->next;
    //         while (current_node != current_list->tail)
    //         {
    //             data_array[i] = *(current_node->data);
    //             index++; // theoritically it should stop at elements_num
    //             current_node = current_node->next;
    //         }
    //     }
    // }

    int getNumberOfElements()
    {
        return(this->elements_num);
    }
};






#endif //UNION_FIND_H_HASHTABLE_H
