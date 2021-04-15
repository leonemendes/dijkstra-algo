#ifndef DIJKSTRA_ALGO_H
#define DIJKSTRA_ALGO_H

// Libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>


// Library headerfile
#include "defs.hpp"
#include "priority_queue.hpp"


using std::vector;
using std::cout;
using std::endl;
using std::find;
using std::unordered_map;
using std::pair;

namespace ipc
{
    namespace ShortestPath
    {
        vector<int> buildPath(unordered_map<int, int> cameFrom, int fromNode, int toNode);

        pair<vector<int>, int> dijkstra(ipc::Graph* g, int fromNode, int toNode);

        pair<vector<int>, int> dijkstraHex(ipc::Graph* g, int fromNode, int toNode, vector<int> validNodes);

        void printPath(vector<int> v);
    }
}


#endif