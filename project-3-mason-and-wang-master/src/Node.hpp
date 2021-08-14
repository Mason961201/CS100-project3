#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <limits>
using namespace std;
/*
 * Node class has four fields:
 * id is the id for the person
 * adj is the vector of all friends the person has
 * dist is the distance between this node with others (we used in findpath)
 * prev is the the previous nodes it comes from
 */ 
class Node{
public:
    int const id;
    vector<int> adj;
    int dist;
    Node* prev;
    int degree;
    bool visit;
    bool visit1;
    Node(const int & d): id(d) {
	adj = {};
        visit1 = false;
        dist = numeric_limits<int>::max();
        prev = nullptr;
	degree = 0;
        visit = false;
    }
    bool operator<(const Node& other);   
    bool operator==(const Node& other);
    bool operator!=(const Node& other);
    void push (int a);

};

#endif // NODE_HPP


