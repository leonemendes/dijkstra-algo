#ifndef PROB_FUNCTIONS_H
#define PROB_FUNCTIONS_H

// Libraries
#include <cstdlib>
#include <ctime>
#include <algorithm>            // random_shuffle

// Using from other namespaces
using std::srand;
using std::rand;
using std::time;
using std::random_shuffle;

namespace ipc
{
    namespace ProbFunctions
    {
        float randNum(float lowerBound, float upperBound);
        float prob();
    }
}

#endif