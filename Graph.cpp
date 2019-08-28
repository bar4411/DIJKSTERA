//
// Created by bar44 on 22-Dec-18.
//
#include <iostream>
#include <algorithm>
#include "Graph.h"
using namespace std;


void Graph::makeGraph() {

    srand(time(NULL));//seeds the random weights
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = i; j <SIZE ; ++j) {
            if (i==j){
                graph[i][j]= false;
            } else if (getRandomNumber()<0.2){
                graph[i][j]= true;
                graph[j][i]=true;
                weightsEdges[j][i]=weightsEdges[i][j]= rand()%(MAX_WEIHGT_EDGE -
                        MIN_WEIHGT_EDGE + 1) + MIN_WEIHGT_EDGE;

            }
        }
    }
    if (!isGraphConnected()) {
        resetVectorsClass();
        makeGraph();
    }
}


double Graph::getRandomNumber() {
    return  ((double) rand() / (double) (RAND_MAX));
}

bool Graph::isGraphConnected() {
    vector<bool > markedNodes(SIZE, false);
    markedNodes[0]=true;
    DFS(0,markedNodes);
    for (int i = 0; i < SIZE; ++i) {
        if (!markedNodes[i]) return false;
    }
    return true;
}

void Graph::DFS(const int NodeIndex,vector<bool>& markedNodes){
    markedNodes[NodeIndex]= true;
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            if (graph[i][j] && !markedNodes[j]){
                DFS(j,markedNodes);
            }
        }
    }
}

void Graph::dijisktra(const int root) {
    vector<int> distances(SIZE,numeric_limits<int>::max()); //enter Max int in every cell of vector
    unordered_set<int> visitedNodes;
    distances[root]=0;
    int minV;
    while (visitedNodes.size()!=SIZE){
        minV = getMinimumVertex(distances, visitedNodes);
        visitedNodes.insert(minV);
        for (int i = 0; i <SIZE ; ++i) {
            if (graph[minV][i]){
                if (distances[i]>distances[minV]+weightsEdges[minV][i]){
                    distances[i]=distances[minV]+weightsEdges[minV][i];
                }
            }
        }
    }
    shortestPathsPrinter(root, distances);
}

void Graph::shortestPathsPrinter(const int root, const vector<int> &distances) const {
    cout << "For vertex Number: " << root << ", All shortest paths are: " << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << "to vertex " << i<< " the shortest distance is: " << distances[i]<<"\n";
    }
}

int Graph::getMinimumVertex(const vector<int> &distances, const unordered_set<int> &visitedNodes) const {
    int minV;
    int minDistance=numeric_limits<int>::max();
    for (int j = 0; j < SIZE; ++j) {
            if (minDistance>distances[j] && visitedNodes.count(j)==0){
                minV=j;
            }
        }
    return minV;
}

void Graph::resetVectorsClass() {
    for (auto& sub : graph) {
        std::fill(sub.begin(), sub.end(), false);
    }
    for (auto& sub : weightsEdges) {
        std::fill(sub.begin(), sub.end(), 0);
    }
}

void Graph::calcAverageShortestPaths() {
    double averagePaths=0;
    for (int i = 0; i <SIZE ; ++i) {
        averagePaths+=averageDijisktra(i);
    }
    this->averageShrtestPaths=averagePaths/SIZE;
}

double Graph::averageDijisktra(const int root) {
    vector<int> distances(SIZE,numeric_limits<int>::max()); //enter Max int in every cell of vector
    unordered_set<int> visitedNodes;
    distances[root]=0;
    int minV;
    while (visitedNodes.size()!=SIZE){
        minV = getMinimumVertex(distances, visitedNodes);
        visitedNodes.insert(minV);
        for (int i = 0; i <SIZE ; ++i) {
            if (graph[minV][i]){
                if (distances[i]>distances[minV]+weightsEdges[minV][i]){
                    distances[i]=distances[minV]+weightsEdges[minV][i];
                }
            }
        }
    }

    return 1.0*accumulate(distances.begin(),distances.end(),0L)/SIZE;

}
