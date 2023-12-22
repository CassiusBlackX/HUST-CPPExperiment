//
// Created by cassius on 20/10/23.
//

#include "../include/Point.h"

void Edge::addNext(Point *_to, double _distance) {
    next = new Edge;
    next->to = _to;
    next->distance = _distance;
}

Edge *&Edge::getNext() {
    return next;
}

Point *&Edge::setTo(Point *p)  {
    to = p;
    return to;
}

void Edge::setDistance(double dis) {
    distance = dis;
}

Point *&Edge::getTo() {
    return to;
}

double Edge::getDistance() const {
    return distance;
}

std::pair<int, int> Point::getPosition() {
    return std::make_pair(x,y);
}

int Point::getIndex() const {
    return index;
}

Edge *Point::getDirectEdgeFirst() {
    return directEdgeFirst;
}

Edge *Point::getEveryEdgeFirst() {
    return everyEdgeFirst;
}

void Point::setPosition(int _x, int _y) {
    this->x = _x;
    this->y = _y;
}

void Point::setIndex(int _index) {
    this->index = _index;
}

void Point::addDirectEdge(Point *p, double distance) {
    if(directEdgeFirst == nullptr){
        directEdgeFirst = new Edge;
        directEdgeFirst->setTo(p);
        directEdgeFirst->setDistance(distance);
        return;
    }
    Edge* e = directEdgeFirst;
    while(e->getNext()!= nullptr){
        e = e->getNext();
    }
    e->addNext(p, distance);
}

void Point::addEveryEdge(Point *p) {
    if(everyEdgeFirst == nullptr) {
        everyEdgeFirst = new Edge;
        everyEdgeFirst->setTo(p);
        return;
    }
    Edge* e = everyEdgeFirst;
    while(e->getNext() != nullptr){
        e = e->getNext();
    }
    e->addNext(p);
}

void Point::setLineType(int l) {
    lineType.push_back(l);
}

std::vector<int> Point::getLineType() {
    return lineType;
}

double calDistance(Point a, Point b) {
    return sqrt((a.getPosition().first - b.getPosition().first) * (a.getPosition().first - b.getPosition().first)
    + (a.getPosition().second - b.getPosition().second) * (a.getPosition().second - b.getPosition().second));
}
