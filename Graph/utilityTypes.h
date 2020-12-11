#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include "Algorithms/dsarray.h"

template<typename data_t, typename weight_t>
struct Edge;
template<typename data_t, typename weight_t>
struct Vertex;

template<typename data_t, typename weight_t>
class Graph;

/////////////define types////////////////////////
#define umap std::unordered_map
#define uset std::unordered_set
#define id_t std::string
#define vertex_t Vertex<data_t, weight_t>
#define edge_t Edge<data_t, weight_t>
#define graph_t Graph<data_t, weight_t>
#define dset_t DisjoinSetArray<id_t>
#define Kpair_t std::pair<weight_t, edge_t*>
#define Ppair_t std::pair<weight_t, edge_t*>
#define Kqueue_t std::priority_queue<Kpair_t, std::vector<Kpair_t>, std::greater<Kpair_t>>
#define Pqueue_t std::priority_queue<Ppair_t, std::vector<Ppair_t>, std::greater<Ppair_t>>
#define stack_t std::stack<vertex_t*>
#define queue_t std::queue<vertex_t*>
#define inf 999

/////////////structures//////////////////////////
template<typename data_t, typename weight_t>
struct Edge {
    vertex_t *vertexes;
    weight_t weight;

    void killSelf() {
        delete this;
    }

    Edge(vertex_t *v, weight_t w) {
        vertexes = v;
        weight = w;
    }
};

template<typename data_t, typename weight_t>
struct Vertex {
    id_t id;
    data_t data;
    std::list<edge_t *> edges;

    Vertex() {}

    bool operator==(vertex_t other) { return this->id == other.id; }

    bool operator==(vertex_t *other) { return this->id == other->id; }

    void killSelf() {
        delete this;
    }
};

struct City {
    int id;
    string name;
    double latitude;
    double longitude;
};

struct Airport {
    int id;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;

    Airport() {}

    Airport(int i, string n, string ci, string co, double lat, double lon) :
            id(i),
            name(n),
            city(ci),
            country(co),
            latitude(lat),
            longitude(lon) {}
};

////////////////functions////////////////////////
template<typename data_t, typename weight_t>
void visit(umap<id_t, bool> &visited, umap<id_t, vertex_t *> &vertexes, id_t id) {
    visited[id] = true;
    for (auto it = vertexes[id]->edges.begin(); it != vertexes[id]->edges.end(); it++) {
        auto other = (*it)->vertexes[0].id != id ? (*it)->vertexes[0].id : (*it)->vertexes[1].id;
        if (visited.find(other) == visited.end())
            visit(visited, vertexes, other);
    }
}

template<typename data_t, typename weight_t>
void traverse(uset<id_t> &visited, umap<id_t, vertex_t *> &vertexes, id_t id) {
    //visited[id] = true;
    visited.insert(id);
    for (auto &it : vertexes) {
        for (auto it2 = vertexes[it.first]->edges.begin(); it2 != vertexes[it.first]->edges.end(); it2++) {
            auto other = (*it2)->vertexes[0].id != it.first ? (*it2)->vertexes[0].id : (*it2)->vertexes[1].id;
            if (other == id) {
                if (visited.find(it.first) == visited.end())
                    traverse(visited, vertexes, it.first);
            }
        }
    }
}

template<typename data_t, typename weight_t>
id_t getIdOf(vertex_t &v) {
    return v.id;
}

template<typename data_t, typename weight_t>
id_t getIdOf(vertex_t *&v) {
    return v->id;
}
