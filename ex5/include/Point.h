//
// Created by cassius on 20/10/23.
//

#ifndef EX5_POINT_H
#define EX5_POINT_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
class Point;

class Edge {
private:
    Point * to = nullptr;
    Edge * next = nullptr;
    double distance = 0.0;
public:
    explicit Edge() : to(nullptr), next(nullptr), distance(0.0) {}
    void addNext(Point* _to, double _distance=1.0);
    Edge*& getNext();
    Point*& setTo(Point* p);
    Point*& getTo();
    void setDistance(double dis);
    [[nodiscard]] double getDistance() const;
};

class Point {
private:
    int x = 0, y = 0;
    int index = 0;
    std::vector<int> lineType;
    Edge* directEdgeFirst = nullptr;
    Edge* everyEdgeFirst = nullptr;
public:
    Point()= default;
    Point(int x, int y, int index):x(x),y(y), index(index) {
        // just reserve a small space so that we will not be too space consuming
        lineType.reserve(3);
    }
    std::pair<int, int> getPosition();
    [[nodiscard]] int getIndex() const;
    Edge* getDirectEdgeFirst();
    Edge* getEveryEdgeFirst();
    void setPosition(int _x, int _y);
    void setIndex(int _index);
    void addDirectEdge(Point* p, double distance);
    void addEveryEdge(Point* p);
    void setLineType(int l);
    std::vector<int> getLineType();
};

double calDistance(Point a, Point b);

#endif //EX5_POINT_H
