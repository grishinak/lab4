#include "graph.h"

#include <iostream>
#include <cmath>
#include <algorithm>

double Graph::Distance(const Point& _p1, const Point& _p2) {
    return sqrt(pow(_p1.x - _p2.x, 2) + pow(_p1.y - _p2.y, 2));
}



Graph::Graph(int _V) : V_(_V) {
    adj_.resize(_V);
    positions_.resize(_V);
}

void Graph::AddEdge(int _u, int _v) {
    adj_[_u].push_back(_v);
    adj_[_v].push_back(_u);
    edges_.push_back({_u, _v});
}


void Graph::AddEdges( std::vector<std::pair<int, int>>& _edges_) {
    for (const auto& edge : _edges_) {
        AddEdge(edge.first, edge.second);
    }
}



void Graph::PrintPositions() {
    for (int i = 0; i < V_; ++i) {
        std::cout << "Node " << i << ": (" << positions_[i].x << ", " << positions_[i].y << ")" << std::endl;
    }
}

int Graph::GetV(){
    return V_;
}

Point Graph::GetPosition(int _index) {
    if (_index >=0 && _index<=V_) {
        return positions_[_index];
    } else {
        return {0,0};
    }
}


void Graph::FRPlanarize() {



    // Инициализация случайных позиций вершин
    for (int i = 0; i < V_; ++i) {
        positions_[i].x = rand() % 2000; // Примерный размер поля для случайной инициализации
        positions_[i].y = rand() % 2000; // Примерный размер поля для случайной инициализации
    }

    // Итеративный процесс для планаризации графа
    for (int iter = 0; iter < kIterations; ++iter) {
        std::vector<Point> forces(V_, {0, 0});

        // Расчет отталкивающих сил между вершинами
        for (int i = 0; i < V_; ++i) {
            for (int j = 0; j < V_; ++j) {
                if (i != j) {
                    double dx = positions_[j].x - positions_[i].x;
                    double dy = positions_[j].y - positions_[i].y;
                    double distance = std::max(sqrt(dx * dx + dy * dy), 0.0001); // Избегаем деления на ноль
                    double force = repulsiveForceFactor_ / distance;
                    forces[i].x -= force * dx / distance;
                    forces[i].y -= force * dy / distance;
                }
            }
        }

        // Расчет притягивающих сил для ребер
        for (const auto& edge : edges_) {
            int u = edge.first;
            int v = edge.second;
            double dx = positions_[v].x - positions_[u].x;
            double dy = positions_[v].y - positions_[u].y;
            double distance = std::max(sqrt(dx * dx + dy * dy), 0.0001); // Избегаем деления на ноль
            double force = springForceFactor_ * (distance - kIdealEdgeLength);
            forces[u].x += force * dx / distance;
            forces[u].y += force * dy / distance;
            forces[v].x -= force * dx / distance;
            forces[v].y -= force * dy / distance;
        }

        // Обновление позиций вершин с учетом сил
        for (int i = 0; i < V_; ++i) {
            positions_[i].x += forces[i].x;
            positions_[i].y += forces[i].y;
        }

        // Охлаждение системы
        repulsiveForceFactor_ *= kCoolingFactor;
        springForceFactor_ *= kCoolingFactor;
    }

    // Приведение позиций к типу int
    for (int i = 0; i < V_; ++i) {
        positions_[i].x = static_cast<int>(positions_[i].x);
        positions_[i].y = static_cast<int>(positions_[i].y);
    }
}
