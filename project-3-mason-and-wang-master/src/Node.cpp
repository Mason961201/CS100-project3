#include "Node.hpp"
/*
 * This is the operator function used to compare two nodes
 */
bool Node::operator==(const Node& other){
    if(id == other.id){
        return true;
    }
        return false;
}
/*
 * This is the operator function used to compare two nodes
 */ 
bool Node::operator!=(const Node& other){
    if(id != other.id){
        return true;
    }
        return false;
}
bool Node::operator<(const Node& other){
    if( degree > other.degree){
        return true;
    }
    else if( degree < other.degree){
        return false;
    }
    else{
        return id>other.id;
    }
}
/*
 * this function is used to add friend into adj list
 */ 
void Node::push(int a){
    adj.push_back(a);
}
