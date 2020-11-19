#include "DirectedGraph.h"

template<typename data_t, typename weight_t>
diGraph_t::DirectedGraph() : Graph<data_t, weight_t>() {
}

template<typename data_t, typename weight_t>
diGraph_t::~DirectedGraph() {
}

template<typename data_t, typename weight_t>
bool diGraph_t::insertVertex(id_t id, data_t vertex) {
    if (!findById(id)) {
        vertex_t *v = new vertex_t{id, vertex, std::list<edge_t *>()};
        this->vertexes.insert(std::make_pair(id, v));
        return true;
    }
    return false;
}

template<typename data_t, typename weight_t>
bool diGraph_t::createEdge(id_t id1, id_t id2, weight_t w) {
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
bool diGraph_t::deleteVertex(id_t id) {
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
bool diGraph_t::deleteEdge(id_t id1, id_t id2) {
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
weight_t &diGraph_t::operator()(id_t id1, id_t id2) {
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

template<typename data_t, typename weight_t>
bool diGraph_t::isConnected() {
  umap<id_t, bool> visited;
  for(auto it: this->vertexes){
    visit(visited,this->vertexes, it.first);
    if(visited.size()==this->vertexes.size()){
      return true;
    }
    visited.clear();
  }
  return false;
}

template<typename data_t, typename weight_t>
bool diGraph_t::isStronglyConnected() {
  umap<id_t, bool> visited;
  for(auto it: this->vertexes){
    visit(visited,this->vertexes, it.first);
    if(visited.size()!=this->vertexes.size()){
      return false;
    }
    visited.clear();
  }
  return true;
}

template<typename data_t, typename weight_t>
bool diGraph_t::isBipartite(){
  umap<id_t, bool> color;
  color[this->vertexes.begin()->first] = true;
  queue <id_t> q; 
  q.push(this->vertexes.begin()->first); 

  while (!q.empty()){
    id_t current = q.front(); 
    q.pop(); 
    for (auto transition: this->vertexes[current]->edges){
      if(transition->vertexes[1].id==current){
        return false;
      }
      if(color.find(transition->vertexes[1].id)==color.end()){
        color[transition->vertexes[1].id] = !color[current];
        q.push(transition->vertexes[1].id);
      }
      else if(color.find(transition->vertexes[1].id)!=color.end() && color[transition->vertexes[1].id] == color[current]){
        return false;
      }
      
    }
  }
    return true;
}

template<typename data_t, typename weight_t>
bool diGraph_t::empty() {
    auto it = this->vertexes.begin();
    return (it==this->vertexes.end());
}

template<typename data_t, typename weight_t>
void diGraph_t::clear() {
    for(auto it_vertex: this->vertexes){
      for(auto it_edge: (*it_vertex.second).edges){
        (*it_edge).killSelf();
      }
      (*it_vertex.second).killSelf();
    }
    this->vertexes.clear();
}

template<typename data_t, typename weight_t>
void diGraph_t::displayVertex(id_t id) {
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
bool diGraph_t::findById(id_t id) {
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
