cmake_minimum_required(VERSION 3.19)
project(tinylib C)

set(CMAKE_C_STANDARD 11)

add_library(tinylib
        array.h array.c
        avl_tree.h avl_tree.c
        stack.h stack.c
        uni_hash.h uni_hash.c
        random.c random.h
        sort.h sort.c
        pair.h pair.c
        list.h list.c
        heap.h heap.c
        hash_table.h has_table.c
        cuckoo_table.h cuckoo_table.c
        vertex.h vertex.c
        edge.c edge.h
        graph.h graph.c)
