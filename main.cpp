#include <iostream>
#include <fstream>
#include <cmath>

#include "Parser/include/rapidjson/document.h"
#include "Tester/tester.h"
#include "Parser/parser.h"
#include "Graph/UndirectedGraph.cpp"
#include "Graph/DirectedGraph.cpp"
#include "Parser/parser.h"

int main(int argc, char *argv[]) {
	std::ifstream file("Parser/Data/airports.json", std::ifstream::in); 
	std::string json="",line;
	if(file.is_open()){
		while(file>>line){
			json+=line;
		}
	}
	else{
		return 1;
	}
	rapidjson::Document doc;
	doc.Parse(json.c_str());

	//UnDirectedGraph<rapidjson::GenericObject<false,rapidjson::Value>,double> graph;
	UnDirectedGraph<Airport,double> graph;
	for(auto& it: doc.GetArray()){
		try{
			std::cout<<it["Airport_ID"].GetString()<<"\n";
			std::cout<<it["Name"].GetString()<<"\n";
			std::cout<<it["City"].GetString()<<"\n";
			std::cout<<it["Country"].GetString()<<"\n";
			std::cout<<it["Latitude"].GetString()<<"\n";
			std::cout<<it["Longitude"].GetString()<<"\n";
			std::cout<<"-------------------------------------------\n";
			graph.insertVertex(it["Airport_ID"].GetString(),Airport(
						std::stoi(it["Airport_ID"].GetString()),
						it["Name"].GetString(),
						it["City"].GetString(),
						it["Country"].GetString(),
						std::stod(it["Latitude"].GetString()),
						std::stod(it["Longitude"].GetString())
						)
					);
			}catch(...){
				continue;
			}
	}
	std::cout<<"----------------------END OF PARSING: vertex added---------------------\n";
	graph.display();
	for(auto& airport: doc.GetArray()){
		for(auto& dest: airport["destinations"].GetArray()){
			try{
				graph.createEdge(
						airport["Airport_ID"].GetString(),
						dest.GetString(),
						//euclidian distance
						sqrt(
							pow(graph[airport["Airport_ID"].GetString()].latitude - graph[dest.GetString()].latitude,2 )
							+
							pow(graph[airport["Airport_ID"].GetString()].longitude - graph[dest.GetString()].longitude,2)
							)
						);
			}catch(...){
				continue;
			}
		}
	}
	std::cout<<"----------------------END OF PARSING: Edges added---------------------\n";
	graph.display();
	return 0;
}
