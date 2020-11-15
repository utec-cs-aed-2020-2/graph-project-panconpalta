#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "Graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE> {
public:
    DirectedGraph();

    ~DirectedGraph();

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

    */bool findById(string id) override;

    void display() override;
};

template<typename TV, typename TE>
DirectedGraph<TV, TE>::DirectedGraph() : Graph<TV, TE>() {

}

template<typename TV, typename TE>
DirectedGraph<TV, TE>::~DirectedGraph() {

}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::insertVertex(string id, TV vertex) {
    if (!findById(id)) {
        Vertex<TV, TE> *v = new Vertex<TV, TE>{id, vertex, std::list<Edge<TV, TE> *>()};
        this->vertexes.insert(std::make_pair(id, v));
        return true;
    }
    return false;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w) {
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
    this->totEdges++;
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteVertex(string id) {
    if (!findById(id))
        return false;
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); ++it) {
        if (it->first != id) {
            for (auto it2 = (it->second)->edges.begin(); it2 != (it->second)->edges.end(); ++it2) {
                if ((*it2)->vertexes[0].id == id || (*it2)->vertexes[1].id == id) {
                    (*it2)->killSelf();
                    (*it2) = nullptr;
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

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteEdge(string id1, string id2) {
    if (!findById(id1))
        return false;
    auto &edges = this->vertexes[id1]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->vertexes[0].id == id2 || (*it)->vertexes[1].id == id2) {
            (*it)->killSelf();
            (*it) = nullptr;
            edges.erase(it);
            this->totEdges--;
            return true;

        }
    }
    return false;
}


template<typename TV, typename TE>
TE &DirectedGraph<TV, TE>::operator()(string id1, string id2) {
    if (!findById(id1))
        throw std::out_of_range("Graph does not contain vertex");
    auto &edges = this->vertexes[id1]->edges;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->vertexes[0].id == id2 || (*it)->vertexes[1].id == id2)
            return (*it)->weight;

    }
    throw std::out_of_range("Graph does not contain edge");
}


template<typename TV, typename TE>
float DirectedGraph<TV, TE>::density() {
    return float(this->totEdges / float((this->vertexes.size() * (this->vertexes.size() - 1))));
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isDense(float threshold) {
    return density() > threshold;
}

template<typename TV, typename TE>
void visit(unordered_map<int,bool>& visited, int id){
      visited[id]=true;
      int id2 = 0;
      for(auto it = this->vertexes[id]->edges.begin(); it!=this->vertexes[id]->edges.end(); it++){
        for(auto it2 = this->vertexes.begin(); it2!= this->vertexes.end(); it2++){
          if(it2->second == (*it)->vertexes[1]){
            id2 = it2->first;
            break;
          }
        }
        if(visited[id2]==false){
          visit(visited,id2);
        }
      }
    }
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isConnected() {
    unordered_map<int, bool> visited;
    for(auto it = this->vertexes.begin(); it!= this->vertexes.end(); it++){
      visited[it->first] = false;
    }
    auto it = this->vertexes.begin();
    visit(visited, it->first);
    for(auto it= visited.begin(); it!= visited.end(); it++){
      if(it->second == false){
        return false;
      }
    }
    return true;
}

/*

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isStronglyConnected() {
    return Graph::isStronglyConnected();
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::empty() {
    return Graph::empty();
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::clear() {
    Graph::clear();
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::displayVertex(string id) {
    Graph::displayVertex(id);
}
*/
template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::findById(string id) {
    return this->vertexes.find(id) != this->vertexes.end();
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::display() {
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
