#ifndef GRAPH_PROJECT_PANCONPALTA_KRUSKAL_H
#define GRAPH_PROJECT_PANCONPALTA_KRUSKAL_H

#ifdef NOCLION
#include "../Graph.h"
#else
#include "Graph.h"
#endif


template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class Kruskal {
private:
    umap<id_t, vertex_t *> v;
    std::vector<std::tuple<id_t, id_t, weight_t>> kruskal;
public:
    explicit Kruskal(UnDirectedGraph<data_t, weight_t> const &graph);

    ~Kruskal();

    UnDirectedGraph<data_t, weight_t> apply();
};

template<typename data_t, typename weight_t>
Kruskal<data_t, weight_t>::Kruskal(UnDirectedGraph<data_t, weight_t> const &graph) {
    std::vector<id_t> vs(graph.vertexes.size());
    Kqueue_t EdgesToCheck;
    for (auto it: graph.vertexes) {
        v.insert({it.first, it.second});
        vs.push_back(it.first);
        for (auto edgePtr: it.second->edges) {
            EdgesToCheck.push(std::make_pair(edgePtr->weight, edgePtr));
        }
    }
    dset_t VertexSets(vs);
    edge_t *currentEdge = nullptr;
    while (!EdgesToCheck.empty()) {
        currentEdge = EdgesToCheck.top().second;
        EdgesToCheck.pop();
        if (VertexSets.Find(getIdOf(currentEdge->vertexes[0])) == VertexSets.Find(getIdOf(currentEdge->vertexes[1])))
            continue;
        VertexSets.Union(VertexSets.Find(getIdOf(currentEdge->vertexes[0])),
                         VertexSets.Find(getIdOf(currentEdge->vertexes[1])));
        kruskal.push_back({getIdOf(currentEdge->vertexes[0]), getIdOf(currentEdge->vertexes[1]), currentEdge->weight});
    }
    vs.clear();
}

template<typename data_t, typename weight_t>
Kruskal<data_t, weight_t>::~Kruskal() {
    v.clear();
    kruskal.clear();
}

template<typename data_t, typename weight_t>
UnDirectedGraph<data_t, weight_t> Kruskal<data_t, weight_t>::apply() {
    UnDirectedGraph<data_t, weight_t> tree;
    for (auto &it : v)
        tree.insertVertex(it.first, it.second->data);
    for (auto &it : kruskal)
        tree.createEdge(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    return tree;
}


#endif //GRAPH_PROJECT_PANCONPALTA_KRUSKAL_H
