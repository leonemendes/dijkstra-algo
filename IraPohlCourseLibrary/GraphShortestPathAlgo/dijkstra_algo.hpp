#ifndef DIJKSTRA_ALGO_H
#define DIJKSTRA_ALGO_H

// Libraries
#include <iostream>
#include <vector>

// Library headerfile
#include "defs.hpp"
#include "priority_queue.hpp"


using std::vector;
using std::cout;
using std::endl;

namespace ipc
{
    class ShortestPath
    {
        private:
        Graph* g;
        PriorityQueue* q;
        vector<int> v;
        int cost;

        ReturnStatus recursivePath(int fromNode, int toNode, int cost, int lastNode, bool firstNode = true);

        public:
        ShortestPath(Graph* g, PriorityQueue* q = new PriorityQueue, vector<int> v = {});

        ReturnStatus path(int fromNode, int toNode);

        void printQueue();

        void printPath();

        int pathCost();

        ~ShortestPath();
    };
}


#endif