#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE> *vertexes;
    TE weight;

    void killSelf() {
        delete this;
    }

    Edge(Vertex<TV, TE> *v, TE w) {
        vertexes = v;
        weight = w;
    }
};

template<typename TV, typename TE>
struct Vertex {
    string id;
    TV data;
    std::list<Edge<TV, TE> *> edges;

    void killSelf() {
        delete this;
        this = nullptr;
    }
};

template<typename TV, typename TE>
class Graph {
protected:
    std::unordered_map<string, Vertex<TV, TE> *> vertexes;
    int totEdges = 0;

public:
    //TODO
    //Parser
    //Constructor, destructor
    //FindById, FindEdge(by starVertex, endVertex)
    //Density, connected, strongly connected, bipartite
    //{Kruskal, prim} (only undirected)
    Graph() {}

    virtual ~Graph() {}

    virtual bool insertVertex(string id, TV vertex) = 0;

    virtual bool createEdge(string id1, string id2, TE w) = 0;

    virtual bool deleteVertex(string id) = 0;

    virtual bool deleteEdge(string id1, string id2) = 0;

    virtual TE &operator()(string id1, string id2) = 0;

    virtual float density() = 0;

    virtual bool isDense(float threshold = 0.5) = 0;

    /*bool isConnected() = 0;

    bool isStronglyConnected() = 0;

    bool empty() = 0;

    void clear() = 0;
 */
    virtual void displayVertex(string id) = 0;

    virtual bool findById(string id) = 0;

    virtual void display() = 0;
};

#endif