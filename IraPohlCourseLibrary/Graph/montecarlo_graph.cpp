#include "montecarlo_graph.hpp"

// MonteCarloGraph Class functions ----------------------

// Private ----------------------
float ipc::MonteCarloGraph::prob()
{
    return static_cast <float> (rand())/ static_cast <float> (RAND_MAX);
}

ReturnStatus ipc::MonteCarloGraph::genMonteCarloGraph()
{
    int v = this->v();

    srand(time(0));


    for(int fromNode = 0; fromNode < v; fromNode++)
    {
        for(int toNode = fromNode; toNode < v; toNode++)
        {
            if(fromNode != toNode && this->isAdjacent(fromNode, toNode) == nullptr && ipc::MonteCarloGraph::prob() < this->density) this->addEdge(fromNode, toNode);
        }
    }
    
    return ReturnSuccess;
}

// Public ----------------------
// Constructor
ipc::MonteCarloGraph::MonteCarloGraph(int numOfVertices, float density) : ipc::Graph(numOfVertices), density(density)
{
    ipc::MonteCarloGraph::genMonteCarloGraph();
}

// Destructor
ipc::MonteCarloGraph::~MonteCarloGraph(){};