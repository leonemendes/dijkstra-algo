#ifndef DIJKSTRA_ALGO_H
#define DIJKSTRA_ALGO_H

// Libraries
#include <iostream>
#include <vector>
#include <algorithm>


// Library headerfile
#include "defs.hpp"
#include "priority_queue.hpp"


using std::vector;
using std::cout;
using std::endl;
using std::find;

namespace ipc
{
    class ShortestPath
    {
        private:
        Graph* g;
        bool pathFound;
        int cost;

        ReturnStatus recursivePath(PriorityQueue* q, PriorityQueue* tmpQ, int fromNode, int toNode, int cost, int lastNode, vector<int> specificCost, bool firstNode = true);

        public:
        vector<int> v;
        ShortestPath(Graph* g, vector<int> v = {});

        ReturnStatus path(int fromNode, int toNode, vector<int> specificCost = {-1});

        void printPath();

        int pathCost();

        ~ShortestPath();
    };
}


#endif