#ifndef GRAPH_PROJECT_PANCONPALTA_TESTER_H
#define GRAPH_PROJECT_PANCONPALTA_TESTER_H

#include "../Parser/parser.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

#define data_type std::string
#define weight_type double

class Tester {
private:
    static void unDirectedExample();

    static void directedExample();

public:
    Tester() = default;

    static void executeParser(file json_file = pe);

    static void executeExamples();

};

void Tester::executeParser(file json_file) {
    Parser parser;
    parser.readJSON(json_file);
    UnDirectedGraph<Airport, double> unDirectedGraph;
    DirectedGraph<Airport, double> DirectedGraph;
    map<std::string, std::pair<double, double>> performance;
    clock_t s1, s2, e1, e2;
    s1 = clock();
    parser.uGraphMake(unDirectedGraph);
    e1 = clock();
    s2 = clock();
    parser.dGraphMake(DirectedGraph);
    e2 = clock();
    performance.insert(std::make_pair("buildGraph", std::make_pair(double(e1 - s1) / double(CLOCKS_PER_SEC),
                                                                   double(e2 - s2) / double(CLOCKS_PER_SEC))));
    s1 = clock();
    //unDirectedGraph.execKruskal();
    e1 = clock();
    performance.insert(std::make_pair("kruskal", std::make_pair(double(e1 - s1) / double(CLOCKS_PER_SEC), -1)));
    s1 = clock();
    //unDirectedGraph.execPrim("2789");
    e1 = clock();
    performance.insert(std::make_pair("prim", std::make_pair(double(e1 - s1) / double(CLOCKS_PER_SEC), -1)));
    /*s1 = clock();
    unDirectedGraph.isConnected();
    e1 = clock();
    s2 = clock();
    DirectedGraph.isConnected();
    e2 = clock();
    performance.insert(std::make_pair("isConnected", std::make_pair(double(e1 - s1) / double(CLOCKS_PER_SEC),
                                                                    double(e2 - s2) / double(CLOCKS_PER_SEC))));
    */
    s2 = clock();
    DirectedGraph.isStronglyConnected();
    e2 = clock();
    performance.insert(std::make_pair("isStronglyConnected", std::make_pair(-1,
                                                                            double(e2 - s2) / double(CLOCKS_PER_SEC))));
    s1 = clock();
    unDirectedGraph.clear();
    e1 = clock();
    s2 = clock();
    DirectedGraph.clear();
    e2 = clock();
    performance.insert(std::make_pair("clear", std::make_pair(double(e1 - s1) / double(CLOCKS_PER_SEC),
                                                              double(e2 - s2) / double(CLOCKS_PER_SEC))));
    std::cout << "================================================" << std::endl;
    std::cout << "TIME PERFORMANCE - PARSER " << parser.getPath() << ".json" << std::endl;
    std::cout << "================================================" << std::endl;

    std::cout << "\nmethod\t\t\tunDirected\tdirected\n";
    for (const auto &it : performance) {
        std::cout << it.first << "\n";
        std::cout << "\t\t\t" << it.second.first << " s\t\t" << it.second.second << " s\n";
    }

}

void Tester::executeExamples() {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "Build Graph:\n1. UnDirected Graph\n2. Directed Graph\n";
    std::string input;
    while (true) {
        std::cout << "\nChoose:";
        std::cin >> input;
        if (input == "1" || input == "2")
            break;
    }
    input == "1" ? unDirectedExample() : directedExample();
}

void Tester::unDirectedExample() {
    int n;
    std::cout << "Choose number of vertexes:";
    std::cin >> n;
    id_t id;
    data_type data;

    UnDirectedGraph<data_type, weight_type> graph;
    for (int i = 0; i < n; ++i) {
        std::cout << "\nid " << i + 1 << ":";
        std::cin >> id;
        std::cout << "\ndata " << i + 1 << ":";
        std::cin >> data;
        graph.insertVertex(id, data);
    }
    graph.display();
    //TODO
}

void Tester::directedExample() {
    ///TODO

}

#endif //GRAPH_PROJECT_PANCONPALTA_TESTER_H
