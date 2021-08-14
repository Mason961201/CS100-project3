#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include "Graph.hpp"
#include "Node.hpp"

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file test_pairs_file output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];
  char* pairs_filename = argv[2];
  char* output_filename = argv[3];

  //TODO   
 /* You can call the pathfinder function from here */
  Graph  graph;
  graph.loadFromFile(graph_filename);
  ifstream infile(pairs_filename);
  ofstream outfile(output_filename);
  // the following code is used to get two query int 
  while(infile){
    string s;
    if(!getline(infile,s)) break;

    istringstream ss(s);
    vector<string> record;

    while(ss){
      string s;
      if (!getline(ss,s,' ')) break;
      record.push_back(s);
    }

    if(record.size() != 2){
      continue;
    }
    unordered_map<int,Node>::iterator itr;
    itr = graph.nodes.find(stol(record[0]));
    if( itr == graph.nodes.end() ){
      outfile<<'\n';
      continue;
    }
    Node * from = &(itr->second);
    itr = graph.nodes.find(stol(record[1]));
    if( itr == graph.nodes.end() ){
      outfile<<'\n';
      continue;
    }
    Node * to = &(itr->second);
    if( to->id == from -> id ){
      outfile<<to->id<<'\n';
      continue;
    }
    bool check = graph.pathfinder( from, to );
    if( check == false ){
      outfile <<'\n';
      continue;
    }
    vector<int> answer;
    Node * curr = to;
    answer.push_back(curr->id);
    while( curr->prev != from ){
      curr = curr-> prev;
      answer.push_back(curr->id);
    }
    answer.push_back(from->id);
    // print answers into output file
    for (int i = answer.size()-1; i >= 0; i--){
      if( i != 0 ){
        outfile<<answer[i]<<' ';
      }
      else{
        outfile<<answer[i];
      }
    }
    answer.clear();
    outfile<<'\n';
  }
  
  infile.close();
  outfile.close();

  return 0;
    
}  
