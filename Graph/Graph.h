#ifndef GRAPH_H
#define GRAPH_H

#include "utilityTypes.h"


template<typename data_t, typename weight_t>
class Graph {
protected:
    umap<id_t, vertex_t *> vertexes;
    int totEdges = 0;
public:

    Graph() {}

    virtual ~Graph() {}

    virtual bool insertVertex(id_t id, data_t vertex) = 0;

    virtual bool createEdge(id_t id1, id_t id2, weight_t w) = 0;

    virtual bool deleteVertex(id_t id) = 0;

    virtual bool deleteEdge(id_t id1, id_t id2) = 0;

    virtual weight_t &operator()(id_t id1, id_t id2) = 0;

    virtual float density() = 0;

    virtual bool isDense(float threshold = 0.5) = 0;

    virtual bool isConnected() = 0;

    virtual bool isBipartite() = 0;

    virtual bool empty() = 0;

    virtual void displayVertex(id_t id) = 0;

    virtual bool findVertex(id_t id) = 0;

    virtual bool findEdge(id_t id1, id_t id2) = 0;

    virtual void clear() = 0;

    virtual void display() = 0;
};

#endif
