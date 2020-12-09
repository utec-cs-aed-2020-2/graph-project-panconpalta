#ifndef GRAPH_PROJECT_PANCONPALTA_BELLMANFORD_H
#define GRAPH_PROJECT_PANCONPALTA_BELLMANFORD_H

#include "Graph.h"

template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class DirectedGraph;


template<typename data_t, typename weight_t>
class BellmanFord {
private:
    umap<id_t, id_t> nodes;
    umap<id_t, weight_t> distances;

    id_t start;
public:
    BellmanFord(UnDirectedGraph<data_t, weight_t> const &graph, id_t start);

    BellmanFord(DirectedGraph<data_t, weight_t> const &graph, id_t start);

    ~BellmanFord();

    void displayDistances();

};

template<typename data_t, typename weight_t>
BellmanFord<data_t, weight_t>::BellmanFord(const UnDirectedGraph<data_t, weight_t> &graph, id_t start) {
    this->start = start;
    if (graph.vertexes.find(start) == graph.vertexes.end())
        throw std::out_of_range("Start Vertex Does Not Exist");

    for (auto &it : graph.vertexes) {
        nodes.insert({it.first, id_t()});
        distances.insert({it.first, inf});
    }
    distances[start] = 0;
    int n = graph.vertexes.size();
    for (int i = 0; i < graph.vertexes.size() - 1; i++) {
        for (auto &it : graph.vertexes) {
            for (auto it2 : it.second->edges) {
                auto u = it2->vertexes[0].id == it.first ? it2->vertexes[0].id : it2->vertexes[1].id;
                auto v = it2->vertexes[1].id != it.first ? it2->vertexes[1].id : it2->vertexes[0].id;
                auto w = it2->weight;
                if ((distances[u] + w) < distances[v]) {
                    distances[v] = distances[u] + w;
                    nodes[v] = u;
                }
            }
        }
    }
    for (auto &it : graph.vertexes) {
        for (auto it2 : it.second->edges) {
            auto u = it2->vertexes[0].id == it.first ? it2->vertexes[0].id : it2->vertexes[1].id;
            auto v = it2->vertexes[1].id != it.first ? it2->vertexes[1].id : it2->vertexes[0].id;
            auto w = it2->weight;
            if ((distances[u] + w) < distances[v]) {
                throw std::out_of_range("Graph contains negative weight cycle");
            }
        }
    }
}

template<typename data_t, typename weight_t>
BellmanFord<data_t, weight_t>::BellmanFord(const DirectedGraph<data_t, weight_t> &graph, std::string start) {
    this->start = start;
    if (graph.vertexes.find(start) == graph.vertexes.end())
        throw std::out_of_range("Start Vertex Does Not Exist");

    for (auto &it : graph.vertexes) {
        nodes.insert({it.first, id_t()});
        distances.insert({it.first, inf});
    }
    distances[start] = 0;
    int n = graph.vertexes.size();
    for (int i = 0; i < graph.vertexes.size() - 1; i++) {
        for (auto &it : graph.vertexes) {
            for (auto it2 : it.second->edges) {
                auto u = it2->vertexes[0].id == it.first ? it2->vertexes[0].id : it2->vertexes[1].id;
                auto v = it2->vertexes[1].id != it.first ? it2->vertexes[1].id : it2->vertexes[0].id;
                auto w = it2->weight;
                if ((distances[u] + w) < distances[v]) {
                    distances[v] = distances[u] + w;
                    nodes[v] = u;
                }
            }
        }
    }
    for (auto &it : graph.vertexes) {
        for (auto it2 : it.second->edges) {
            auto u = it2->vertexes[0].id == it.first ? it2->vertexes[0].id : it2->vertexes[1].id;
            auto v = it2->vertexes[1].id != it.first ? it2->vertexes[1].id : it2->vertexes[0].id;
            auto w = it2->weight;
            if ((distances[u] + w) < distances[v]) {
                throw std::out_of_range("Graph contains negative weight cycle");
            }
        }
    }
}

template<typename data_t, typename weight_t>
BellmanFord<data_t, weight_t>::~BellmanFord() {
    nodes.clear();
    distances.clear();
}

template<typename data_t, typename weight_t>
void BellmanFord<data_t, weight_t>::displayDistances() {
    std::cout << "Distances From " << start << "\n";
    for (auto &it : distances)
        std::cout << it.first << ":\t" << it.second << "\n";
}


#endif //GRAPH_PROJECT_PANCONPALTA_BELLMANFORD_H
