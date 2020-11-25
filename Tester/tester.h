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

    static void unDirectedSwitch(UnDirectedGraph<data_type, weight_type> &graph, int input);

    static void directedExample();

    static void directedSwitch(DirectedGraph<data_type, weight_type> &graph, int input);


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
    umap<std::string, std::pair<double, double>> performance;
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
    Kruskal<Airport, double> kruskal(unDirectedGraph);
    auto kResult = kruskal.apply();
    e1 = clock();
    performance.insert(std::make_pair("kruskal", std::make_pair(double(e1 - s1) / double(CLOCKS_PER_SEC), -1)));
    s1 = clock();
    Prim<Airport, double> prim(unDirectedGraph, "2789");
    auto pResult = prim.apply();
    e1 = clock();
    performance.insert(std::make_pair("prim", std::make_pair(double(e1 - s1) / double(CLOCKS_PER_SEC), -1)));
    //isConnected runs correctly, but takes time to test with airports.json
    //If wanted, just uncomment this section
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
    for (auto it = performance.begin(); it != performance.end(); ++it) {
        std::cout << it->first << "\n";
        std::cout << "\t\t\t" << it->second.first << " s\t\t" << it->second.second << " s\n";
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
    UnDirectedGraph<data_type, weight_type> graph;
    int input = 1;
    while (input != 0) {
        std::cout
                << "Options\n1. Add Vertex\t2. Add Edge\t3. Delete Vertex\n4. Delete Edge\t5. Display\t6. Kruskal\n7. Prim\t\t8. Connected\t9. Density\n10. Clear\t0. Finish\nChoose:";
        std::cin >> input;
        if (input == 0)
            break;
        if (input > 10)
            continue;
        unDirectedSwitch(graph, input);
    }
    std::cout << "Finished!\n";
}

void Tester::unDirectedSwitch(UnDirectedGraph<std::string, double> &graph, int input) {
    int n;
    switch (input) {
        case 1: {
            std::cout << "1. Add Vertex\n";
            std::cout << "Choose number of vertexes:";
            std::cin >> n;
            id_t id;
            data_type data;
            for (int i = 0; i < n; ++i) {
                std::cout << i + 1 << ". id:";
                std::cin >> id;
                std::cout << i + 1 << ". data:";
                std::cin >> data;
                if (!graph.insertVertex(id, data))
                    std::cout << "Vertex already exists!\n";
                else
                    std::cout << "Vertex added!\n";
            }
            std::cout << "\n";
            break;
        }
        case 2: {
            std::cout << "2. Add Edge\n";
            std::cout << "Choose number of edges:";
            std::cin >> n;
            id_t id1, id2;
            weight_type weight;
            for (int i = 0; i < n; ++i) {
                std::cout << i + 1 << ". id (from):";
                std::cin >> id1;
                std::cout << i + 1 << ". id (to):";
                std::cin >> id2;
                std::cout << i + 1 << ". weight:";
                std::cin >> weight;
                if (!graph.createEdge(id1, id2, weight))
                    std::cout << "Edge already exists!\n";
                else
                    std::cout << "Edge added!\n";
            }
            std::cout << "\n";
            break;
        }
        case 3: {
            std::cout << "3. Delete Vertex\n";
            std::cout << "Choose number of vertexes:";
            std::cin >> n;
            id_t id;
            for (int i = 0; i < n; ++i) {
                std::cout << i + 1 << ". id:";
                std::cin >> id;
                if (!graph.deleteVertex(id))
                    std::cout << "Vertex does not exist\n";
                else
                    std::cout << "Vertex deleted!\n";
            }
            std::cout << "\n";
            break;
        }
        case 4: {
            std::cout << "4. Delete Edge\n";
            std::cout << "Choose number of edges:";
            std::cin >> n;
            id_t id1, id2;
            for (int i = 0; i < n; ++i) {
                std::cout << i + 1 << ". id (from):";
                std::cin >> id1;
                std::cout << i + 1 << ". id (to):";
                std::cin >> id2;
                if (!graph.deleteEdge(id1, id2))
                    std::cout << "Edge does not exist!\n";
                else
                    std::cout << "Edge deleted!\n";
            }
            std::cout << "\n";
            break;
        }
        case 5: {
            std::cout << "5. Display\n";
            graph.display();
            std::cout << "\n";
            break;
        }
        case 6: {
            std::cout << "6. Kruskal\n";
            Kruskal<data_type, weight_type> kruskal(graph);
            kruskal.apply().display();
            std::cout << "\n";
            break;
        }
        case 7: {
            std::cout << "7. Prim\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                Prim<data_type, weight_type> prim(graph, input);
                prim.apply().display();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 8: {
            std::cout << "8. isConnected\n";
            std::cout << std::boolalpha << graph.isConnected() << "\n\n";
            break;
        }
        case 9: {
            std::cout << "9. Density\n";
            std::cout << graph.density() << "\n\n";
            break;
        }
        case 10: {
            std::cout << "10. Clear\n";
            graph.clear();
            std::cout << "Graph cleared!\n\n";
            break;
        }
    }
}

void Tester::directedExample() {
    DirectedGraph<data_type, weight_type> graph;
    int input = 1;
    while (input != 0) {
        std::cout
                << "Options\n1. Add Vertex\t2. Add Edge\t3. Delete Vertex\n4. Delete Edge\t5. Display\t6. Connected\n7. Density \t8. Clear\t9. Strongly Connected\n0. Finish\nChoose:";
        std::cin >> input;
        if (input == 0)
            break;
        if (input > 10)
            continue;
        directedSwitch(graph, input);
    }

    std::cout << "Finished!\n";

}

void Tester::directedSwitch(DirectedGraph<std::string, double> &graph, int input) {
    int n;
    switch (input) {
        case 1: {
            std::cout << "1. Add Vertex\n";
            std::cout << "Choose number of vertexes:";
            std::cin >> n;
            id_t id;
            data_type data;
            for (int i = 0; i < n; ++i) {
                std::cout << i + 1 << ". id:";
                std::cin >> id;
                std::cout << i + 1 << ". data:";
                std::cin >> data;
                if (!graph.insertVertex(id, data))
                    std::cout << "Vertex already exists!\n";
                else
                    std::cout << "Vertex added!\n";
            }
            std::cout << "\n";
            break;
        }
        case 2: {
            std::cout << "2. Add Edge\n";
            std::cout << "Choose number of edges:";
            std::cin >> n;
            id_t id1, id2;
            weight_type weight;
            for (int i = 0; i < n; ++i) {
                std::cout << i + 1 << ". id (from):";
                std::cin >> id1;
                std::cout << i + 1 << ". id (to):";
                std::cin >> id2;
                std::cout << i + 1 << ". weight:";
                std::cin >> weight;
                if (!graph.createEdge(id1, id2, weight))
                    std::cout << "Edge already exists!\n";
                else
                    std::cout << "Edge added!\n";
            }
            std::cout << "\n";
            break;
        }
        case 3: {
            std::cout << "3. Delete Vertex\n";
            std::cout << "Choose number of vertexes:";
            std::cin >> n;
            id_t id;
            for (int i = 0; i < n; ++i) {
                std::cout << i + 1 << ". id:";
                std::cin >> id;
                if (!graph.deleteVertex(id))
                    std::cout << "Vertex does not exist\n";
                else
                    std::cout << "Vertex deleted!\n";
            }
            std::cout << "\n";
            break;
        }
        case 4: {
            std::cout << "4. Delete Edge\n";
            std::cout << "Choose number of edges:";
            std::cin >> n;
            id_t id1, id2;
            for (int i = 0; i < n; ++i) {
                std::cout << i + 1 << ". id (from):";
                std::cin >> id1;
                std::cout << i + 1 << ". id (to):";
                std::cin >> id2;
                if (!graph.deleteEdge(id1, id2))
                    std::cout << "Edge does not exist!\n";
                else
                    std::cout << "Edge deleted!\n";
            }
            std::cout << "\n";
            break;
        }
        case 5: {
            std::cout << "5. Display\n";
            graph.display();
            std::cout << "\n";
            break;
        }
        case 6: {
            std::cout << "6. isConnected\n";
            std::cout << std::boolalpha << graph.isConnected() << "\n\n";
            break;
        }
        case 7: {
            std::cout << "7. Density\n";
            std::cout << graph.density() << "\n\n";
            break;
        }
        case 8: {
            std::cout << "8. Clear\n";
            graph.clear();
            std::cout << "Graph cleared!\n\n";
            break;
        }
        case 9: {
            std::cout << "9. isStronglyConnected\n";
            std::cout << std::boolalpha << graph.isStronglyConnected() << "\n\n";
            break;
        }
    }

}


#endif //GRAPH_PROJECT_PANCONPALTA_TESTER_H
