#include <iostream>
#include "Graph.cpp"
#include "Graph.h"

using namespace std;

int main() {
    int size;
    cout << "Enter the size of graph: ";
    cin >>size;
    Graph g(size);
    //g.dijisktra(1);
    cout << "The average shortest path in a graph is: " << g.getAvergeShortestPaths()<<endl;
    return 0;
}