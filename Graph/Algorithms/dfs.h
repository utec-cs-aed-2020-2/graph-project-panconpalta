#ifndef GRAPH_PROJECT_PANCONPALTA_DFS_H
#define GRAPH_PROJECT_PANCONPALTA_DFS_H

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
class DFS {
private:
    enum graphType {
        unDirected, directed
    };
    graphType type;
    umap<id_t, vertex_t *> v;
    std::vector<std::tuple<id_t, id_t, weight_t>> dfs;

public:
    explicit DFS(UnDirectedGraph<data_t, weight_t> &graph, id_t start);

    explicit DFS(DirectedGraph<data_t, weight_t> &graph, id_t start);

    UnDirectedGraph<data_t, weight_t> unDirectedApply();

    DirectedGraph<data_t, weight_t> directedApply();

    ~DFS();


};

template<typename data_t, typename weight_t>
DFS<data_t, weight_t>::DFS(UnDirectedGraph<data_t, weight_t> &graph, id_t start) {
    if (graph.vertexes.find(start) == graph.vertexes.end())
        throw std::out_of_range("Start Vertex Does Not Exist");
    type = unDirected;
    std::stack<id_t> nodes;
    std::stack<std::pair<id_t, weight_t>> weight_prev;
    std::unordered_set<id_t> visited;

    nodes.push(graph.vertexes[start]->id);
    std::pair<id_t, weight_t> top_weight;
    id_t top, other;
    while (!nodes.empty()) {
        top = nodes.top();
        if (!weight_prev.empty()) {
            top_weight = weight_prev.top();
            weight_prev.pop();
        }
        nodes.pop();

        if (visited.find(top) == visited.end()) {
            v.insert({top, graph.vertexes[top]});
            if (!weight_prev.empty())
                dfs.push_back({top, top_weight.first, top_weight.second});
            visited.insert(top);
        }

        for (auto it = graph.vertexes[top]->edges.begin(); it != graph.vertexes[top]->edges.end(); ++it) {
            other = (*it)->vertexes[0].id != top ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
            if (visited.find(other) == visited.end()) {
                nodes.push(other);
                weight_prev.push(std::make_pair(top, (*it)->weight));
            }
        }
    }
}

template<typename data_t, typename weight_t>
DFS<data_t, weight_t>::DFS(DirectedGraph<data_t, weight_t> &graph, id_t start) {
    if (graph.vertexes.find(start) == graph.vertexes.end())
        throw std::out_of_range("Start Vertex Does Not Exist");
    type = directed;
    std::stack<id_t> nodes;
    std::stack<std::pair<id_t, weight_t>> weight_prev;
    std::unordered_set<id_t> visited;

    nodes.push(graph.vertexes[start]->id);
    std::pair<id_t, weight_t> top_weight;
    id_t top, other;
    while (!nodes.empty()) {
        top = nodes.top();
        nodes.pop();

        if (visited.find(top) == visited.end()) {
            v.insert({top, graph.vertexes[top]});
            if (!weight_prev.empty()) {
                top_weight = weight_prev.top();
                weight_prev.pop();
                dfs.push_back({top_weight.first, top, top_weight.second});
            }
            visited.insert(top);
        }

        for (auto it = graph.vertexes[top]->edges.begin(); it != graph.vertexes[top]->edges.end(); ++it) {
            other = (*it)->vertexes[0].id != top ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
            if (visited.find(other) == visited.end()) {
                nodes.push(other);
                weight_prev.push(std::make_pair(top, (*it)->weight));
            }
        }
    }
}

template<typename data_t, typename weight_t>
DFS<data_t, weight_t>::~DFS() {
    v.clear();
    dfs.clear();
}

template<typename data_t, typename weight_t>
UnDirectedGraph<data_t, weight_t> DFS<data_t, weight_t>::unDirectedApply() {
    if (type != unDirected)
        throw std::invalid_argument("Invalid Graph Type");
    UnDirectedGraph<data_t, weight_t> tree;
    for (auto &it : v)
        tree.insertVertex(it.first, it.second->data);
    for (auto &it : dfs)
        tree.createEdge(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    return tree;
}

template<typename data_t, typename weight_t>
DirectedGraph<data_t, weight_t> DFS<data_t, weight_t>::directedApply() {
    if (type != directed)
        throw std::invalid_argument("Invalid Graph Type");
    DirectedGraph<data_t, weight_t> tree;
    for (auto &it : v)
        tree.insertVertex(it.first, it.second->data);
    for (auto &it : dfs)
        tree.createEdge(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    return tree;
}

#endif //GRAPH_PROJECT_PANCONPALTA_DFS_H
