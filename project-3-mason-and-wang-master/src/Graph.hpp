#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "Node.hpp"
#include <unordered_map>
#include <string>

using namespace std;
class Nodecmp{
  public:
    bool operator()(Node*& lhs, Node*& rhs) const{
      return *lhs < *rhs;
    }
};
class Nodecmp1{
  public:
    bool operator()(Node*& lhs, Node*& rhs) const{
      return !(*lhs < *rhs);
    }
};
class Graph {
 protected:
  //MAYBE ADD CLASS DATA STRUCTURE(S) HERE
  //unordered_map<int,Node> nodes;
 public:
  unordered_map<int,Node> nodes;

  Graph(void);

  ~Graph(void);
  //MAYBE ADD SOME MORE METHODS HERE SO AS TO ANSWER QUESTIONS IN YOUR PA
	
  /* YOU CAN MODIFY THIS IF YOU LIKE , in_filename : THE INPUT FILENAME */

  bool loadFromFile(const char* in_filename);

  bool pathfinder(Node * from, Node* to);
    
  void socialgathering(vector<int>& invitees, const int& k);
  
  unordered_map<int,Node> get();

  void setDegree();
};

#endif  // GRAPH_HPP
