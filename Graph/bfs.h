#ifndef GRAPH_PROJECT_PANCONPALTA_BFS_H
#define GRAPH_PROJECT_PANCONPALTA_BFS_H

#include "utilityTypes.h"


template<typename data_t, typename weight_t>
class Graph;

template<typename data_t, typename weight_t>
class BFS {
private:
    graph_t BFS;
    std::vector<id_t> vs(vertexs.size());
    queue_t Path;

    ~BFS(){

    }
    BFS(){

    }
    graph_t Apply

	graph_t execBFS(){
		//Preparing for the algorithm
		for(auto& it: vertexs){
			//adding the vertexs to the disjoin set
			vs.push_back(it.first);
		}
		dset_t VertexSets(vs);
		//setting the root of the tree
		Path.push(vertexs.begin()->second);
		//Preparation done
		//Executing the algorithm
		vertex_t* currentVertex=nullptr;
		vertex_t* nextVertex=nullptr;
		while(!Path.empty()){
			currentVertex=Path.front();
			//if current is a new vertex in BFS
			if(BFS.vertexs.find(currentVertex->id)==BFS.vertexs.end()){
				BFS.insertVertex(currentVertex->id,currentVertex->data);
			}
			Path.pop();
			for(auto& currentEdge: currentVertex->edges){
			//cuz the graph is undirected it needs to check wich vertex follows the current in the current edge
				if(currentVertex==currentEdge->vertexs[0]){
					nextVertex=currentEdge->vertexs[1];
				}else{
					nextVertex=currentEdge->vertexs[0];
				}
			//checking if the nodes of the edge are already conected
				if(VertexSets.Find(getIdOf(currentVertex)) == VertexSets.Find(getIdOf(nextVertex))){
					continue;
				}
				//else
				if(BFS.vertexs.find(nextVertex->id)==BFS.vertexs.end()){
					BFS.insertVertex(nextVertex->id,nextVertex->data);
				}
				VertexSets.Union(VertexSets.Find(getIdOf(currentVertex)),
								 VertexSets.Find(getIdOf(nextVertex)));
				BFS.createEdge(getIdOf(currentVertex),getIdOf(nextVertex),currentEdge->weight);
				Path.push(nextVertex);
			}
		}
		return BFS;
	}
};


#endif //GRAPH_PROJECT_PANCONPALTA_BFS_H
