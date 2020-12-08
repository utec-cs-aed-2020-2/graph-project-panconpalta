#ifndef GRAPH_PROJECT_PANCONPALTA_DFS_H
#define GRAPH_PROJECT_PANCONPALTA_DFS_H

#include "Graph.h"

template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class DirectedGraph;


template<typename data_t, typename weight_t>
class DFS {
private:
    enum graphtype {
        UNDIRECTEDGRAPH = 0, DIRECTEDGRAPH
    };
    graphtype type;
    umap<id_t, vertex_t *> vertexes;
    dset_t *VertexSets;
    stack_t currentPath;

    graph_t *Apply();

    void prepareDFS();

public:
    ~DFS() {
        delete VertexSets;
    }

    explicit DFS(UnDirectedGraph<data_t, weight_t> const &graph) {
        type = graphtype::UNDIRECTEDGRAPH;
        vertexes = graph.vertexes;
        prepareDFS();
    }

    explicit DFS(DirectedGraph<data_t, weight_t> const &graph) {
        type = graphtype::DIRECTEDGRAPH;
        vertexes = graph.vertexes;
        prepareDFS();
    }

    //need to: delete &returnedgraph;
    UnDirectedGraph<data_t, weight_t> undiApply() {
        return *(UnDirectedGraph<data_t, weight_t> *) (Apply());
    }

    DirectedGraph<data_t, weight_t> diApply() {
        return *(DirectedGraph<data_t, weight_t> *) (Apply());
    }

};

template<typename data_t, typename weight_t>
void DFS<data_t, weight_t>::prepareDFS() {
    //Preparing for the algorithm
    std::vector<id_t> vs(vertexes.size());
    for (auto &it: vertexes) {
        //adding the vertexes to the disjoin set
        vs.push_back(it.first);
    }
    VertexSets = new dset_t(vs);
    //setting the root of the tree
    currentPath.push(vertexes.begin()->second);
    //Preparation done
}

template<typename data_t, typename weight_t>
graph_t *DFS<data_t, weight_t>::Apply() {
    graph_t *DFS = nullptr;
    switch (type) {
        case graphtype::DIRECTEDGRAPH:
            DFS = new DirectedGraph<data_t, weight_t>;
            break;
        default:
            DFS = new UnDirectedGraph<data_t, weight_t>;
            break;
    }
    //Executing the algorithm
    vertex_t *currentVertex = nullptr;
    vertex_t *nextVertex = nullptr;
    while (!currentPath.empty()) {
        currentVertex = currentPath.top();
        //if current is a new vertex in DFS
        if (DFS->vertexes.find(currentVertex->id) == DFS->vertexes.end()) {
            DFS->insertVertex(currentVertex->id, currentVertex->data);
        }
        for (auto &currentEdge: currentVertex->edges) {
            //cuz the graph is undirected it needs to check wich vertex follows the current in the current edge
            if (currentVertex == currentEdge->vertexes[0]) {
                nextVertex = currentEdge->vertexes[1];
            } else {
                nextVertex = currentEdge->vertexes[0];
            }
            //checking if the nodes of the edge are already conected
            if (VertexSets->Find(getIdOf(currentVertex)) == VertexSets->Find(getIdOf(nextVertex))) {
                continue;
            }
            //else
            DFS->insertVertex(nextVertex->id, nextVertex->data);
            VertexSets->Union(VertexSets->Find(getIdOf(currentVertex)),
                              VertexSets->Find(getIdOf(nextVertex)));
            DFS->createEdge(getIdOf(currentVertex), getIdOf(nextVertex), currentEdge->weight);
            currentPath.push(nextVertex);
            currentVertex = nextVertex;//this means that the path continues
            break;
        }
        //check if the path ends
        if (currentVertex != nextVertex) {
            currentPath.pop();//returns to the previus node
        }
    }

    return DFS;
}

#endif //GRAPH_PROJECT_PANCONPALTA_DFS_H
