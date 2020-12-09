#include "Graph/kruskal.h"
#include "Graph/prim.h"
#include "Graph/bfs.h"
#include "Graph/dfs.h"
#include "Graph/FloydWarshall.h"
#include "Tester/tester.h"

int main() {
    //Tester::executeParser(file::airports);
    //Tester::executeExamples();
    DirectedGraph<int, int> graph;
    graph.insertVertex("A", 1);
    graph.insertVertex("B", 2);
    graph.insertVertex("C", 3);
    graph.insertVertex("D", 4);
    graph.insertVertex("E", 5);
    graph.createEdge("A", "B", 1);
    graph.createEdge("C", "A", 2);
    graph.createEdge("C", "B", 6);
    graph.createEdge("C", "E", 5);
    graph.createEdge("B", "E", 4);
    graph.createEdge("E", "D", 3);
    graph.display();
    std::cout << "\n";
    auto bfs = BFS<int, int>(graph, "C");
    auto ans = bfs.directedApply();
    ans.display();
    return EXIT_SUCCESS;
}
