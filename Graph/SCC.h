#ifndef GRAPH_PROJECT_PANCONPALTA_SCC_H
#define GRAPH_PROJECT_PANCONPALTA_SCC_H

#include "Graph.h"


template<typename data_t, typename weight_t>
class DirectedGraph;

template<typename data_t, typename weight_t>
class SCC {
private:
    umap<id_t, vertex_t *> vertexes;

    std::vector<std::tuple<id_t, id_t, weight_t>> scc;

    int time = 0;

    std::vector<std::vector<id_t>> components;

    std::unordered_map<id_t, int> index;

    std::unordered_map<id_t, int> low;

    std::unordered_set<id_t> stackMember;

    std::stack<id_t> stack;


public:
    explicit SCC(DirectedGraph<data_t, weight_t> &graph);

    ~SCC();

    DirectedGraph<data_t, weight_t> apply();

    void displayComponents();

private:
    void strongConnect(id_t node, DirectedGraph<data_t, weight_t> &graph);

    void buildEdges(uset<id_t> &comp, DirectedGraph<data_t, weight_t> &graph);
};

template<typename data_t, typename weight_t>
SCC<data_t, weight_t>::SCC(DirectedGraph<data_t, weight_t> &graph) {
    for (auto &it : graph.vertexes) {
        index.insert({it.first, -1});
        low.insert({it.first, -1});
    }
    for (auto &it : graph.vertexes)
        if (index[it.first] == -1)
            strongConnect(it.first, graph);

}

template<typename data_t, typename weight_t>
SCC<data_t, weight_t>::~SCC() {
    vertexes.clear();
    scc.clear();
    for (auto &i : components)
        i.clear();
    components.clear();
}

template<typename data_t, typename weight_t>
void SCC<data_t, weight_t>::strongConnect(id_t node, DirectedGraph<data_t, weight_t> &graph) {
    index[node] = time;
    low[node] = time;
    time++;
    stack.push(node);
    stackMember.insert(node);
    for (auto it = graph.vertexes[node]->edges.begin(); it != graph.vertexes[node]->edges.end(); ++it) {
        auto other = (*it)->vertexes[0].id != node ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
        if (index[other] == -1) {
            strongConnect(other, graph);
            low[node] = std::min(low[node], low[other]);
        } else if (stackMember.find(other) != stackMember.end())
            low[node] = std::min(low[node], index[other]);
    }
    uset<id_t> comp;
    std::vector<id_t> c;
    if (low[node] == index[node]) {
        while (stack.top() != node) {
            c.push_back(stack.top());
            comp.insert(stack.top());
            stackMember.erase(stack.top());
            vertexes.insert({stack.top(), graph.vertexes[stack.top()]});
            stack.pop();
        }
        c.push_back(stack.top());
        comp.insert(stack.top());
        vertexes.insert({stack.top(), graph.vertexes[stack.top()]});
        stackMember.erase(stack.top());
        stack.pop();
        components.push_back(c);
        buildEdges(comp, graph);
    }
}

template<typename data_t, typename weight_t>
void SCC<data_t, weight_t>::buildEdges(uset<id_t> &comp, DirectedGraph<data_t, weight_t> &graph) {
    for (auto &node :comp) {
        for (auto it = graph.vertexes[node]->edges.begin(); it != graph.vertexes[node]->edges.end(); ++it) {
            auto other = (*it)->vertexes[0].id != node ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
            if (comp.find(other) != comp.end())
                scc.push_back({node, other, (*it)->weight});
        }
    }
}

template<typename data_t, typename weight_t>
DirectedGraph<data_t, weight_t> SCC<data_t, weight_t>::apply() {
    DirectedGraph<data_t, weight_t> tree;
    for (auto &it : vertexes)
        tree.insertVertex(it.first, it.second->data);
    for (auto &it : scc)
        tree.createEdge(std::get<0>(it), std::get<1>(it), std::get<2>(it));
    return tree;
}

template<typename data_t, typename weight_t>
void SCC<data_t, weight_t>::displayComponents() {
    for (int i = 0; i < components.size(); ++i) {
        std::cout << "Component " << i + 1 << ":\t";
        for (int j = 0; j < components[i].size(); ++j) {
            std::cout << components[i][j];
            if (j != components[i].size() - 1)
                std::cout << " - ";
        }
        std::cout << "\n";
    }
}

#endif //GRAPH_PROJECT_PANCONPALTA_SCC_H
