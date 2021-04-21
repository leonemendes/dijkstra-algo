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
    int v = 0, fromV, cost;

    PriorityQueue* tmpQueue = new PriorityQueue;
    detail::Node<detail::vertice>* head;


    neigh = g->neighbours(v);
    
    while (!neigh.empty())
    {

        for (auto n: neigh)
        {
            if (DebugLevelMstJp > 1) cout << "From node: " << v << " To node: " << n << endl;
            if (!q->contains(n)) tmpQueue->insert(n, v, g->cost(v, n));

        }
        head = tmpQueue->minPriority();
        v = head->data->vertice;
        fromV = head->data->fromVertice;
        cost = head->data->value;

        q->insert(v, fromV, cost);

        if(q->size() == g->v()) break;
        else neigh = g->neighbours(v);
    }

    if(q->size() != g->v())
    {
        if (DebugLevelMstJp > 1) cout << "ERROR: Disconnected tree." << endl;
        return ReturnError;
    }

    this->tree->init(this->g->v(), g->isDirectedFlag());

    this->q->fromQueueToType(this->tree);

    return ReturnSuccess;
}

// Destructor
ipc::MinSpanTree::~MinSpanTree(){}