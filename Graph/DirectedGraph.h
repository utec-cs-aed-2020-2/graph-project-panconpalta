#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "Graph.h"
/////////////////////////////////////////
#define diGraph_t DirectedGraph<data_t, weight_t>
/////////////////////////////////////////

template<typename data_t, typename weight_t>
class DirectedGraph : public graph_t {
public:
    DirectedGraph();
    ~DirectedGraph();
    bool insertVertex(string id, data_t vertex) override;
    bool createEdge(string id1, string id2, weight_t w) override;
    bool deleteVertex(string id) override;
    bool deleteEdge(string id1, string id2) override;
    weight_t &operator()(string id1, string id2) override;
    float density() override;
    bool isDense(float threshold = 0.5) override;
    /*bool isConnected() override;
    bool isStronglyConnected() override;
    bool empty() override;
    void clear() override;
*/
    void displayVertex(string id) override;
    bool findById(string id) override;
    void display() override;
};

template<typename data_t, typename weight_t>
diGraph_t::DirectedGraph() : Graph<data_t, weight_t>() {

}

template<typename data_t, typename weight_t>
diGraph_t::~DirectedGraph() {

}

template<typename data_t, typename weight_t>
bool diGraph_t::insertVertex(string id, data_t vertex) {
    if (!findById(id)) {
        vertex_t *v = new vertex_t{id, vertex, std::list<edge_t *>()};
        this->vertexes.insert(std::make_pair(id, v));
        return true;
    }
    return false;
}

template<typename data_t, typename weight_t>
bool diGraph_t::createEdge(string id1, string id2, weight_t w) {
    if (!findById(id1))
        return false;
    auto edges = this->vertexes[id1]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->vertexes[0].id == id2 || (*it)->vertexes[1].id == id2)
            return false;
    }
    vertex_t *v = new vertex_t[2];
    v[0] = *this->vertexes.at(id1);
    v[1] = *this->vertexes.at(id2);
    edge_t *edge = new edge_t(v, w);
    this->vertexes.at(id1)->edges.push_back(edge);
    this->totEdges++;
    return true;
}

template<typename data_t, typename weight_t>
bool diGraph_t::deleteVertex(string id) {
    if (!findById(id))
        return false;
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        if (it->first != id) {
            for (auto it2 = (it->second)->edges.begin(); it2 != (it->second)->edges.end(); ++it2) {
                if ((*it2)->vertexes[0].id == id || (*it2)->vertexes[1].id == id) {
                    (*it2)->weight = INT_FAST8_MIN;
                    (*it2)->killSelf();
                    (it->second)->edges.erase(it2);
                    this->totEdges--;
                    break;
                }
            }
        }
    }
    this->vertexes[id]->edges.clear();
    this->vertexes.erase(id);
    return true;
}

template<typename data_t, typename weight_t>
bool diGraph_t::deleteEdge(string id1, string id2) {
    if (!findById(id1))
        return false;
    auto &edges = this->vertexes[id1]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->vertexes[0].id == id2 || (*it)->vertexes[1].id == id2) {
            (*it)->weight = INT_FAST8_MIN;
            (*it)->killSelf();
            edges.erase(it);
            this->totEdges--;
            return true;

        }
    }
    return false;
}


template<typename data_t, typename weight_t>
weight_t &diGraph_t::operator()(string id1, string id2) {
    if (!findById(id1))
        throw std::out_of_range("Graph does not contain vertex");
    auto &edges = this->vertexes[id1]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->vertexes[0].id == id2 || (*it)->vertexes[1].id == id2)
            return (*it)->weight;

    }
    throw std::out_of_range("Graph does not contain edge");
}


template<typename data_t, typename weight_t>
float diGraph_t::density() {
    return float(this->totEdges / float((this->vertexes.size() * (this->vertexes.size() - 1))));
}

template<typename data_t, typename weight_t>
bool diGraph_t::isDense(float threshold) {
    return density() > threshold;
}

/*
template<typename data_t, typename weight_t>
bool diGraph_t::isConnected() {
    return Graph::isConnected();
}

template<typename data_t, typename weight_t>
bool diGraph_t::isStronglyConnected() {
    return Graph::isStronglyConnected();
}

template<typename data_t, typename weight_t>
bool diGraph_t::empty() {
    return Graph::empty();
}

template<typename data_t, typename weight_t>
void diGraph_t::clear() {
    Graph::clear();
}
*/
template<typename data_t, typename weight_t>
void diGraph_t::displayVertex(string id) {
    auto it = this->vertexes.find(id);
    if (it == this->vertexes.end())
        throw std::out_of_range("Graph does not contain vertex");
    std::cout << it->second->data << ": ";
    for (auto it2 = it->second->edges.begin(); it2 != it->second->edges.end(); ++it2) {
        auto val = (*it2)->vertexes[0].id != id ? (*it2)->vertexes[0].id : (*it2)->vertexes[1].id;
        std::cout << val << '(' << (*it2)->weight << ')' << ", ";
    }
    std::cout << std::endl;
}

template<typename data_t, typename weight_t>
bool diGraph_t::findById(string id) {
    return this->vertexes.find(id) != this->vertexes.end();
}

template<typename data_t, typename weight_t>
void diGraph_t::display() {
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
