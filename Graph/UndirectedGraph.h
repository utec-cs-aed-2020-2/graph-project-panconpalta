#ifndef UNDIRECweight_tDGRAPH_H
#define UNDIRECweight_tDGRAPH_H

#include "Graph.h"
/////////////////////////////////////////
#define undiGraph_t UnDirectedGraph<data_t, weight_t>
/////////////////////////////////////////

template<typename data_t, typename weight_t>
class UnDirectedGraph : public Graph<data_t, weight_t> {
private:

public:
    UnDirectedGraph();

    ~UnDirectedGraph();

    weight_t &operator()(id_t id1, id_t id2) override;

    float density() override;

    bool insertVertex(id_t id, data_t vertex) override;

    bool createEdge(id_t id1, id_t id2, weight_t w) override;

    bool deleteVertex(id_t id) override;

    bool deleteEdge(id_t id1, id_t id2) override;

    bool isDense(float threshold = 0.5) override;

    bool isConnected() override;

    bool isStronglyConnected() override;

    bool isBipartite() override;

    bool empty() override;

    bool findById(id_t id) override;

    void clear() override;

    void displayVertex(id_t id) override;

    void display() override;

    data_t operator[](id_t key);

    undiGraph_t execKruskal();
};

template<typename data_t, typename weight_t>
undiGraph_t::UnDirectedGraph():Graph<data_t, weight_t>() {
}

template<typename data_t, typename weight_t>
undiGraph_t::~UnDirectedGraph() {
}

template<typename data_t, typename weight_t>
bool undiGraph_t::insertVertex(id_t id, data_t vertex) {
    if (!findById(id)) {
        vertex_t *v = new vertex_t;
        v->data = vertex;
        v->id = id;
        this->vertexes[id] = v;
        return true;
    }
    return false;
}

template<typename data_t, typename weight_t>
bool undiGraph_t::createEdge(id_t id1, id_t id2, weight_t w) {
    if (!findById(id1) || !findById(id1))
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
    this->vertexes.at(id2)->edges.push_back(edge);
    this->totEdges++;
    return true;
}

template<typename data_t, typename weight_t>
bool undiGraph_t::deleteVertex(id_t id) {
    if (!findById(id))
        return false;
    auto &edges = this->vertexes[id]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        auto &other_edges = (*it)->vertexes[0].id != id ? this->vertexes[(*it)->vertexes[0].id]->edges
                                                        : this->vertexes[(*it)->vertexes[1].id]->edges;
        for (auto it2 = other_edges.begin(); it2 != other_edges.end(); ++it2) {
            if ((*it)->vertexes[0].id == id || (*it)->vertexes[1].id == id) {
                (*it2)->killSelf();
                other_edges.erase(it2);
                break;
            }
        }
    }
    edges.clear();
    this->vertexes.erase(id);
    return true;
}

template<typename data_t, typename weight_t>
bool undiGraph_t::deleteEdge(id_t id1, id_t id2) {
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

template<typename data_t, typename weight_t>
data_t undiGraph_t::operator[](id_t key) {
    if (this->vertexes.find(key) != this->vertexes.end())
        return this->vertexes[key]->data;
    else
        return data_t();
}

template<typename data_t, typename weight_t>
weight_t &undiGraph_t::operator()(id_t id1, id_t id2) {
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


template<typename data_t, typename weight_t>
float undiGraph_t::density() {
    return 2 * float(this->totEdges / float((this->vertexes.size() * (this->vertexes.size() - 1))));
}

template<typename data_t, typename weight_t>
bool undiGraph_t::isDense(float threshold) {
    return density() > threshold;
}

template<typename data_t, typename weight_t>
bool undiGraph_t::isConnected() {
    umap<id_t, bool> visited;
    for (auto it: this->vertexes) {
        visit(visited, this->vertexes, it.first);
        if (visited.size() == this->vertexes.size()) {
            return true;
        }
        visited.clear();
    }
    return false;
}

template<typename data_t, typename weight_t>
bool undiGraph_t::isStronglyConnected() {
    return isConnected();
}

template<typename data_t, typename weight_t>
bool undiGraph_t::isBipartite() {
    umap<id_t, bool> color;
    color[this->vertexes.begin()->first] = true;
    queue<id_t> q;
    q.push(this->vertexes.begin()->first);

    while (!q.empty()) {
        id_t current = q.front();
        q.pop();
        for (auto transition: this->vertexes[current]->edges) {
            if (transition->vertexes[1].id == current) {
                return false;
            }
            if (color.find(transition->vertexes[1].id) == color.end()) {
                color[transition->vertexes[1].id] = !color[current];
                q.push(transition->vertexes[1].id);
            } else if (color.find(transition->vertexes[1].id) != color.end() &&
                       color[transition->vertexes[1].id] == color[current]) {
                return false;
            }

        }
    }
    return true;
}

template<typename data_t, typename weight_t>
bool undiGraph_t::empty() {
    auto it = this->vertexes.begin();
    return (it == this->vertexes.end());
}

template<typename data_t, typename weight_t>
void undiGraph_t::clear() {
    for (auto &it_vertex: this->vertexes) {
        for (auto &it_edge: it_vertex.second->edges) {
            if (it_edge != nullptr) {
                it_edge->killSelf();
                it_edge = nullptr;
            }
        }
        //it_vertex.second->edges.clear();
    }
    for(auto &it_vertex: this->vertexes)
        if(it_vertex.second != nullptr){
            it_vertex.second->killSelf();
            it_vertex.second = nullptr;
        }
    this->vertexes.clear();
}

template<typename data_t, typename weight_t>
void undiGraph_t::displayVertex(id_t id) {
    auto it = this->vertexes.find(id);
    if (it == this->vertexes.end())
        throw std::out_of_range("Graph does not contain vertex");
    std::cout << it->second->id << ": ";
    for (auto it2 = it->second->edges.begin(); it2 != it->second->edges.end(); ++it2) {
        auto val_id = (*it2)->vertexes[0].id != id ? (*it2)->vertexes[0].id : (*it2)->vertexes[1].id;
        std::cout << val_id << '(' << (*it2)->weight << ')' << ", ";
    }
    std::cout << std::endl;
}

template<typename data_t, typename weight_t>
bool undiGraph_t::findById(id_t id) {
    return this->vertexes.find(id) != this->vertexes.end();
}

template<typename data_t, typename weight_t>
void undiGraph_t::display() {
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        std::cout << it->second->id << ": ";
        for (auto it2 = it->second->edges.begin(); it2 != it->second->edges.end(); ++it2) {
            auto val = (*it2)->vertexes[0].id;
            if ((*it2)->vertexes[0].id == it->second->id)
                val = (*it2)->vertexes[1].id;
            std::cout << val << '(' << (*it2)->weight << ')' << ", ";
        }
        std::cout << std::endl;
    }
}


template<typename data_t, typename weight_t>
undiGraph_t undiGraph_t::execKruskal() {
    undiGraph_t Kruskal;
    std::vector<id_t> vs(this->vertexes.size());
    Kqueue_t EdgesToCheck;
    //Preparing for the algorithm
    for (auto &it: this->vertexes) {
        //making a copy of the graph without edges
        Kruskal.insertVertex(it.first, it.second->data);
        //adding the vertexes to the disjoin set
        vs.push_back(it.first);
        //adding the edges to the priority queue
        for (auto &edgePtr: it.second->edges) {
            //the edges are duplicated cuz the graph is undirected
            EdgesToCheck.push(std::make_pair(edgePtr->weight, edgePtr));
        }
    }
    dset_t VertexSets(vs);
    //Preparation done
    //Executing the algorithm
    edge_t *currentEdge = nullptr;
    while (!EdgesToCheck.empty()) {
        currentEdge = EdgesToCheck.top().second;
        EdgesToCheck.pop();
        //checking if the nodes of the edge are already conected
        if (VertexSets.Find(getIdOf(currentEdge->vertexes[0])) == VertexSets.Find(getIdOf(currentEdge->vertexes[1])))
            continue;
        //else
        VertexSets.Union(VertexSets.Find(getIdOf(currentEdge->vertexes[0])),
                         VertexSets.Find(getIdOf(currentEdge->vertexes[1])));
        Kruskal.createEdge(getIdOf(currentEdge->vertexes[0]), getIdOf(currentEdge->vertexes[1]), currentEdge->weight);
    }

    return Kruskal;
}

#endif
