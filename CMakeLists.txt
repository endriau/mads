cmake_minimum_required(VERSION 3.19)
project(tinylib C)

set(CMAKE_C_STANDARD 11)

add_library(tinylib
        data_structures/array.h data_structures/array.c
        data_structures/avl_tree.h data_structures/avl_tree.c
        stack.h stack.c
        uni_hash.h uni_hash.c
        algorithms/random.c algorithms/random.h
        algorithms/sort.h algorithms/sort.c
        pair.h pair.c
        data_structures/list.h data_structures/list.c
        heap.h heap.c
        hash_table.h has_table.c
        cuckoo_table.h cuckoo_table.c
        vertex.h vertex.c
        edge.c edge.h
        graph.h graph.c)
