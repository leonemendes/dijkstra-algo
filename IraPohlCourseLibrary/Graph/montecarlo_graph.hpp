#ifndef MONTECARLO_GRAPH_H
#define MONTECARLO_GRAPH_H

#include <cstdlib>
#include <ctime>
#include "graph.hpp"

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

        float prob(float lowerBound = 0.0, float upperBound = 1.0);

        public:
        MonteCarloGraph(int numOfVertices, float density, bool isDirected = true, bool randCost = false, int range = 0);

        ~MonteCarloGraph();

    };
}

#endif