#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "Graph.h"

template<typename TV, typename TE>
class Compare {
public:
    bool operator()(Edge<TV, TE> *&a, Edge<TV, TE> *&b) {
        return a->weight > b->weight;
    }
};

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE> {
private:
    std::priority_queue<Edge<TV, TE> *, std::vector<Edge<TV, TE> *>, Compare<TV, TE>> priority_queue;

public:
    UnDirectedGraph();

    ~UnDirectedGraph();

    bool insertVertex(string id, TV vertex) override;

    bool createEdge(string id1, string id2, TE w) override;

    bool deleteVertex(string id) override;

    bool deleteEdge(string id1, string id2) override;

    TE &operator()(string id1, string id2) override;

    float density() override;

    bool isDense(float threshold = 0.5) override;

    /*bool isConnected() override;

    bool isStronglyConnected() override;

    bool empty() override;

    void clear() override;

    void displayVertex(string id) override;
*/
    bool findById(string id) override;

    void display() override;

};

template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::UnDirectedGraph():Graph<TV, TE>() {

}

template<typename TV, typename TE>
UnDirectedGraph<TV, TE>::~UnDirectedGraph() {
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {
    if (!findById(id)) {
        Vertex<TV, TE> *v = new Vertex<TV, TE>{id, vertex, std::list<Edge<TV, TE> *>()};
        this->vertexes.insert(std::make_pair(id, v));
        return true;
    }
    return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
    if (!findById(id1))
        return false;
    auto edges = this->vertexes[id1]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->vertexes[0].id == id2 || (*it)->vertexes[1].id == id2)
            return false;
    }
    Vertex<TV, TE> *v = new Vertex<TV, TE>[2];
    v[0] = *this->vertexes.at(id1);
    v[1] = *this->vertexes.at(id2);
    Edge<TV, TE> *edge = new Edge<TV, TE>(v, w);
    this->vertexes.at(id1)->edges.push_back(edge);
    priority_queue.push(edge);
    this->vertexes.at(id2)->edges.push_back(edge);
    this->totEdges++;
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteVertex(string id) {
    if (!findById(id))
        return false;
    auto &edges = this->vertexes[id]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        auto &other_edges = (*it)->vertexes[0].id != id ? this->vertexes[(*it)->vertexes[0].id]->edges
                                                        : this->vertexes[(*it)->vertexes[1].id]->edges;
        for (auto it2 = other_edges.begin(); it2 != other_edges.end(); ++it2) {
            if ((*it)->vertexes[0].id == id || (*it)->vertexes[1].id == id) {
                (*it2)->killSelf();
                (*it2) = nullptr;
                other_edges.erase(it2);
                break;
            }
        }
    }
    edges.clear();
    this->vertexes.erase(id);
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteEdge(string id1, string id2) {
    if (!findById(id1))
        return false;
    auto &edges = this->vertexes[id1]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->vertexes[0].id == id2 || (*it)->vertexes[1].id == id2) {
            auto &other_edges = (*it)->vertexes[0].id != id1 ? this->vertexes[(*it)->vertexes[0].id]->edges
                                                             : this->vertexes[(*it)->vertexes[1].id]->edges;
            for (auto it2 = other_edges.begin(); it2 != other_edges.end(); ++it2) {
                if ((*it2)->vertexes[0].id == id1 || (*it2)->vertexes[1].id == id1) {
                    (*it2)->killSelf();
                    (*it2) = nullptr;
                    other_edges.erase(it2);
                    this->totEdges--;
                }
                edges.erase(it);
                return true;
            }
        }
    }
    return false;
}


template<typename TV, typename TE>
TE &UnDirectedGraph<TV, TE>::operator()(string id1, string id2) {
    if (!findById(id1))
        throw std::out_of_range("Graph does not contain vertex");
    auto &edges = this->vertexes[id1]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->vertexes[0].id == id2 || (*it)->vertexes[1].id == id2) {
            return (*it)->weight;
        }
    }
    throw std::out_of_range("Graph does not contain edge");
}


template<typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density() {
    return 2 * float(this->totEdges / float((this->vertexes.size() * (this->vertexes.size() - 1))));
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold) {
    return density() > threshold;
}

/*
template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isConnected() {
    return Graph::isConnected();
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isStronglyConnected() {
    return Graph::isStronglyConnected();
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::empty() {
    return Graph::empty();
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::clear() {
    Graph::clear();
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::displayVertex(string id) {
    Graph::displayVertex(id);
}
*/
template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(string id) {
    return this->vertexes.find(id) != this->vertexes.end();
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::display() {
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        std::cout << it->second->data << ": ";
        for (auto it2 = it->second->edges.begin(); it2 != it->second->edges.end(); ++it2) {
            auto val = (*it2)->vertexes[0].data;
            if ((*it2)->vertexes[0].data == it->second->data)
                val = (*it2)->vertexes[1].data;
            std::cout << val << '(' << (*it2)->weight << ')' << ", ";
        }
        std::cout << std::endl;
    }
}

#endif