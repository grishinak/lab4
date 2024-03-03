#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Point {
    int x, y;
};

class Graph {
private:
    int V_;
    std::vector<std::vector<int>> adj_;
    std::vector<Point> positions_;
    
    double distance(const Point& p1, const Point& p2);
    void applyForce(Point& p1, Point& p2);
    void repelNodes();
    void adjustSpringForces();

public:
    std::vector<std::pair<int, int>> edges;
    const int kspring_ = 1; // Spring constant
    Graph(int V);
    void addEdge(int u, int v);
  //  void addSingleEdge(const std::pair<int, int>& edge);
    void addEdges( std::vector<std::pair<int, int>>& edges);
    void planarize();
    void printPositions();
    int getV();
    Point getPosition(int index);
};

#endif // GRAPH_H