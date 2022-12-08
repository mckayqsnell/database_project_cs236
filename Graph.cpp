#include "Graph.h"

Graph::Graph(unsigned int size)
{
    for(unsigned int i = 0; i < size; i++)
    {
        graph[i] = set<int>();
        reverseGraph[i] = set<int>(); // make sure this is working.
    }
}

Graph::~Graph()
{
    //dtor
}

void Graph::addEdge(unsigned int from, unsigned int to)
{
    graph[from].insert(to);
    reverseGraph[to].insert(from);
}

void Graph::addNode(unsigned int node)
{
    graph[node];
    reverseGraph[node];
}

/*void Graph::set_graph(map<int, set<int>> graph)
{
    this->graph = graph;
} */

map<unsigned int, set<int>> Graph::get_graph()
{
    return graph;
}

string Graph::toString()
{
    stringstream ss;
    for(auto & it : graph)
    {
        ss << "R" << it.first << ":";
        for(int it2 : it.second)
        {
            ss << "R" << it2;
            //only print the comma if it is not the last element
            if(it2 != *it.second.rbegin())
            {
                ss << ",";
            }
        }
        ss << endl;
    }
    return ss.str();
}

void Graph::dfs_Forest()
{
    //Set all nodes to unvisited
    for(auto & it : graph)
    {
        visited[it.first] = false;
    }
    //For each node in the graph
    for(auto & it : graph)
    {
        //If the node has not been visited
        if(!visited[it.first])
        {
            //Run DFS on the node
            dfs(it.first);
        }
    }
}

set<int> Graph::dfs(int node)
{
    set<int> output;
    //Mark the given node as visited
    visited[node] = true;
    //for each node adjacent to the given node
    for(int it : graph[node])
    {
        //If the node has not been visited
        if(!visited[it])
        {
            //Run DFS on the node
            set<int> result = dfs(it);
            //Add stuff from result to output
            output.insert(result.begin(), result.end());
        }
    }
    //Add the node to the post order
    postOrder.push_back(node);
    output.insert(node);

    return output;
}

void Graph::dfs_Forest_Reverse(vector<unsigned int> post_order)
{
    vector<unsigned int> empty;
    // mark each node as unvisited
    for(auto & it : graph)
    {
        visited[it.first] = false;
    }
    // you will need to reverse the post order list
    reverse(post_order.begin(), post_order.end()); // Double check if this edits the orginal postOrder
    //cout << "DFS-FOREST-REVERSE" << "Post order after reverse: ";
    /*for(auto i : post_order)
    {
        cout << i;
        if(i != *post_order.rbegin())
        {
            cout << ",";
        }
    } */
    cout << endl;
    //for each Node N in PostOrder:
    for(auto & it : post_order)
    {
        //if N is unvisited
        if(!visited[it])
        {
            //create a new set S
            set<int> SCC;
            //run DFS2 on N, with S as the set of nodes in the current SCC
            dfs2(it, SCC);
            //add S to the list of SCCs
            SCCs.push_back(SCC);
        }
    }
}

void Graph::dfs2(int node, set<int> & scc)
{
    visited[node] = true;
    scc.insert(node);
    for(int it : graph[node])
    {
        if(!visited[it])
        {
            dfs2(it, scc);
        }
    }
}

vector<unsigned int> Graph::getPostOrder()
{
    return postOrder;
}

vector<set<int>> Graph::getSCCs()
{
    return SCCs;
}
