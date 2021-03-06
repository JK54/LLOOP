#!/bin/sh 
rm -rf ./Tmp/*
rm -rf ./Statistics/*
clang++ -std=c++11 -g -pedantic-errors -O3 -D DDO3 -D AVL_H -o ./Tmp/avl_h_o3 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O1 -D AVL_H -o ./Tmp/avl_h_o1 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O3 -D DDO3 -D AVL_L -o ./Tmp/avl_l_o3 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O1 -D AVL_L -o ./Tmp/avl_l_o1 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O3 -D DDO3 -D RBT -o ./Tmp/rbt_h_o3 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O1 -D RBT -o ./Tmp/rbt_h_o1 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O3 -D DDO3 -D BST -o ./Tmp/bst_h_o3 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O1 -D BST -o ./Tmp/bst_h_o1 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O3 -D DDO3 -D SET -o ./Tmp/set_h_o3 ./CompareBST.cpp
clang++ -std=c++11 -g -pedantic-errors -O1 -D SET -o ./Tmp/set_h_o1 ./CompareBST.cpp

echo "./Tmp/avl_h_o1;./Tmp/avl_h_o3"

echo "./Tmp/rbt_h_o3;./Tmp/bst_h_o1"

echo "./Tmp/rbt_h_o1;./Tmp/bst_h_o3"

echo "./Tmp/avl_l_o1;./Tmp/avl_l_o3"
