#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <queue>
#include <iostream>
#include "dsarray.h"

template<typename data_t, typename weight_t>
struct Edge;
template<typename data_t, typename weight_t>
struct Vertex;

template<typename data_t, typename weight_t>
class Graph;

/////////////define types////////////////////////
#define umap std::unordered_map
#define map std::map
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
        if (visited[(*it)->vertexes[1].id] == false)
            visit(visited, vertexes, (*it)->vertexes[1].id);
    }
}

template<typename data_t, typename weight_t>
id_t getIdOf(vertex_t &v) {
    return v.id;
}

