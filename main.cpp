#include "Graph/kruskal.h"
#include "Graph/prim.h"
#include "Graph/bfs.h"
#include "Graph/FloydWarshall.h"
#include "Tester/tester.h"

int main() {
    //Tester::executeParser(file::airports);
    //Tester::executeExamples();
    /*UnDirectedGraph<int, int> graph;
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
    graph.createEdge("D", "E", 3);
    graph.display();

    FloydWarshall<int, int>floyd(graph);
    floyd.displayDistances();
    floyd.displayPaths();
    floyd.showPath("A", "D");*/
    return EXIT_SUCCESS;
}
