//
// Created by luca eaton on 3/11/26.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <vector>
using namespace std;
class Vertex;
class Edge;
class Graph {
private:
    unordered_map<long long, vector<Vertex*>> adj_;
    vector<Edge*> edges_;

public:

};
// We need an edge list to begin with. Idk how we get that edge list but its possible
/*
 * for (const auto& e : edge)
 *      adj[e[0]].push_back(e[1]);
*/

/* Assume I have edges_ = vector<Edge*>
 * for (const auto& e : edges_)
 *  Vertex* src = edge->getSource();
 *  Vertex* dest = edge->getDest();
 *  adj[src].push_back(dest);
*/
// {v1 : v2, ..., vn}
// unordered_map<Vertex, vector<Vertex>>
// you have to define a custom hash function for vertices


#endif //GRAPH_H
