#include <iostream>

#include "Tester/tester.h"
#include "Parser/parser.h"
#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
using namespace std;

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
    std::cout << boolalpha << graph.createEdge("first", "second", 1.4) << "\n";
    std::cout << boolalpha << graph.createEdge("second", "third", 3.5) << "\n";
    std::cout << boolalpha << graph.deleteEdge("third", "second") << "\n";

    //std::cout << boolalpha << graph.deleteVertex("first") << "\n";
    //std::cout << boolalpha << graph.deleteVertex("second") << "\n";
    //std::cout << boolalpha << graph.deleteEdge("second", "third") << "\n";
    //std::cout << boolalpha << graph.deleteEdge("second", "third") << "\n";
    graph.display();

    
    return EXIT_SUCCESS;
}