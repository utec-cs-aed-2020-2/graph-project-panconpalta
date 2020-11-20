//
// Created by AIO on 19/11/2020.
//

#ifndef GRAPH_PROJECT_PANCONPALTA_KRUSKAL_H
#define GRAPH_PROJECT_PANCONPALTA_KRUSKAL_H

//#include "UndirectedGraph.h"
template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class Kruskal {
private:
    undiGraph_t mst;
public:
    Kruskal(UnDirectedGraph<data_t, weight_t> *graph);
    ~Kruskal();
    undiGraph_t apply();
};

template<typename data_t, typename weight_t>
Kruskal<data_t, weight_t>::Kruskal(UnDirectedGraph<data_t, weight_t> *graph) {
    std::vector<id_t> vs(graph->vertexes.size());
    Kqueue_t EdgesToCheck;
    //Preparing for the algorithm
    for (auto it: graph->vertexes) {
        //making a copy of the graph without edges
        mst.insertVertex(it.first, it.second->data);
        //adding the vertexes to the disjoin set
        vs.push_back(it.first);
        //adding the edges to the priority queue
        for (auto edgePtr: it.second->edges) {
            //the edges are duplicated cuz the graph is undirected
            EdgesToCheck.push(std::make_pair(edgePtr->weight, edgePtr));
        }
    }
    dset_t VertexSets(vs);
    //Preparation done
    //Executing the algorithm
    edge_t *currentEdge = nullptr;
    while (!EdgesToCheck.empty()) {
        currentEdge = EdgesToCheck.top().second;
        EdgesToCheck.pop();
        //checking if the nodes of the edge are already conected
        if (VertexSets.Find(getIdOf(currentEdge->vertexes[0])) == VertexSets.Find(getIdOf(currentEdge->vertexes[1])))
            continue;
        //else
        VertexSets.Union(VertexSets.Find(getIdOf(currentEdge->vertexes[0])),
                         VertexSets.Find(getIdOf(currentEdge->vertexes[1])));
        mst.createEdge(getIdOf(currentEdge->vertexes[0]), getIdOf(currentEdge->vertexes[1]), currentEdge->weight);
    }
    vs.clear();
}

template<typename data_t, typename weight_t>
Kruskal<data_t, weight_t>::~Kruskal() {

}

template<typename data_t, typename weight_t>
UnDirectedGraph<data_t, weight_t> Kruskal<data_t, weight_t>::apply() {
    return mst;
}


#endif //GRAPH_PROJECT_PANCONPALTA_KRUSKAL_H
