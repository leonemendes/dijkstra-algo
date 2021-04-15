#ifndef DEFS_H
#define DEFS_H

#include "cout_cfg.hpp"

// DEBUG LEVEL
const int DebugLevel = 0;
const int DebugLevelGraph = 0;
const int DebugLevelShortestPath = 0;
const int DebugLevelMstJp = 0;
const int DebugLevelPq = 0;
const int DebugLevelHex = 0;

// TYPE DEIFINITIONS

enum ReturnStatus
{
    ReturnError = -1,
    ReturnSuccess = 0,
    ReturnWarning = 1,
    ReturnEndOfLoop = 2,
    ReturnNotFound = 3,
};

#endif