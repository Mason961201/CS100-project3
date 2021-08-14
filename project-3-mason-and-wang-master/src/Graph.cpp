#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <sstream>
#include <string>
#include <utility>
#include "Node.hpp"
#include <queue>
#include <limits>
#include <set>
#include <functional>
using namespace std;
// construct and deconstruct
Graph::Graph(void)
    {
        nodes = {};
    }

Graph::~Graph(void) {
    for (auto itr : nodes) {
        //delete itr;
    }
}

/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */
//TODO
unordered_map<int,Node> Graph::get(){
    return this->nodes;
}

/* Read in relationships from an inputfile to create a graph */
/*
 * this function is used to readin data adn create a graph out of the data
 */
bool Graph::loadFromFile(const char* in_filename) {
    ifstream infile(in_filename);

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string s;
            if (!getline(ss, s, ' ')) break;
            record.push_back(s);
        }

        if (record.size() != 2) {
            continue;
        }

    //TODO - YOU HAVE THE PAIR OF IDS OF 2 FRIENDS IN 'RECORD'. WHAT DO NEED TO DO NOW? 
    // add them into the graph
        unordered_map<int,Node>::iterator itr;
        int id = stol(record[0]);
        int fri = stol(record[1]);
        itr = nodes.find(id);
        if(itr == nodes.end()){
            Node n(id);
            n.adj.push_back(fri);
            nodes.insert({id,n});
        }else{
            itr->second.adj.push_back(fri);
        }

        unordered_map<int,Node>::iterator itr1;
        itr1 = nodes.find(fri);
        if(itr1 == nodes.end()){
            Node n1(fri);
            n1.adj.push_back(id);
            nodes.insert({fri,n1});
        }else{
            itr1->second.adj.push_back(id);
        }
    }

    if (!infile.eof()) {
      cerr << "Failed to read " << in_filename << "!\n";
      return false;
    }

    infile.close();
    return true;
}

/* Implement pathfinder*/
//TODO 
// this function is used to find the shortest path between two nodes
bool Graph::pathfinder(Node* from, Node* to) {
    // this loop is used to set every nodes's dist to infinite and prev to null
    for ( unordered_map<int,Node>::iterator begin = nodes.begin(); 
          begin != nodes.end(); ++begin ){
        begin->second.dist = numeric_limits<int>::max();
        begin->second.prev = nullptr;
    }
    int curr;
    queue<int> q;
    q.push(from->id);
    unordered_map<int,Node>::iterator it = nodes.find(from->id);
    // following two if is used to check if the nodes are valid
    if( it == nodes.end()){
        return false;
    }
    it->second.dist = 0;
    it = nodes.find(to->id);
    if( it == nodes.end()){
        return false;
    }
    // loop untill the q is empty to check every nodes.
    while( !q.empty()){
        curr = q.front();
        q.pop();
        it = nodes.find(curr);
        for(unsigned int i=0;i<it->second.adj.size();i++){
            unordered_map<int,Node>::iterator neighbor = nodes.find(it->second.adj[i]);
            if( neighbor->second.dist == numeric_limits<int>::max() ){
                neighbor->second.prev = &(it->second);
                neighbor->second.dist = it->second.dist+1;
                q.push(neighbor->second.id);
            }
            if( neighbor->second.id == to->id ){
                break;
            }
        }
    }
    return true;
}
void Graph::setDegree() {
    for ( unordered_map<int,Node>::iterator begin = nodes.begin();
          begin != nodes.end(); ++begin ){
        begin->second.degree = begin->second.adj.size();
        begin->second.visit = false; 
    }
}
/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<int>& invitees, const int& k) {
    vector<Node*> node_queue;
    for ( unordered_map<int,Node>::iterator begin = nodes.begin();
          begin != nodes.end(); ++begin ){
        node_queue.push_back(&(begin->second));
    } 
    while(true){
        for( unsigned int d = 0; d < node_queue.size(); d++){        
            Node* cur = node_queue[d];
            if( cur->degree < k ){
                node_queue.erase(node_queue.begin()+d);
                for( unsigned int i =0; i < cur->adj.size(); i++ ){
                    int neighbor = cur->adj[i];
                    unordered_map<int,Node>::iterator itr = nodes.find(neighbor);
                    itr->second.degree--;
               }
            }
        }
        bool check = false;
        for ( unordered_map<int,Node>::iterator begin = nodes.begin();
              begin != nodes.end(); ++begin ){
            if( begin->second.degree >= k ){
                check = true;
            }
        }
        if( check == false ){
            break;
        }
        check = false;
        for( unsigned int x = 0; x < node_queue.size(); x++){
            Node* cur1 = node_queue[x];
            if( cur1->degree < k ){
                check = true;
            }
        }
        if( check == false ){
            break;
        }
    }
    for( unsigned int i = 0; i < node_queue.size(); i++ ){    
        Node* cur = node_queue[i];
        if( cur->degree >= k){
            cout<< "ID: "<< cur->id<<"Degree: "<<cur->degree<<'\n';
            invitees.push_back(cur->id);
        }
    }
    cout<<invitees.size()<<'\n';
    
}

