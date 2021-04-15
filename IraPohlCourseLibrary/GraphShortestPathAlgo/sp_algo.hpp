#ifndef SP_ALGO_H
#define SP_ALGO_H

// Libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <cstdlib>          // abs
#include <cmath>


// Library headerfile
#include "defs.hpp"
#include "priority_queue.hpp"
#include "hex.hpp"


using std::vector;
using std::cout;
using std::endl;
using std::find;
using std::unordered_map;
using std::pair;
using std::abs;
using std::sqrt;

namespace ipc
{
    namespace ShortestPath
    {
        // Auxiliar functions
        int heuristic(pair<int,int> fromNode, pair<int,int> toNode);

        int heuristic(int fromNode,int toNode, int squareSize);

        vector<int> buildPath(unordered_map<int, int> cameFrom, int fromNode, int toNode);


        // Main functions

        pair<vector<int>, int> dijkstra(ipc::Graph* g, int fromNode, int toNode);

        pair<vector<int>, int> dijkstraHex(ipc::Graph* g, int fromNode, int toNode, vector<int> validNodes);

        pair<vector<int>, int> aStarHex(ipc::Graph* g, int fromNode, int toNode, vector<int> validNodes);

        void printPath(vector<int> v);
    }
}


#endif