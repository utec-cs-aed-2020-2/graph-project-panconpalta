#ifndef GRAPH_PROJECT_PANCONPALTA_DIJKSTRA_H
#define GRAPH_PROJECT_PANCONPALTA_DIJKSTRA_H

#ifdef NOCLION
#include "../Graph.h"
#else
#include "Graph.h"
#endif

template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class DirectedGraph;


template<typename data_t, typename weight_t>
class Dijkstra {
private:
    umap<id_t, id_t> nodes;
    umap<id_t, weight_t> distances;

    id_t start;
public:
    Dijkstra(UnDirectedGraph<data_t, weight_t> &graph, id_t start);

    Dijkstra(DirectedGraph<data_t, weight_t> &graph, id_t start);

    ~Dijkstra();

    void displayDistances();

    void showPath(id_t a);

private:
    id_t minDistance(uset<id_t> &q);
};

template<typename data_t, typename weight_t>
Dijkstra<data_t, weight_t>::Dijkstra(UnDirectedGraph<data_t, weight_t> &graph, id_t start) {
    if (graph.vertexes.find(start) == graph.vertexes.end()) {
        throw std::out_of_range("Start Vertex Does Not Exist");
    }
    this->start = start;
    uset<id_t> q;
    for (auto &it : graph.vertexes) {
        nodes.insert({it.first, id_t()});
        distances.insert({it.first, inf});
        q.insert(it.first);
    }
    distances[start] = 0;
    while (!q.empty()) {
        auto node = minDistance(q);
        q.erase(node);
        for (auto it = graph.vertexes[node]->edges.begin(); it != graph.vertexes[node]->edges.end(); ++it) {
            auto other = (*it)->vertexes[0].id != node ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
            auto alt = distances[node] + (*it)->weight;
            if (alt < distances[other]) {
                distances[other] = alt;
                nodes[other] = node;
            }
        }
    }
}

template<typename data_t, typename weight_t>
Dijkstra<data_t, weight_t>::Dijkstra(DirectedGraph<data_t, weight_t> &graph, id_t start) {
    if (graph.vertexes.find(start) == graph.vertexes.end()) {
        throw std::out_of_range("Start Vertex Does Not Exist");
    }
    this->start = start;
    uset<id_t> q;
    for (auto &it : graph.vertexes) {
        nodes.insert({it.first, id_t()});
        distances.insert({it.first, inf});
        q.insert(it.first);
    }
    distances[start] = 0;
    while (!q.empty()) {
        auto node = minDistance(q);
        q.erase(node);
        for (auto it = graph.vertexes[node]->edges.begin(); it != graph.vertexes[node]->edges.end(); ++it) {
            auto other = (*it)->vertexes[0].id != node ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
            auto alt = distances[node] + (*it)->weight;
            if (alt < distances[other]) {
                distances[other] = alt;
                nodes[other] = node;
            }
        }
    }
}

template<typename data_t, typename weight_t>
Dijkstra<data_t, weight_t>::~Dijkstra() {
    nodes.clear();
    distances.clear();
}

template<typename data_t, typename weight_t>
void Dijkstra<data_t, weight_t>::displayDistances() {
    std::cout << "Distances From " << start << "\n";
    for (auto &it : distances)
        std::cout << it.first << ":\t" << it.second << "\n";
}

template<typename data_t, typename weight_t>
void Dijkstra<data_t, weight_t>::showPath(id_t a) {
    if (distances.find(a) == distances.end())
        throw std::out_of_range("Vertex Does Not Exist");
    if (distances[a] == inf) {
        std::cout << "Impossible to reach " << a << " from " << start << "\n";
        return;
    }
    std::vector<id_t> path;
    path.push_back(a);
    std::cout << "Path From " << start << " to " << a << "\n";
    auto s = a;
    while (s != start) {
        path.push_back(nodes[s]);
        s = nodes[s];
    }
    for (int i = path.size() - 1; i >= 1; i--)
        std::cout << "[" << path[i] << "] -- (" << distances[path[i - 1]] - distances[path[i]] << ") --> ";
    std::cout << "[" << path[0] << "]\n";
}

template<typename data_t, typename weight_t>
id_t Dijkstra<data_t, weight_t>::minDistance(uset<id_t> &q) {
    weight_t min = inf;
    id_t node;
    for (auto &it : q) {
        if (distances[it] < min) {
            min = distances[it];
            node = it;
        }
    }
    return node;
}


#endif //GRAPH_PROJECT_PANCONPALTA_DIJKSTRA_H
