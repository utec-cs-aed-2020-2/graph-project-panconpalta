#ifndef GRAPH_PROJECT_PANCONPALTA_FLOYDWARSHALL_H
#define GRAPH_PROJECT_PANCONPALTA_FLOYDWARSHALL_H

#include "Graph.h"

#define inf 999

template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class DirectedGraph;

template<typename data_t, typename weight_t>
class FloydWarshall {
private:
    weight_t **distance;
    id_t **nodes;
    umap<id_t, int> idt_pos;
    umap<int, id_t> pos_idt;

public:
    explicit FloydWarshall(UnDirectedGraph<data_t, weight_t> const &graph);

    explicit FloydWarshall(DirectedGraph<data_t, weight_t> const &graph);

    ~FloydWarshall();

    void displayDistances();

    void displayPaths();

    void showPath(id_t a, id_t b);

};

template<typename data_t, typename weight_t>
FloydWarshall<data_t, weight_t>::FloydWarshall(const UnDirectedGraph<data_t, weight_t> &graph) {
    distance = new weight_t *[graph.vertexes.size()];
    nodes = new id_t *[graph.vertexes.size()];
    int i = 0;
    for (const auto &it : graph.vertexes) {
        idt_pos.insert(std::make_pair(it.first, i));
        pos_idt.insert(std::make_pair(i, it.first));
        distance[i] = new weight_t[graph.vertexes.size()];
        nodes[i] = new id_t[graph.vertexes.size()];
        i++;
    }
    for (int i = 0; i < graph.vertexes.size(); ++i) {
        for (int j = 0; j < graph.vertexes.size(); ++j) {
            if (i == j) {
                distance[i][j] = weight_t();
                nodes[i][j] = pos_idt[i];
            } else {
                distance[i][j] = inf;
                nodes[i][j] = id_t();
            }
        }
    }

    for (const auto &it: graph.vertexes) {
        for (const auto &it2 : it.second->edges) {
            id_t j = it2->vertexes[0].id != it.first ? it2->vertexes[0].id : it2->vertexes[1].id;
            distance[idt_pos[it.first]][idt_pos[j]] = it2->weight;
            nodes[idt_pos[it.first]][idt_pos[j]] = j;
        }
    }

    for (int k = 0; k < graph.vertexes.size(); ++k) {
        for (i = 0; i < graph.vertexes.size(); ++i) {
            for (int j = 0; j < graph.vertexes.size(); ++j) {
                if (distance[i][j] > (distance[i][k] + distance[k][j])) {
                    distance[i][j] = (distance[i][k] + distance[k][j]);
                    nodes[i][j] = nodes[i][k];
                }
            }
        }
    }
}


template<typename data_t, typename weight_t>
FloydWarshall<data_t, weight_t>::FloydWarshall(const DirectedGraph<data_t, weight_t> &graph) {
    distance = new weight_t *[graph.vertexes.size()];
    nodes = new id_t *[graph.vertexes.size()];
    int i = 0;
    for (const auto &it : graph.vertexes) {
        idt_pos.insert(std::make_pair(it.first, i));
        pos_idt.insert(std::make_pair(i, it.first));
        distance[i] = new weight_t[graph.vertexes.size()];
        nodes[i] = new id_t[graph.vertexes.size()];
        i++;
    }
    for (int i = 0; i < graph.vertexes.size(); ++i) {
        for (int j = 0; j < graph.vertexes.size(); ++j) {
            if (i == j) {
                distance[i][j] = weight_t();
                nodes[i][j] = pos_idt[j];
            } else {
                distance[i][j] = inf;
                nodes[i][j] = id_t();
            }
        }
    }

    for (const auto &it: graph.vertexes) {
        for (const auto &it2 : it.second->edges) {
            id_t j = it2->vertexes[0].id != it.first ? it2->vertexes[0].id : it2->vertexes[1].id;
            distance[idt_pos[it.first]][idt_pos[j]] = it2->weight;
            nodes[idt_pos[it.first]][idt_pos[j]] = j;
        }
    }

    for (int k = 0; k < graph.vertexes.size(); ++k) {
        for (i = 0; i < graph.vertexes.size(); ++i) {
            for (int j = 0; j < graph.vertexes.size(); ++j) {
                if (distance[i][j] > (distance[i][k] + distance[k][j])) {
                    distance[i][j] = (distance[i][k] + distance[k][j]);
                    nodes[i][j] = nodes[i][k];
                }
            }
        }
    }
}


template<typename data_t, typename weight_t>
FloydWarshall<data_t, weight_t>::~FloydWarshall() {
    for (int i = 0; i < idt_pos.size(); ++i) {
        delete[] distance[i];
        delete[] nodes[i];
    }
    delete[] distance;
    delete[] nodes;

}

template<typename data_t, typename weight_t>
void FloydWarshall<data_t, weight_t>::displayDistances() {
    std::cout << "\n \t";
    for (int k = 0; k < pos_idt.size(); ++k)
        std::cout << pos_idt[k] << "\t";
    std::cout << "\n";
    for (int i = 0; i < pos_idt.size(); ++i) {
        std::cout << pos_idt[i] << ":\t";
        for (int j = 0; j < pos_idt.size(); ++j) {
            if (distance[i][j] == inf)
                std::cout << "-";
            else
                std::cout << distance[i][j];
            std::cout << "\t";
        }
        std::cout << "\n";
    }
}

template<typename data_t, typename weight_t>
void FloydWarshall<data_t, weight_t>::displayPaths() {
    std::cout << "\n \t";
    for (int k = 0; k < pos_idt.size(); ++k)
        std::cout << pos_idt[k] << "\t";
    std::cout << "\n";
    for (int i = 0; i < pos_idt.size(); ++i) {
        std::cout << pos_idt[i] << ":\t";
        for (int j = 0; j < pos_idt.size(); ++j) {
            if (nodes[i][j].empty())
                std::cout << "-";
            else
                std::cout << nodes[i][j];
            std::cout << "\t";
        }
        std::cout << "\n";
    }
}

template<typename data_t, typename weight_t>
void FloydWarshall<data_t, weight_t>::showPath(std::string a, std::string b) {
    if (nodes[idt_pos[a]][idt_pos[b]].empty())
        std::cout << "Impossible to reach " << b << " from " << a << "\n";
    std::vector<id_t> path;
    path.push_back(a);
    std::cout << "Path From " << a << " to " << b << "\n";

    while (a != b) {
        a = nodes[idt_pos[a]][idt_pos[b]];
        path.push_back(a);
    }
    for (int i = 0; i < path.size() - 1; ++i) {
        std::cout << "[" << path[i] << "] -- (" << distance[idt_pos[path[i]]][idt_pos[path[i + 1]]] << ") --> ";
    }
    std::cout << "[" << path[path.size() - 1] << "]\n";
}

#endif