#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

template<typename data_t, typename weight_t>
struct Edge;

template<typename data_t, typename weight_t>
struct Vertex;

template<typename data_t, typename weight_t>
class Graph;

/////////////////////////////////////////////////
#define id_t std::string
#define vertex_t Vertex<data_t, weight_t>   
#define edge_t Edge<data_t, weight_t>       
#define graph_t Graph<data_t, weight_t>     
#define dset_t DisjoinSetArray<id_t>
#define Kpair_t std::pair<weight_t, edge_t*>
#define Kqueue_t std::priority_queue<Kpair_t, std::vector<Kpair_t>, std::greater<Kpair_t>>
#define stack_t std::stack<vertex_t*>
#define queue_t std::queue<vertex_t*>
/////////////////////////////////////////////////

template<typename data_t, typename weight_t>
struct Edge {
    vertex_t *vertexes;
    weight_t weight;

    void killSelf() {
        delete this;
    }

    Edge(vertex_t *v, weight_t w) {
        vertexes = v;
        weight = w;
    }
};

template<typename data_t, typename weight_t>
struct Vertex {
    id_t id;
    data_t data;
    std::list<edge_t *> edges;

    void killSelf() {
        delete this;
        this = nullptr;
    }
};

template<typename data_t, typename weight_t>
class Graph {
protected:
    std::unordered_map<id_t, vertex_t *> vertexes;
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

    virtual bool insertVertex(id_t id, data_t vertex) = 0;

    virtual bool createEdge(id_t id1, id_t id2, weight_t w) = 0;

    virtual bool deleteVertex(id_t id) = 0;

    virtual bool deleteEdge(id_t id1, id_t id2) = 0;

    virtual weight_t &operator()(id_t id1, id_t id2) = 0;

    virtual float density() = 0;

    virtual bool isDense(float threshold = 0.5) = 0;

    /*bool isConnected() = 0;

    bool isStronglyConnected() = 0;

    bool empty() = 0;

    void clear() = 0;
 */
    virtual void displayVertex(id_t id) = 0;

    virtual bool findById(id_t id) = 0;

    virtual void display() = 0;
};

#endif
