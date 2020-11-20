#ifndef GRAPH_PROJECT_PANCONPALTA_PARSER_H
#define GRAPH_PROJECT_PANCONPALTA_PARSER_H

#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "../Graph/UndirectedGraph.h"
#include "../Graph/DirectedGraph.h"

#include <fstream>
#include <cmath>

enum file {
    pe, airports
};

class Parser {
private:
    rapidjson::Document doc;
    std::string path;
public:
    Parser() = default;

    void readJSON(file json_file = pe);

    void uGraphMake(UnDirectedGraph<Airport, double> &graph);

    void dGraphMake(DirectedGraph<Airport, double> &graph);

    void clear();

    std::string getPath();

};

void Parser::readJSON(file json_file) {
    path = json_file == pe ? "pe" : "airports";
    std::ifstream file("../Parser/Data/" + path + ".json", std::ifstream::in);
    std::string json = "", line;
    if (file.is_open()) {
        while (file >> line) {
            json += line;
        }
    } else
        throw std::invalid_argument("Could not open file");
    doc.Parse(json.c_str());
}

void Parser::uGraphMake(UnDirectedGraph<Airport, double> &graph) {
    //Creating vertexes
    for (auto &it: doc.GetArray()) {
        try {
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
    //Creating edges
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
}

void Parser::dGraphMake(DirectedGraph<Airport, double> &graph) {
//Creating vertexes
    for (auto &it: doc.GetArray()) {
        try {
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
    //Creating edges
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
}

void Parser::clear() {
    doc.Clear();
    path.clear();
}

std::string Parser::getPath() {
    return path;
}


#endif //GRAPH_PROJECT_PANCONPALTA_PARSER_H
