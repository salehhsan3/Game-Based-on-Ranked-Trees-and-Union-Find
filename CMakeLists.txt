cmake_minimum_required(VERSION 3.16)
project(DS_WET_2)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(DS_WET_2
        Employee.cpp
        Employee.h
        AO_Tree_node.h
        AO_AVL_Tree.h
        HashTable.h
        list.h
        Union-Find.h
        UpTreeNode.h
        MultiStructures.cpp
        MultiStructures.h
        Company.cpp
        Company.h
        Industry.cpp
        Industry.h
        library2.cpp
        library2.h
        main2.cpp)