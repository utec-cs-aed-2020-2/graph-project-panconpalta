#ifndef UNDIRECweight_tDGRAPH_H
#define UNDIRECweight_tDGRAPH_H

#include "Graph.h"
/////////////////////////////////////////
#define undiGraph_t UnDirectedGraph<data_t, weight_t>
/////////////////////////////////////////

template<typename data_t, typename weight_t>
class UnDirectedGraph : public Graph<data_t, weight_t> {
private:

public:
    UnDirectedGraph();
    ~UnDirectedGraph();
    
	weight_t &operator()(id_t id1, id_t id2) override;
    float density() override;

    bool insertVertex(id_t id, data_t vertex) override;
    bool createEdge(id_t id1, id_t id2, weight_t w) override;
    bool deleteVertex(id_t id) override;
    bool deleteEdge(id_t id1, id_t id2) override;
    bool isDense(float threshold = 0.5) override;
    bool isConnected() override;
    bool isStronglyConnected() override;
    bool empty() override;
    bool findById(id_t id) override;

    void clear() override;
    void displayVertex(id_t id) override;
    void display() override;

	data_t operator[](id_t key);

	undiGraph_t execKruskal();
};
#endif
