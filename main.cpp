#include <iostream>

#include "Tester/tester.h"
#include "Parser/parser.h"
#include "Graph/UndirectedGraph.cpp"
#include "Graph/DirectedGraph.cpp"

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    
    //Tester::executeExamples();
    //Tester::executeParser();
    DirectedGraph<char, float> graph;
    graph.insertVertex("first", 'a');
    graph.insertVertex("second", 'b');
    graph.insertVertex("third", 'c');
    std::cout << std::boolalpha << graph.createEdge("first", "second", 1.4) << "\n";
    std::cout << std::boolalpha << graph.createEdge("second", "third", 3.5) << "\n";
    //std::cout << boolalpha << graph.deleteEdge("first", "second") << "\n";
    graph("first", "second") = 1.6;
    //std::cout << boolalpha << graph.deleteVertex("first") << "\n";
    //std::cout << boolalpha << graph.deleteVertex("second") << "\n";
    //std::cout << boolalpha << graph.deleteEdge("second", "third") << "\n";
    //std::cout << boolalpha << graph.deleteEdge("second", "third") << "\n";

    std::cout << "density: " << graph.density() << "\n";
    std::cout << "empty: " << graph.empty() <<"\n";
    std::cout << "connected: " << graph.isConnected() <<"\n";
    std::cout << "strongly connected: "<< graph.isStronglyConnected() <<"\n";
    std::cout << "bipartite: "<< graph.isBipartite() <<"\n";
    graph.display();
    graph.clear();
    std::cout << "empty: " << graph.empty() <<"\n";
    
    return EXIT_SUCCESS;
}
