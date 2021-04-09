#include "prob_functions.hpp"

// ProbFunctions namespace functions ----------------------
float ipc::ProbFunctions::randNum(float lowerBound, float upperBound)
{
    srand(time(0));
    return lowerBound + static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/(upperBound - lowerBound)));
}

float ipc::ProbFunctions::prob()
{
    return randNum(0.0, 1.0);
}