#include "montecarlo_graph.hpp"

// MonteCarloGraph Class functions ----------------------

// Private ----------------------
float ipc::MonteCarloGraph::prob(float lowerBound, float upperBound)
{
    return lowerBound + static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/(upperBound - lowerBound)));
}

ReturnStatus ipc::MonteCarloGraph::genMonteCarloGraph()
{
    int v = this->v();
    int cost = 1;

    srand(time(0));


    for(int fromNode = 0; fromNode < v; fromNode++)
    {
        for(int toNode = 0; toNode < v; toNode++)
        {
            if(fromNode != toNode && this->isAdjacent(fromNode, toNode) == nullptr && ipc::MonteCarloGraph::prob() < this->density)
            {
                if (this->randCost) cost = static_cast<int> (prob(1,10));
                this->addEdge(fromNode, toNode, cost);
            }
        }
    }
    
    return ReturnSuccess;
}

// Public ----------------------

// Constructor
ipc::MonteCarloGraph::MonteCarloGraph(int numOfVertices, float density, bool isDirected, bool randCost, int range)
    : ipc::Graph(numOfVertices, isDirected), density(density), isDirected(isDirected), randCost(randCost), range(range)
{
    ipc::MonteCarloGraph::genMonteCarloGraph();
}

// Destructor
ipc::MonteCarloGraph::~MonteCarloGraph(){};