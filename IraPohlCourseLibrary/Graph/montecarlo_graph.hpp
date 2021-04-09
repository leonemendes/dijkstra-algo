#ifndef MONTECARLO_GRAPH_H
#define MONTECARLO_GRAPH_H

// Libraries
#include <cstdlib>
#include <ctime>

// Library headerfile
#include "graph.hpp"
#include "prob_functions.hpp"

// Using from other namespaces
using namespace ipc::ProbFunctions;
using std::srand;
using std::rand;
using std::time;

namespace ipc
{
    class MonteCarloGraph : public Graph
    {
        private:
        float density;
        bool isDirected, randCost;
        int range;

        ReturnStatus genMonteCarloGraph();

        public:
        MonteCarloGraph(int numOfVertices, float density, bool isDirected = true, bool randCost = false, int range = 0);

        ~MonteCarloGraph();

    };
}

#endif