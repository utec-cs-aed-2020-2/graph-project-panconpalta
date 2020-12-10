#include "Graph/kruskal.h"
#include "Graph/prim.h"
#include "Graph/bfs.h"
#include "Graph/dfs.h"
#include "Graph/FloydWarshall.h"
#include "Graph/BellmanFord.h"
#include "Graph/SCC.h"
#include "Graph/Dijkstra.h"
#include "Tester/tester.h"

int main() {
    //Tester::executeParser(file::airports);
    //Tester::executeExamples();
    DirectedGraph<int, int> graph;
    graph.insertVertex("A", 0);
    graph.insertVertex("B", 0);
    graph.insertVertex("C", 0);
    graph.insertVertex("D", 0);
    graph.insertVertex("E", 0);
    graph.createEdge("A", "B", 6);
    graph.createEdge("A", "D", 1);
    graph.createEdge("B", "D", 2);
    graph.createEdge("D", "E", 1);
    graph.createEdge("E", "B", 2);
    graph.createEdge("C", "B", 5);
    graph.createEdge("E", "C", 5);
    graph.display();
    std::cout << "\n";
    auto dijkstra = Dijkstra<int, int>(graph, "A");
    dijkstra.displayDistances();
    dijkstra.showPath("B");
    auto bellman = BellmanFord<int, int>(graph, "A");
    bellman.displayDistances();
    bellman.showPath("B");
    return EXIT_SUCCESS;
}
