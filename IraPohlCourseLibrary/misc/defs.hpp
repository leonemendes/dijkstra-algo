#ifndef DEFS_H
#define DEFS_H

// DEBUG LEVEL
const int DebugLevel = 0;
const int DebugLevelShortestPath = 0;

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