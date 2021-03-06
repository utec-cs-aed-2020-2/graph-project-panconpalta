/*#include "Graph/project.h"

int main() {
    //Tester::executeParser(file::airports);
    Tester::executeExamples();

    return EXIT_SUCCESS;
}
*/
#include "Graph/project.h"


struct point {
    int x;
    int y;
};

double heuristic(point a, point b) {
    return pow((pow((a.x - b.x), 2) + pow(a.y - b.y, 2)), 0.5);
}


int main() {
    string s[4] = {"a", "b", "c", "d"};
    point points[4] = {
            {1, 2},
            {2, 3},
            {3, 4},
            {5, 6}
    };
    DirectedGraph<point, double> g1;
    UnDirectedGraph<point, double> g2;
    for (int i = 0; i < 4; i++) {
        g1.insertVertex(s[i], points[i]);
        g2.insertVertex(s[i], points[i]);
    }
    for (int i = 0; i < 3; i++) {
        g1.createEdge(s[i], s[i + 1], 1);
        g2.createEdge(s[i], s[i + 1], 1);
    }

    Astar<point, double> A1(g1, heuristic, heuristic);
    Astar<point, double> A2(g2, heuristic, heuristic);
    g1.display();
    g2.display();

    //A1.DirectedApply("a", "d").display();
    A2.UnDirectedApply("a", "d").display();

    return 0;
}