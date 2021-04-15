#include <iostream>
#include <chrono>
#include <limits>
#include <utility>

#include "main.hpp"

// From namespace
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::pair;

// Calling namespace library functions
using namespace std::chrono;
using namespace ipc::ShortestPath;

using ipc::Graph;
using ipc::MonteCarloGraph;
using ipc::MinSpanTree;
using ipc::Hex;

int main()
{
    Graph g(10);

    g.addEdge(0,1,4);
    g.addEdge(0,2,3);
    g.addEdge(0,4,7);
    g.addEdge(0,6,1);

    g.addEdge(1,3,1);

    g.addEdge(2,4,4);
    g.addEdge(2,0,3);

    g.addEdge(3,5,1);

    g.addEdge(4,5,1);
    g.addEdge(4,6,5);
    g.addEdge(4,8,3);

    g.addEdge(5,7,2);
    g.addEdge(5,8,4);

    g.addEdge(6,9,1);

    g.addEdge(7,5,2);
    g.addEdge(7,8,3);

    g.addEdge(8,6,5);

    g.print();

    pair<vector<int>, int> dijkstraResult;
    dijkstraResult = dijkstra(&g, 0,8);

    printPath(dijkstraResult.first);

    return 0;
}
