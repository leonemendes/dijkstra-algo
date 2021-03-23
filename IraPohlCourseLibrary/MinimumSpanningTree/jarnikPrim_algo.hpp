#ifndef JARNIKPRIM_ALGO_H
#define JARKIKPRIM_ALGO_H

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
    class MinSpanTree
    {
        private:
        Graph* g;
        Graph* tree;
        PriorityQueue* q;
        vector<int> v;
        int cost;

        public:
        MinSpanTree(Graph* g, Graph* tree = new Graph, PriorityQueue* q = new PriorityQueue, vector<int> v = {});

        Graph* treeGraph();

        ReturnStatus mst();

        ~MinSpanTree();

    };
}

#endif