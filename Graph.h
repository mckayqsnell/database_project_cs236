#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <string>
//#include "Node.h"
#include <algorithm>

using namespace std;

class Graph {
private:
    map<unsigned int, set<int>> graph;
    map<unsigned int, set<int>> reverseGraph;
    vector<unsigned int> postOrder;
    vector<set<int>> SCCs;
    //store a boolean for each node to see if it has been visited
    map<unsigned int, bool> visited;
    //store a boolean for each node to see if it has been visited in the reverse graph
public:
    Graph(unsigned int size);
    ~Graph();
    string toString();
    void addEdge(unsigned int from, unsigned int to);
    void addNode(unsigned int node);
    //void set_graph(map<int, set<int>> graph);
    map<unsigned int, set<int>> get_graph();
    // dfs forest(in regular numerical order) on the reverse dependency graph to get the post order
    void dfs_Forest();
    // DFS-Forest (in reverse post-order) on the forward dependency graph to find the strongly connected components
    void dfs_Forest_Reverse(vector<unsigned int> post_order);
    set<int> dfs(int node);
    void dfs2(int node, set<int> & SCC);
    vector<unsigned int> getPostOrder();
    vector<set<int>> getSCCs();
};


#endif //PROJECT1_GRAPH_H
