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

        ReturnStatus genMonteCarloGraph();

        float prob();

        public:
        MonteCarloGraph(int numOfVertices, float density);

        ~MonteCarloGraph();

    };
}

#endif