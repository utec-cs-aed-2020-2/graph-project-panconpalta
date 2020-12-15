#pragma once

#ifdef NOCLION
#include "../Graph.h"
#else
#include "Graph.h"
#endif

#include <limits>

#define INFINITY std::numeric_limits<int>::max
#define AsPair std::pair<weight_t,vertex_t*>
#define openset_t MyQueue<AsPair,std::vector<AsPair>,std::greater<AsPair>>

template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class DirectedGraph;

template<typename data_t, typename weight_t>
class Astar {
    map<id_t, weight_t> gScore, fScore;

    weight_t (*h)(data_t, data_t) = nullptr;

    weight_t (*d)(data_t, data_t) = nullptr;

    umap<id_t, vertex_t *> vertexs;
    map<id_t, id_t> cameFrom;
    //bool undirected;
    openset_t openSet;

    void resetSets();

    UnDirectedGraph<data_t, weight_t> UnDiConstruct(id_t);

    DirectedGraph<data_t, weight_t> DiConstruct(id_t);

public:
    explicit Astar(UnDirectedGraph<data_t, weight_t> &, weight_t(*)(data_t, data_t), weight_t(*)(data_t, data_t));

    explicit Astar(DirectedGraph<data_t, weight_t> &, weight_t(*)(data_t, data_t), weight_t(*)(data_t, data_t));


    UnDirectedGraph<data_t, weight_t> UnDirectedApply(id_t, id_t);

    DirectedGraph<data_t, weight_t> DirectedApply(id_t, id_t);

    ~Astar();

};

template<typename data_t, typename weight_t>
Astar<data_t, weight_t>::Astar(UnDirectedGraph<data_t, weight_t> &graph, weight_t(*hfunc)(data_t, data_t),
                               weight_t(*dfunc)(data_t, data_t)):h(hfunc), d(dfunc) {
    for (const auto &it:graph.vertexes) {
        vertexs[it.first] = it.second;
    }
}

template<typename data_t, typename weight_t>
Astar<data_t, weight_t>::Astar(DirectedGraph<data_t, weight_t> &graph, weight_t(*hfunc)(data_t, data_t),
                               weight_t(*dfunc)(data_t, data_t)):h(hfunc), d(dfunc) {
    for (const auto &it:graph.vertexes) {
        vertexs[it.first] = it.second;
    }
}

template<typename data_t, typename weight_t>
UnDirectedGraph<data_t, weight_t> Astar<data_t, weight_t>::UnDirectedApply(id_t a, id_t b) {
    resetSets();
    gScore[a] = 0;
    fScore[a] = h(vertexs[a]->data, vertexs[b]->data);
    openSet.push(std::make_pair(fScore[a], vertexs[a]));
    vertex_t *current = nullptr;
    vertex_t *neighbor = nullptr;
    auto newGScore = INFINITY;

    while (!openSet.empty()) {
        current = openSet.top().second;
        openSet.pop();

        if (current->id == b) return UnDiConstruct(b);

        //check for al the neighbors and evaluate them
        for (const auto &edge:current->edges) {
            //just getting the neighbor
            neighbor = &(edge[0]);
            if (current->id == neighbor->id) neighbor = &(edge[1]);
            //gotten

            newGScore = gScore[current->id] + d(*current, *neighbor);
            //if the the new gscore is better then add it 
            if (newGScore < gScore[neighbor->id]) {
                cameFrom[neighbor->id] = current->id;
                gScore[neighbor->id] = newGScore;
                fScore[neighbor->id] = gScore[neighbor->id] + h(current->data, neighbor->data);
                //if the neighbor isn´t in the open set then add it
                if (openSet.find(std::make_pair(fScore[neighbor->id], vertexs[neighbor->id])) == openSet.end())
                    openSet.push(std::make_pair(fScore[neighbor->id], vertexs[neighbor->id]));
            }
        }
    }
    //if b is not reachable
    return UnDirectedGraph<data_t, weight_t>();
}

template<typename data_t, typename weight_t>
DirectedGraph<data_t, weight_t> Astar<data_t, weight_t>::DirectedApply(id_t a, id_t b) {
    resetSets();
    gScore[a] = 0;
    fScore[a] = h(vertexs[a]->data, vertexs[b]->data);
    openSet.push(std::make_pair(fScore[a], vertexs[a]));
    vertex_t *current = nullptr;
    vertex_t *neighbor = nullptr;
    auto newGScore = INFINITY;

    while (!openSet.empty()) {
        current = openSet.top().second;
        openSet.pop();

        if (current->id == b) return DiConstruct(b);

        //check for al the neighbors and evaluate them
        for (const auto &edge:current->edges) {
            //just getting the neighbor
            neighbor = &(edge[0]);
            if (current->id == neighbor->id) neighbor = &(edge[1]);
            //gotten

            newGScore = gScore[current->id] + d(*current, *neighbor);
            //if the the new gscore is better then add it 
            if (newGScore < gScore[neighbor->id]) {
                cameFrom[neighbor->id] = current->id;
                gScore[neighbor->id] = newGScore;
                fScore[neighbor->id] = gScore[neighbor->id] + h(current->data, neighbor->data);
                //if the neighbor isn´t in the open set then add it
                if (openSet.find(std::make_pair(fScore[neighbor->id], vertexs[neighbor->id])) == openSet.end())
                    openSet.push(std::make_pair(fScore[neighbor->id], vertexs[neighbor->id]));
            }
        }
    }
    //if b is not reachable
    return DirectedGraph<data_t, weight_t>();
}

template<typename data_t, typename weight_t>
UnDirectedGraph<data_t, weight_t> Astar<data_t, weight_t>::UnDiConstruct(id_t current) {
    UnDirectedGraph<data_t, weight_t> result;
    id_t next;
    result.insertVertex(current, vertexs[current]->data);
    while (vertexs.find(current) != vertexs.end()) {//while current has a predecesor
        next = current;
        current = cameFrom[current];
        result.insertVertex(current, vertexs[current]->data);
        result.createEdge(current, next, d(*vertexs[current], *vertexs[next]));
    }
    return result;
}

template<typename data_t, typename weight_t>
DirectedGraph<data_t, weight_t> Astar<data_t, weight_t>::DiConstruct(id_t current) {
    DirectedGraph<data_t, weight_t> result;
    id_t next;
    result.insertVertex(current, vertexs[current]->data);
    while (vertexs.find(current) != vertexs.end()) {//while current has a predecesor
        next = current;
        current = cameFrom[current];
        result.insertVertex(current, vertexs[current]->data);
        result.createEdge(current, next, d(*vertexs[current], *vertexs[next]));
    }
    return result;
}

template<typename data_t, typename weight_t>
void Astar<data_t, weight_t>::resetSets() {
    for (const auto &it: vertexs) {
        gScore[it.first] = INFINITY;
        fScore[it.first] = INFINITY;
    }
}

template<typename data_t, typename weight_t>
Astar<data_t, weight_t>::~Astar() {
    gScore.clear();
    fScore.clear();
    vertexs.clear();
    cameFrom.clear();
}
