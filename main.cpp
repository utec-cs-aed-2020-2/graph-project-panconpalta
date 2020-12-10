#include "Graph/kruskal.h"
#include "Graph/prim.h"
#include "Graph/bfs.h"
#include "Graph/dfs.h"
#include "Graph/FloydWarshall.h"
#include "Graph/BellmanFord.h"
#include "Graph/SCC.h"
#include "Tester/tester.h"

int main() {
    //Tester::executeParser(file::airports);
    //Tester::executeExamples();
    DirectedGraph<int, int> graph;
    graph.insertVertex("a", 0);
    graph.insertVertex("b", 1);
    graph.insertVertex("c", 2);
    graph.insertVertex("d", 3);
    graph.insertVertex("e", 4);
    graph.insertVertex("f", 4);
    graph.insertVertex("g", 4);
    graph.insertVertex("h", 4);
    graph.insertVertex("i", 4);
    graph.createEdge("a", "b", 1);
    graph.createEdge("b", "e", 2);
    graph.createEdge("e", "a", 6);
    graph.createEdge("e", "f", 5);
    graph.createEdge("b", "f", 4);
    graph.createEdge("f", "g", 4);
    graph.createEdge("g", "f", 4);
    graph.createEdge("b", "c", 4);
    graph.createEdge("c", "d", 4);
    graph.createEdge("d", "c", 4);
    graph.createEdge("c", "g", 4);
    graph.createEdge("d", "h", 4);
    graph.createEdge("h", "d", 4);
    graph.createEdge("d", "i", 4);
    graph.createEdge("i", "d", 4);
    graph.display();
    std::cout << "\n";
    auto scc = SCC<int, int>(graph);
    scc.apply().display();
    scc.displayComponents();
    return EXIT_SUCCESS;
}
