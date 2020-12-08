#ifndef GRAPH_PROJECT_PANCONPALTA_DFS_H
#define GRAPH_PROJECT_PANCONPALTA_DFS_H

#include "utilityTypes.h"

template<typename data_t, typename weight_t>
class DFS {
private:
		graph_t DFS;
		std::vector<id_t> vs(vertexs.size());
		stack_t currentPath;

graph_t execDFS(){


		//Preparing for the algorithm
		for(auto& it: vertexs){
			//adding the vertexs to the disjoin set
			vs.push_back(it.first);
		}
		dset_t VertexSets(vs);
		//setting the root of the tree
		currentPath.push(vertexs.begin()->second);
		//Preparation done
		//Executing the algorithm
		vertex_t* currentVertex=nullptr;
		vertex_t* nextVertex=nullptr;
		while(!currentPath.empty()){
			currentVertex=currentPath.top();
			//if current is a new vertex in DFS
			if(DFS.vertexs.find(currentVertex->id)==DFS.vertexs.end()){
				DFS.insertVertex(currentVertex->id,currentVertex->data);
			}
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
				DFS.insertVertex(nextVertex->id,nextVertex->data);
				VertexSets.Union(VertexSets.Find(getIdOf(currentVertex)),
								 VertexSets.Find(getIdOf(nextVertex)));
				DFS.createEdge(getIdOf(currentVertex),getIdOf(nextVertex),currentEdge->weight);
				currentPath.push(nextVertex);
				currentVertex=nextVertex;//this means that the path continues
				break;
			}
			//check if the path ends
			if(currentVertex!=nextVertex){
				currentPath.pop();//returns to the previus node
			}
		}

		return DFS;
	}
};


#endif //GRAPH_PROJECT_PANCONPALTA_DFS_H
