#ifndef GRAPH_PROJECT_PANCONPALTA_BFS_H
#define GRAPH_PROJECT_PANCONPALTA_BFS_H

#include "utilityTypes.h"


template<typename data_t, typename weight_t>
class UnDirectedGraph;

template<typename data_t, typename weight_t>
class DirectedGraph;



template<typename data_t, typename weight_t>
class BFS {
private:
	enum graphtype{
		UNDIRECTEDGRAPH=0, DIRECTEDGRAPH
	};

	graphtype type;
    umap<id_t, vertex_t *> vertexes;
    queue_t Path;
	dset_t* VertexSets;

	graph_t* Apply();
	void prepareBFS();
public:
    ~BFS(){
		delete VertexSets;
    }
	explicit BFS(UnDirectedGraph<data_t, weight_t> const &graph){
		type= graphtype::UNDIRECTEDGRAPH;
		vertexes= graph.vertexes;
		prepareBFS();
	}

    explicit BFS(DirectedGraph<data_t, weight_t> const &graph){
		type= graphtype::DIRECTEDGRAPH;
		vertexes= graph.vertexes;
		prepareBFS();
	}

	//need to: delete &returnedgraph;
	UnDirectedGraph<data_t, weight_t> undiApply(){
		return *(UnDirectedGraph<data_t, weight_t>*)(Apply());
	}
	DirectedGraph<data_t, weight_t> diApply(){
		return *(DirectedGraph<data_t, weight_t>*)(Apply());
	}

};

template<typename data_t, typename weight_t>
void BFS<data_t,weight_t>::prepareBFS(){
//Preparing for the algorithm
std::vector<id_t> vs(vertexes.size());
for(auto& it: vertexes){
	//adding the vertexs to the disjoin set
	vs.push_back(it.first);
}
VertexSets = new dset_t(vs);
//setting the root of the tree
Path.push(vertexes.begin()->second);
//Preparation done
}

template<typename data_t, typename weight_t>
graph_t* BFS<data_t,weight_t>::Apply(){	
	graph_t* BFS=nullptr;
	switch (type){
	case graphtype::DIRECTEDGRAPH:
		BFS = new UnDirectedGraph<data_t,weight_t>;
		break;
	default:
		BFS = new DirectedGraph<data_t,weight_t>;
		break;
	}
	//Executing the algorithm
	vertex_t* currentVertex=nullptr;
	vertex_t* nextVertex=nullptr;
	while(!Path.empty()){
		currentVertex=Path.front();
		//if current is a new vertex in BFS
		if(BFS->vertexs.find(currentVertex->id)==BFS->vertexs.end()){
			BFS->insertVertex(currentVertex->id,currentVertex->data);
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
			if(VertexSets->Find(getIdOf(currentVertex)) == VertexSets->Find(getIdOf(nextVertex))){
				continue;
			}
			//else
			if(BFS->vertexs.find(nextVertex->id)==BFS->vertexs.end()){
				BFS->insertVertex(nextVertex->id,nextVertex->data);
			}
			VertexSets->Union(VertexSets->Find(getIdOf(currentVertex)),
								VertexSets->Find(getIdOf(nextVertex)));
			BFS->createEdge(getIdOf(currentVertex),getIdOf(nextVertex),currentEdge->weight);
			Path.push(nextVertex);
		}
	}
	return BFS;
}


#endif //GRAPH_PROJECT_PANCONPALTA_BFS_H
