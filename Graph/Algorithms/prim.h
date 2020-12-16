#ifndef GRAPH_PROJECT_PANCONPALTA_PRIM_H
#define GRAPH_PROJECT_PANCONPALTA_PRIM_H

#ifdef NOCLION
#include "../Graph.h"
#else
#include "Graph.h"
#endif


template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class Prim {
    umap<id_t, vertex_t *> v;
    std::vector<std::tuple<id_t, id_t, weight_t>> prim;
public:
    explicit Prim(UnDirectedGraph<data_t, weight_t> &graph, id_t start);

    ~Prim();

    UnDirectedGraph<data_t, weight_t> apply();
};

template<typename data_t, typename weight_t>
Prim<data_t, weight_t>::Prim(UnDirectedGraph<data_t, weight_t> &graph, id_t start) {
    if (!graph.findVertex(start))
        throw std::out_of_range("Graph does not contain vertex");

    std::vector<id_t> vs;
    uset<id_t> visited;
    Pqueue_t EdgesToCheck;
    vs.push_back(start);
    v.insert({start, graph.vertexes[start]});
    for (auto &edgePtr: graph.vertexes[start]->edges) {
        EdgesToCheck.push(std::make_pair(edgePtr->weight, edgePtr));
        edgePtr->vertexes[0].id != start ? vs.push_back(edgePtr->vertexes[0].id) : vs.push_back(
                edgePtr->vertexes[1].id);
    }
    visited.insert(start);
    edge_t *currentEdge = nullptr;
    dset_t VertexSets(vs);

    while (!EdgesToCheck.empty()) {
        currentEdge = EdgesToCheck.top().second;
        EdgesToCheck.pop();
        if (VertexSets.Find(getIdOf(currentEdge->vertexes[0])) == VertexSets.Find(getIdOf(currentEdge->vertexes[1])))
            continue;
        VertexSets.Union(VertexSets.Find(getIdOf(currentEdge->vertexes[0])),
                         VertexSets.Find(getIdOf(currentEdge->vertexes[1])));

        if (v.find(getIdOf(currentEdge->vertexes[0])) == v.end())
            v.insert({getIdOf(currentEdge->vertexes[0]),
                      graph.vertexes[getIdOf(currentEdge->vertexes[0])]});
        if (v.find(getIdOf(currentEdge->vertexes[1])) == v.end())
            v.insert({getIdOf(currentEdge->vertexes[1]),
                      graph.vertexes[getIdOf(currentEdge->vertexes[1])]});

        prim.push_back({getIdOf(currentEdge->vertexes[0]), getIdOf(currentEdge->vertexes[1]), currentEdge->weight});

        for (int i = 0; i < 2; ++i) {
            auto current_v = currentEdge->vertexes[i].id;
            if (visited.find(current_v) == visited.end()) {
                for (auto &edgePtr: graph.vertexes[current_v]->edges) {
                    auto other_v =
                            edgePtr->vertexes[0].id != current_v ? edgePtr->vertexes[0].id : edgePtr->vertexes[1].id;
                    if (visited.find(other_v) == visited.end()) {
                        EdgesToCheck.push(std::make_pair(edgePtr->weight, edgePtr));
                        VertexSets.Add(other_v);
                    }
                }
                visited.insert(current_v);
            }
        }
    }
    vs.clear();
    visited.clear();
}

template<typename data_t, typename weight_t>
Prim<data_t, weight_t>::~Prim() {
    v.clear();
    prim.clear();
}

template<typename data_t, typename weight_t>
UnDirectedGraph<data_t, weight_t> Prim<data_t, weight_t>::apply() {
    UnDirectedGraph<data_t, weight_t> tree;
    for (auto &it : v)
        tree.insertVertex(it.first, it.second->data);
    for (auto &it : prim)
        tree.createEdge(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    return tree;
}


#endif //GRAPH_PROJECT_PANCONPALTA_PRIM_H
