//
// Created by cassius on 20/10/23.
//

#ifndef EX5_BUSMAP_H
#define EX5_BUSMAP_H
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <exception>
#include "Point.h"
#include <vector>

class BusMap {
private:
    int busStopsNum = 0, busLinesNum = 0, orgNum = 0;
    int* eachBusLineNum = nullptr;
    int ** busLines = nullptr;
    Point** busStops = nullptr;
    std::string orgNames[100];
    std::pair<int, int> orgPos[100];
    int* path = nullptr;
    std::vector<std::vector<int>> lineMat;
public:
    BusMap(const std::string& busStopsFile, const std::string& busLinesFile, const std::string& organizationsFile);
    void showStopsAndLines();
    int* findNearestPath(int startIndex, int endIndex);
    int* findLeastStations(int startIndex, int endIndex);
    [[nodiscard]] int getBusLinesNum() const;
    int** getBusLines();
    int* getEachBusLineNum();
    [[nodiscard]] int getBusStopsNum() const;
    Point** getBusStops();
    [[nodiscard]] int getOrgNum() const;
    std::string* getOrgames();
    std::pair<int, int>* getOrgPos();
    ~BusMap();
};
class FileOpenError : public std::exception{
public:
    [[nodiscard]] const char * what() const noexcept override{
        return "File Open Error!";
    }
};

#endif //EX5_BUSMAP_H
