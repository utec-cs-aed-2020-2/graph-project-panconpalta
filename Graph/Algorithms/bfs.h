#ifndef GRAPH_PROJECT_PANCONPALTA_BFS_H
#define GRAPH_PROJECT_PANCONPALTA_BFS_H

#include "Graph.h"

template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class DirectedGraph;


template<typename data_t, typename weight_t>
class BFS {
private:
    enum graphType {
        unDirected, directed
    };
    graphType type;
    umap<id_t, vertex_t *> v;
    std::vector<std::tuple<id_t, id_t, weight_t>> bfs;

public:
    explicit BFS(UnDirectedGraph<data_t, weight_t> &graph, id_t start);

    explicit BFS(DirectedGraph<data_t, weight_t> &graph, id_t start);

    UnDirectedGraph<data_t, weight_t> unDirectedApply();

    DirectedGraph<data_t, weight_t> directedApply();

    ~BFS();


};

template<typename data_t, typename weight_t>
BFS<data_t, weight_t>::BFS(UnDirectedGraph<data_t, weight_t> &graph, id_t start) {
    if (graph.vertexes.find(start) == graph.vertexes.end())
        throw std::out_of_range("Start Vertex Does Not Exist");
    type = unDirected;
    std::queue<id_t> nodes;
    std::queue<std::pair<id_t, weight_t>> weight_prev;
    std::unordered_set<id_t> visited;

    nodes.push(graph.vertexes[start]->id);
    std::pair<id_t, weight_t> front_weight;
    id_t front, other;
    while (!nodes.empty()) {
        front = nodes.front();
        v.insert({front, graph.vertexes[front]});
        if (!weight_prev.empty()) {
            front_weight = weight_prev.front();
            weight_prev.pop();
            bfs.push_back({front, front_weight.first, front_weight.second});
        }
        nodes.pop();

        for (auto it = graph.vertexes[front]->edges.begin(); it != graph.vertexes[front]->edges.end(); ++it) {
            other = (*it)->vertexes[0].id != front ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
            if (visited.find(other) == visited.end()) {
                visited.insert(other);
                nodes.push(other);
                weight_prev.push(std::make_pair(front, (*it)->weight));
            }
        }
    }
}

template<typename data_t, typename weight_t>
BFS<data_t, weight_t>::BFS(DirectedGraph<data_t, weight_t> &graph, id_t start) {
    if (graph.vertexes.find(start) == graph.vertexes.end())
        throw std::out_of_range("Start Vertex Does Not Exist");
    type = directed;
    std::queue<id_t> nodes;
    std::queue<std::pair<id_t, weight_t>> weight_prev;
    std::unordered_set<id_t> visited;

    nodes.push(graph.vertexes[start]->id);
    std::pair<id_t, weight_t> front_weight;
    id_t front, other;
    while (!nodes.empty()) {
        front = nodes.front();
        v.insert({front, graph.vertexes[front]});
        if (!weight_prev.empty()) {
            front_weight = weight_prev.front();
            weight_prev.pop();
            if(front != start)
                bfs.push_back({front_weight.first, front, front_weight.second});
        }
        nodes.pop();

        for (auto it = graph.vertexes[front]->edges.begin(); it != graph.vertexes[front]->edges.end(); ++it) {
            other = (*it)->vertexes[0].id != front ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
            if (visited.find(other) == visited.end()) {
                visited.insert(other);
                nodes.push(other);
                weight_prev.push(std::make_pair(front, (*it)->weight));
            }
        }
    }
}

template<typename data_t, typename weight_t>
BFS<data_t, weight_t>::~BFS() {
    v.clear();
    bfs.clear();
}

template<typename data_t, typename weight_t>
UnDirectedGraph<data_t, weight_t> BFS<data_t, weight_t>::unDirectedApply() {
    if (type != unDirected)
        throw std::invalid_argument("Invalid Graph Type");
    UnDirectedGraph<data_t, weight_t> tree;
    for (auto &it : v)
        tree.insertVertex(it.first, it.second->data);
    for (auto &it : bfs)
        tree.createEdge(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    return tree;
}

template<typename data_t, typename weight_t>
DirectedGraph<data_t, weight_t> BFS<data_t, weight_t>::directedApply() {
    if (type != directed)
        throw std::invalid_argument("Invalid Graph Type");
    DirectedGraph<data_t, weight_t> tree;
    for (auto &it : v)
        tree.insertVertex(it.first, it.second->data);
    for (auto &it : bfs)
        tree.createEdge(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    return tree;
}

#endif //GRAPH_PROJECT_PANCONPALTA_BFS_H
