//
// Created by bar44 on 22-Dec-18.
//
#ifndef DIJKSTERA_GRAPH_H
#define DIJKSTERA_GRAPH_H

static const int MAX_WEIHGT_EDGE = 100;
static const int MIN_WEIHGT_EDGE = 5;


#include <vector>
#include <random>
#include <string>
#include "limits"
#include <unordered_set>
using namespace std;

/**
 * the class is making a graph and checks for shortest paths
 */
class Graph{
private:
    const int SIZE;
    vector<vector<bool>> graph;
    vector<vector<int>> weightsEdges;
    double averageShrtestPaths;

    /**
     *make random probability for insert edge between to vertexes
     * @return double number between 0 to 1
     */
    double getRandomNumber();
    /**
     * prepare a new graph with SIZE nodes
     */
    void makeGraph();
    /**
     * checks if the graph is correct and connected
     * @return
     */
    bool isGraphConnected();
    /**
     * scan the graph in DFS algoritm
     * @param NodeIndex start node
     * @param markedNodes vector of visited vertexes
     */
    void DFS(const int NodeIndex,vector<bool>& markedNodes);
    /**
     * reset all vector fields in the class in a case of wrong graph
     */
    void resetVectorsClass();
    /**
     * calculates the avergae shortest paths of the input root to all vertexes in graph
     * @param root input root
     * @return average shortest paths from the root to all vertexes.
     */
    double averageDijisktra(const int root);
    /**
     * detect the minimum distance in the current iteration in dijikstera algoritm run
     * @param distances vector of all current distances from root
     * @param visitedNodes all nodes that visited already
     * @return the index of the minimum vertex
     */
    int getMinimumVertex(const vector<int> &distances, const unordered_set<int> &visitedNodes) const;

public:
    explicit Graph(const int size=50):SIZE(size),graph(size,vector<bool>(size, false)),
        weightsEdges(size,vector<int>(size,0)) {
        makeGraph();
        calcAverageShortestPaths();
    }
    /**
     * algroim to find the best paths from the root to all vertexes in graph
     * @param root index of the wanted root
     */
    void dijisktra(const int root);

    /**
     * prints all shortest paths from root to all vertexes in graph
     * @param root input of the root/vertex to check
     * @param distances vector of all distances from the root
     */
    void shortestPathsPrinter(const int root, const vector<int> &distances) const;
    /**
     * calculate the average shorts paths in the graph
     */
    void calcAverageShortestPaths();
    /**
     * @return the value of the average shortest paths in the graph
     */
    double getAvergeShortestPaths() const { return this->averageShrtestPaths;};
};


#endif //DIJKSTERA_GRAPH_H
