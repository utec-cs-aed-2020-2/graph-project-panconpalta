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
    std::vector<std::tuple<std::string, double, double>> performance;
    clock_t s1, s2, e1, e2;
    //parse data - build graph
    s1 = clock();
    parser.uGraphMake(unDirectedGraph);
    e1 = clock();
    s2 = clock();
    parser.dGraphMake(DirectedGraph);
    e2 = clock();
    performance.push_back(std::make_tuple("buildGraph", double(e1 - s1) / double(CLOCKS_PER_SEC),
                                          double(e2 - s2) / double(CLOCKS_PER_SEC)));

    std::cout << "================================================" << std::endl;
    std::cout << "TOP DISPLAY - PARSER " << parser.getPath() << ".json" << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "\nunDirected:\n";
    unDirectedGraph.displayTop();
    std::cout << "\ndirected:\n";
    DirectedGraph.displayTop();
    std::cout << "\n";
    // kruskal
    s1 = clock();
    Kruskal<Airport, double> kruskal(unDirectedGraph);
    auto kResult = kruskal.apply();
    e1 = clock();
    performance.push_back(std::make_tuple("kruskal", double(e1 - s1) / double(CLOCKS_PER_SEC), -1));

    //prim from lima - 2789
    s1 = clock();
    Prim<Airport, double> prim(unDirectedGraph, "2789");
    auto pResult = prim.apply();
    e1 = clock();
    performance.push_back(std::make_tuple("prim (lima)", double(e1 - s1) / double(CLOCKS_PER_SEC), -1));

    //isStronglyConnected
    s2 = clock();
    DirectedGraph.isStronglyConnected();
    e2 = clock();
    performance.push_back(std::make_tuple("isStronglyConnected", -1,
                                          double(e2 - s2) / double(CLOCKS_PER_SEC)));
    //bfs from lima - 2789
    s1 = clock();
    BFS<Airport, double> bfs1(unDirectedGraph, "2789");
    auto bfs1Result = bfs1.unDirectedApply();
    e1 = clock();
    s2 = clock();
    BFS<Airport, double> bfs2(DirectedGraph, "2789");
    auto bfs2Result = bfs2.directedApply();
    e2 = clock();
    performance.push_back(std::make_tuple("bfs (lima)", double(e1 - s1) / double(CLOCKS_PER_SEC),
                                          double(e2 - s2) / double(CLOCKS_PER_SEC)));
    //dfs from lima - 2789
    s1 = clock();
    DFS<Airport, double> dfs1(unDirectedGraph, "2789");
    auto dfs1Result = dfs1.unDirectedApply();
    e1 = clock();
    s2 = clock();
    DFS<Airport, double> dfs2(DirectedGraph, "2789");
    auto dfs2Result = dfs2.directedApply();
    e2 = clock();
    performance.push_back(std::make_tuple("dfs (lima)", double(e1 - s1) / double(CLOCKS_PER_SEC),
                                          double(e2 - s2) / double(CLOCKS_PER_SEC)));

    //strongly connected components
    s2 = clock();
    SCC<Airport, double> scc(DirectedGraph);
    e2 = clock();
    performance.push_back(std::make_tuple("strongly connected components", -1,
                                          double(e2 - s2) /
                                          double(CLOCKS_PER_SEC)));
    //clear
    s1 = clock();
    unDirectedGraph.clear();
    e1 = clock();
    s2 = clock();
    DirectedGraph.clear();
    e2 = clock();
    performance.push_back(std::make_tuple("clear", double(e1 - s1) / double(CLOCKS_PER_SEC),
                                          double(e2 - s2) / double(CLOCKS_PER_SEC)));

    std::cout << "================================================" << std::endl;
    std::cout << "TIME PERFORMANCE - PARSER " << parser.getPath() << ".json" << std::endl;
    std::cout << "================================================" << std::endl;

    std::cout << "\nmethod\t\t\tunDirected\tdirected\n";
    for (auto i = 0; i != performance.size(); ++i) {
        std::cout << std::get<0>(performance[i]) << "\n";
        std::cout << "\t\t\t" << std::get<1>(performance[i]) << " s\t\t" << std::get<2>(performance[i]) << " s\n";
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
                << "Options\n1. Add Vertex\t2. Add Edge\t3. Delete Vertex\n4. Delete Edge\t5. Display\t6. Kruskal\n7. Prim\t\t8. Connected\t9. Density\n10. BFS\t\t11. DFS\t\t12. Dijkstra\n13. Bellman\t14. Floyd\t15. Clear\n0. Finish\nChoose:";
        std::cin >> input;
        if (input == 0)
            break;
        if (input > 15)
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
            std::cout << "10. BFS\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                BFS<data_type, weight_type> bfs(graph, input);
                bfs.unDirectedApply().display();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 11: {
            std::cout << "11. DFS\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                DFS<data_type, weight_type> dfs(graph, input);
                dfs.unDirectedApply().display();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 12: {
            std::cout << "12. Dijkstra\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                Dijkstra<data_type, weight_type> dijkstra(graph, input);
                dijkstra.displayDistances();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 13: {
            std::cout << "13. Bellman Ford\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                BellmanFord<data_type, weight_type> bellman(graph, input);
                bellman.displayDistances();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 14: {
            std::cout << "14. Floyd Warshall\n";
            FloydWarshall<data_type, weight_type> floyd(graph);
            floyd.displayDistances();
            floyd.displayPaths();
            std::cout << "\n";
            break;
        }
        case 15: {
            std::cout << "15. Clear\n";
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
                << "Options\n1. Add Vertex\t2. Add Edge\t3. Delete Vertex\n4. Delete Edge\t5. Display\t6. Connected\n7. Density \t8. Clear\t9. Strongly Connected\n10. BFS\t\t11. DFS\t\t12. Dijkstra\n13. Bellman\t14. Floyd\t15. Strongly Connected Components\n0. Finish\nChoose:";
        std::cin >> input;
        if (input == 0)
            break;
        if (input > 15)
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
        case 10: {
            std::cout << "10. BFS\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                BFS<data_type, weight_type> bfs(graph, input);
                bfs.directedApply().display();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 11: {
            std::cout << "11. DFS\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                DFS<data_type, weight_type> dfs(graph, input);
                dfs.directedApply().display();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 12: {
            std::cout << "12. Dijkstra\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                Dijkstra<data_type, weight_type> dijkstra(graph, input);
                dijkstra.displayDistances();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 13: {
            std::cout << "13. Bellman Ford\n";
            id_t input;
            std::cout << "Choose start vertex:";
            std::cin >> input;
            try {
                BellmanFord<data_type, weight_type> bellman(graph, input);
                bellman.displayDistances();
            }
            catch (std::out_of_range) {
                std::cout << "Vertex does not exist!\n";
            }
            std::cout << "\n";
            break;
        }
        case 14: {
            std::cout << "14. Floyd Warshall\n";
            FloydWarshall<data_type, weight_type> floyd(graph);
            floyd.displayDistances();
            floyd.displayPaths();
            std::cout << "\n";
            break;
        }
        case 15: {
            std::cout << "15. Strongly Connected Components\n";
            SCC<data_type, weight_type> scc(graph);
            scc.displayComponents();
            scc.apply().display();
            std::cout << "\n";
            break;
        }
    }

}


#endif //GRAPH_PROJECT_PANCONPALTA_TESTER_H
