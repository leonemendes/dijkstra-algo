#include "jarnikPrim_algo.hpp"

// Dijkstra's Algorithm Class functions ----------------------

// Private ----------------------


// Public ----------------------

// Constructor 
ipc::MinSpanTree::MinSpanTree(Graph* g, Graph* tree, PriorityQueue* q, vector<int> v):g(g), tree(tree), q(q), v(v), cost(0){ ipc::MinSpanTree::mst(); }

ipc::Graph* ipc::MinSpanTree::treeGraph(){ return this->tree; }

ReturnStatus ipc::MinSpanTree::mst()
{
    vector<int> neigh;
    
    for(int v = 0; v < g->v(); v++)
    {
        vector<int> neigh = g->neighbors(v);
        if(!neigh.empty())
        {
            if (DebugLevelMstJp > 1) cout << "From node: " << v << " To node: ";

            for(auto n: neigh)
            {
                if (DebugLevelMstJp > 1) cout << n << " ";
                q->insert(n, v, g->getEdgeValue(v, n));
            }
            cout << endl;
        }
    }

    this->tree->init(this->g->v());

    this->q->fromQueueToType(this->tree);

    return ReturnSuccess;
}

// Destructor
ipc::MinSpanTree::~MinSpanTree(){}