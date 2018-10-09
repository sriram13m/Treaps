Treap = include/Treap.h src/Treap.cc
Treap_Test = $(Treap) test/Treap.cpp

treap : $(Treap_Test)
	g++ -o treap test/Treap.cpp -Wall --std=c++17 -g3
