#ifndef GRAPH_PROJECT_PANCONPALTA_TESTER_H
#define GRAPH_PROJECT_PANCONPALTA_TESTER_H

#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"
#include "../Parser/parser.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
enum file {
    airports, pe
};

class Tester {
public:
    Tester() = default;

    static void executeParser(file json_file = pe) {
        std::string path;
        if (json_file == pe)
            path = "pe";
        else
            path = "airports";
        std::ifstream file("../Parser/Data/" + path + ".json", std::ifstream::in);
        std::string json = "", line;
        if (file.is_open()) {
            while (file >> line) {
                json += line;
            }
        } else
            return;

        rapidjson::Document doc;
        doc.Parse(json.c_str());

        //UnDirectedGraph<rapidjson::GenericObject<false,rapidjson::Value>,double> graph;
        UnDirectedGraph<Airport, double> graph;
        for (auto &it: doc.GetArray()) {
            try {
                //std::cout<<it["Airport_ID"].GetString()<<"\n";
                //std::cout<<it["Name"].GetString()<<"\n";
                //std::cout<<it["City"].GetString()<<"\n";
                //std::cout<<it["Country"].GetString()<<"\n";
                //std::cout<<it["Latitude"].GetString()<<"\n";
                //std::cout<<it["Longitude"].GetString()<<"\n";
                //std::cout<<"-------------------------------------------\n";
                graph.insertVertex(it["Airport_ID"].GetString(), Airport(
                        std::stoi(it["Airport_ID"].GetString()),
                        it["Name"].GetString(),
                        it["City"].GetString(),
                        it["Country"].GetString(),
                        std::stod(it["Latitude"].GetString()),
                        std::stod(it["Longitude"].GetString())
                                   )
                );
            } catch (...) {
                continue;
            }
        }
        //std::cout<<"----------------------END OF PARSING: vertex added---------------------\n";
        //graph.display();
        for (auto &airport: doc.GetArray()) {
            for (auto &dest: airport["destinations"].GetArray()) {
                try {
                    graph.createEdge(
                            airport["Airport_ID"].GetString(),
                            dest.GetString(),
                            //euclidian distance
                            sqrt(
                                    pow(graph[airport["Airport_ID"].GetString()].latitude -
                                        graph[dest.GetString()].latitude, 2)
                                    +
                                    pow(graph[airport["Airport_ID"].GetString()].longitude -
                                        graph[dest.GetString()].longitude, 2)
                            )
                    );
                } catch (...) {
                    continue;
                }
            }
        }
        clock_t start, end;
        std::cout<<"----------------------Graph---------------------\n";

        graph.display();


        //std::cout << "density: " << graph.density() << "\n";
        //std::cout << "empty: " << graph.empty() <<"\n";
        //std::cout << "connected: " << graph.isConnected() << "\n";
        //std::cout << "strongly connected: "<< graph.isStronglyConnected() <<"\n";
        //std::cout << "bipartite: "<< graph.isBipartite() <<"\n";
        //graph.display();
        std::cout << "----------------------Kruskal:---------------------\n";
        start = clock();
        auto kruskal = graph.execKruskal();
        end = clock();
        std::cout << "Kruskal execution time: " << double(end - start) / double(CLOCKS_PER_SEC) << "\n";
        std::cout << "----------------------Prim From 2789:---------------------\n";
        start = clock();
        auto prim = graph.execPrim("2789");
        end = clock();
        std::cout << "Prim execution time: " << double(end - start) / double(CLOCKS_PER_SEC) << "\n";

        std::cout << "----------------------Clear:---------------------\n";
        graph.clear();
        std::cout << "empty: " << std::boolalpha << graph.empty() << "\n";
    }

};

#endif //GRAPH_PROJECT_PANCONPALTA_TESTER_H
