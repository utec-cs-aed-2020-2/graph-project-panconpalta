#include "Astar.h"
#include "kruskal.h"
#include "prim.h"
#include "DFS.h"
#include "BFS.h"
#include "FloydWarshall.h"
#include "SCC.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "../UndirectedGraph.h"
#include "../DirectedGraph.h"
#include <cmath>


struct  point{
    int x;
    int y;
};

double heuristic(point a,point b){
    return pow((pow((a.x - b.x),2)+pow(a.y - b.y ,2)),0.5);
}



int main(){
    string s[4]={"a","b","c","d"};
    point points[4]={
        {1,2},
        {2,3},
        {3,4},
        {5,6}
    };
    DirectedGraph<point, double> g1;
    UnDirectedGraph<point, double> g2;
    for(int i=0;i<4;i++){
        g1.insertVertex(s[i],points[i]);
        g2.insertVertex(s[i],points[i]);
    }
    for(int i=0;i<3;i++){
        g1.createEdge(s[i],s[i+1],i);
        g2.createEdge(s[i],s[i+1],i);
    }

    Astar<point,double> A1(g1,heuristic);
    Astar<point,double> A2(g2,heuristic);

    std::cout<<"Directed graph\n";
    g1.display();
    std::cout<<"UnDirected graph\n";
    g2.display();

    std::cout<<"A* Directed graph\n";
    A1.DirectedApply("a","d").display();
    std::cout<<"A* UnDirected graph\n";
    A2.UnDirectedApply("a","d").display();

    return 0;
}