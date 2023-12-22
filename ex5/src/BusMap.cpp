//
// Created by cassius on 20/10/23.
//

#include "BusMap.h"

//#define NEW_ATTEMPT
std::vector<std::vector<int>> matrixMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int m = A.size(); // A 的行数
    int n = A[0].size(); // A 的列数
    int p = B[0].size(); // B 的列数

    std::vector<std::vector<int>> result(m, std::vector<int>(p, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

void matrixAdd(std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B){
    for(int i=0;i<A.size();i++){
        for(int j=0;j<A[0].size();j++){
            A[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matClosure(std::vector<std::vector<int>>& m, int n){
    std::vector<std::vector<int>>tempMat(m);
    std::vector<std::vector<int>>APlusMat(m);
    for(int i=0;i<n-1;i++){
        tempMat = matrixMultiply(tempMat, m);
        matrixAdd(APlusMat,tempMat);
    }
    m = APlusMat;
}

BusMap::BusMap(const std::string &busStopsFile, const std::string &busLinesFile, const std::string &organizationsFile) {
    // initialize bus stops points
    std::ifstream fp(busStopsFile);
    if(!fp.is_open()){
        throw FileOpenError();
    }
    fp>>busStopsNum;
    busStops = new Point* [busStopsNum+1];
    path = new int[busStopsNum*2+5];
    for(int i=1,a,b;i<=busStopsNum;i++){
        fp>>a>>b;
        busStops[i] = new Point(a,b,i);
    }
    fp.close();
    // initialize bus lines
    fp.open(busLinesFile);
    if(!fp.is_open()){
        throw FileOpenError();
    }
    fp>>busLinesNum;
    lineMat.resize(busLinesNum+1,std::vector<int>(busLinesNum+1,0));
    busLines = new int* [busLinesNum+1];
    eachBusLineNum = new int [busLinesNum+1];
    for(int i=1;i<=busLinesNum;i++){
        fp>>eachBusLineNum[i];
        busLines[i] = new int [eachBusLineNum[i]+1];
    }
    for(int i=1;i<=busLinesNum;i++){
        for(int j=1;j<=eachBusLineNum[i];j++){
            fp>>busLines[i][j];
            busStops[busLines[i][j]]->setLineType(i);
        }
    }

    // initialize edges of points on bus lines
    for(int i=1;i<=busLinesNum;i++){
        for(int j=1;j<=eachBusLineNum[i];j++){
            for(int k=j+1;k<=eachBusLineNum[i];k++){
                busStops[busLines[i][j]]->addEveryEdge(busStops[busLines[i][k]]);
                busStops[busLines[i][k]]->addEveryEdge(busStops[busLines[i][j]]);
            }
        }
    }
    for(int i=1;i<=busLinesNum;i++){
        for(int j=1;j<=eachBusLineNum[i]-1;j++){
            double _dis = calDistance(*busStops[busLines[i][j]],*busStops[busLines[i][j+1]]);
            busStops[busLines[i][j]]->addDirectEdge(busStops[busLines[i][j+1]],_dis);
            busStops[busLines[i][j+1]]->addDirectEdge(busStops[busLines[i][j]],_dis);
        }
    }
    path[0] = 0;
    fp.close();

    // initialize the busStopsMat
    for(int i=1;i<busLinesNum;i++){
        for(int j=i+1;j<=busLinesNum;j++){
            for(int k=1;k<=eachBusLineNum[i];k++){
                for(int l=1;l<=eachBusLineNum[j];l++){
                    if(busLines[i][k] == busLines[j][l]){
                        lineMat[i][j]++;
                        lineMat[j][i]++;
                    }
                }
            }
        }
    }

    // initialize organizations
    fp.open(organizationsFile);
    if(!fp.is_open()){
        throw FileOpenError();
    }
    std::string _temp;
    while(fp>>_temp){
        orgNum++;
        orgNames[orgNum] = _temp;
        fp >> orgPos[orgNum].first;
        fp.get();
        fp >> orgPos[orgNum].second;
    }
    fp.close();
}

void BusMap::showStopsAndLines() {
//    std::cout<<"stops: "<<busStopsNum<<std::endl;
//    for(int i=1;i<=busStopsNum;i++){
//        std::cout<<busStops[i]->getPosition().first<<" "<<busStops[i]->getPosition().second<<std::endl;
//    }
//    std::cout<<"lines: "<<busLinesNum<<std::endl;
//    for(int i=1;i<=busLinesNum;i++){
//        std::cout<<eachBusLineNum[i]<<": ";
//        for(int j=0;j<=eachBusLineNum[i];j++){
//            std::cout<<busLines[i][j]<<" ";
//        }
//        std::cout<<std::endl;
//    }
    std::cout<<"map: "<<std::endl;
    for(int i=1;i<=busStopsNum;i++){
        std::cout<<busStops[i]->getIndex()<<" directEdge: ";
        Edge* p = busStops[i]->getDirectEdgeFirst();
        while(p != nullptr){
            std::cout<<p->getTo()->getIndex()<<": "<<p->getDistance()<<";";
            p = p->getNext();
        }
        std::cout<<std::endl;


        std::cout<<busStops[i]->getIndex()<<" everyEdge:";
        p = busStops[i]->getEveryEdgeFirst();
        while(p != nullptr){
            std::cout<<p->getTo()->getIndex()<<" ";
            p = p->getNext();
        }
        std::cout<<std::endl;
    }
//    for(int i=1;i<=lineMat.size();i++){
//        for(int j=1;j<lineMat[i].size();j++){
//            std::cout<<lineMat[i][j]<<" ";
//        }
//        std::cout<<std::endl;
//    }
}

int *BusMap::findNearestPath(int startIndex, int endIndex) {
    // 使用DJI算法，仅考虑了距离而未考虑公交线路行驶约束。
    auto* dis = new double[busStopsNum+1];
    for(int i=1;i<=busStopsNum;i++) {
        dis[i] = 1e9;
    }
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    // distance, index;
    dis[startIndex] = 0.0;
    pq.emplace(0, startIndex);
    path[startIndex] = 0;
    while(!pq.empty()){
        double curDis = pq.top().first;
        int curIndex = pq.top().second;
        pq.pop();
        if(dis[curIndex] != curDis){
            continue;
        }
        for(auto e=busStops[curIndex]->getDirectEdgeFirst(); e != nullptr; e=e->getNext()){
            int idx = e->getTo()->getIndex();
            if(dis[idx] > dis[curIndex] + e->getDistance()){
                dis[idx] = dis[curIndex] + e->getDistance();
                pq.emplace(dis[idx], idx);
                path[idx] = curIndex;
            }
        }
    }
    delete[] dis;
    return path;
}

#ifndef NEW_ATTEMPT
int *BusMap::findLeastStations(int startIndex, int endIndex) {
    int numStops = busStopsNum;

    // Create a new graph with virtual nodes
    int numNodes = 2 * numStops+1;
    std::vector<std::vector<std::pair<int, double>>> graph(numNodes);

    for (int i = 1; i <= numStops; i++) {
        // Add edges to the virtual nodes
        graph[i].emplace_back(i + numStops, 0.00001);
        graph[i + numStops].emplace_back(i, 0.00001);

        // Add direct edges based on the original bus stop distances
        for (auto edge = busStops[i]->getDirectEdgeFirst(); edge != nullptr; edge = edge->getNext()) {
            int to = edge->getTo()->getIndex();
            double distance = edge->getDistance();
            graph[i].emplace_back(to, distance);
            graph[to].emplace_back(i, distance);
        }
    }

    // Run Dijkstra's algorithm to find the shortest path
    std::vector<double> distance(numNodes, std::numeric_limits<double>::max());
    std::vector<int> previous(numNodes, -1);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    distance[startIndex] = 0.0;
    pq.emplace(0.0, startIndex);

    while (!pq.empty()) {
        double dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        if (dist > distance[current]) {
            continue;
        }

        for (const auto& neighbor : graph[current]) {
            int next = neighbor.first;
            double weight = neighbor.second;
            double new_dist = dist + weight;

            if (new_dist < distance[next]) {
                distance[next] = new_dist;
                previous[next] = current;
                pq.push({new_dist, next});
            }
        }
    }

    // Reconstruct the path with virtual nodes
    std::vector<int> pathNodes;
    int current = endIndex;
    while (current != -1) {
        pathNodes.push_back(current);
        current = previous[current];
    }

    // Reverse the path and store it in the path array
    int pathLength = static_cast<int>(pathNodes.size());
    for (int i = 0; i < pathLength; i++) {
        path[i] = pathNodes[pathLength - 1 - i];
    }

    int* pathCopy = findNearestPath(startIndex, endIndex);
    std::set<int> busLinesSet[busLinesNum+1];
    for(int i=1;i<=busLinesNum;i++){
        for(int j=1;j<=eachBusLineNum[i];j++){
            busLinesSet[i].insert(busLines[i][j]);
        }
    }
    // to create the connection between the bus stops and the bus line they belong to
    int pointIndex = endIndex;
    while(pathCopy[pointIndex]!=0){
        for(int i=1;i<=busLinesNum;i++){
            // to find at where can the bus stops from difference bus lines meet
            if(busLinesSet[i].count(pathCopy[pointIndex]) && busLinesSet[i].count(pointIndex)){
                int _start = 1, _end =1;
                while(busLines[i][_start] != pathCopy[pointIndex]){
                    _start++;
                }
                while(busLines[i][_end] != pointIndex){
                    _end++;
                }
                if(_start < _end){
                    for(int j=_end;j>_start;j--){
                        path[busLines[i][j]] = busLines[i][j-1];
                    }
                }
                else{
                    for(int j=_end;j<_start;j++){
                        path[busLines[i][j]] = busLines[i][j+1];
                    }
                }
            }
        }
        pointIndex = pathCopy[pointIndex];
    }
    path[startIndex] = 0;
//    delete[] pathCopy;
    return path;
}

#else
int* BusMap::findLeastStations(int startIndex, int endIndex) {
    int numStops = busStopsNum;

    // Create a new graph with virtual nodes
    int numNodes = 2 * numStops+1;
    std::vector<std::vector<std::pair<int, double>>> graph(numNodes);

    for (int i = 1; i <= numStops; i++) {
        // Add edges to the virtual nodes
        graph[i].push_back({i + numStops, 0.00001});
        graph[i + numStops].push_back({i, 0.00001});

        // Add direct edges based on the original bus stop distances
        for (auto edge = busStops[i]->getDirectEdgeFirst(); edge != nullptr; edge = edge->getNext()) {
            int to = edge->getTo()->getIndex();
            double distance = edge->getDistance();
            graph[i].push_back({to, distance});
            graph[to].push_back({i, distance});
        }
    }

    // Run Dijkstra's algorithm to find the shortest path
    std::vector<double> distance(numNodes, std::numeric_limits<double>::max());
    std::vector<int> previous(numNodes, -1);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    distance[startIndex] = 0.0;
    pq.push({0.0, startIndex});

    while (!pq.empty()) {
        double dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        if (dist > distance[current]) {
            continue;
        }

        for (const auto& neighbor : graph[current]) {
            int next = neighbor.first;
            double weight = neighbor.second;
            double new_dist = dist + weight;

            if (new_dist < distance[next]) {
                distance[next] = new_dist;
                previous[next] = current;
                pq.push({new_dist, next});
            }
        }
    }

    // Reconstruct the path with virtual nodes
    std::vector<int> pathNodes;
    int current = endIndex;
    while (current != -1) {
        pathNodes.push_back(current);
        current = previous[current];
    }

    // Reverse the path and store it in the path array
    int pathLength = static_cast<int>(pathNodes.size());
    for (int i = 0; i < pathLength; i++) {
        path[i] = pathNodes[pathLength - 1 - i];
    }

    return path;
}
#endif


int BusMap::getBusLinesNum() const {
    return busLinesNum;
}

int **BusMap::getBusLines() {
    return busLines;
}

int *BusMap::getEachBusLineNum() {
    return eachBusLineNum;
}

int BusMap::getBusStopsNum() const {
    return busStopsNum;
}

Point** BusMap::getBusStops() {
    return busStops;
}

int BusMap::getOrgNum() const {
    return orgNum;
}

std::string *BusMap::getOrgames() {
    return orgNames;
}

std::pair<int, int> *BusMap::getOrgPos() {
    return orgPos;
}

BusMap::~BusMap() {
    for(int i=1;i<=busLinesNum;i++){
        delete[] busLines[i];
        busLines[i] = nullptr;
    }
//    delete[] path;
    delete[] eachBusLineNum;
    delete[] busLines;
    delete[] busStops;
    eachBusLineNum = nullptr;
    busLines = nullptr;
    busStops = nullptr;
    path = nullptr;
}

