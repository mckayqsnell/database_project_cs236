#ifndef PROJECT1_NODE_H
#define PROJECT1_NODE_H
#include <set>
#include <iostream>

using namespace std;

class Node {
public:
    int id;
    set<int> adjacencies;
    bool visited;
    bool isSelfInDependent;
    Node() {
        visited = false;
    }
    ~Node() {}
};


#endif //PROJECT1_NODE_H
