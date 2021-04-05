#ifndef HEX_H
#define HEX_H

// Libraries
#include <utility>

// Library headerfile
#include "graph.hpp"

// Using from other namespaces
using std::pair;


namespace ipc
{
    class Hex : public Graph
    {
        private:
        int size;

        pair<int, int> indexToSquarePos(int fromNode);

        bool isValidSquarePos(pair<int,int> pos);

        int validInd(int fromNode);

        int squarePosToIndex(int i, int j);

        int squarePosToIndex(pair<int,int> p);

        public:
        Hex(int size);

        ReturnStatus genBoard();

        vector<int> neigh(int fromNode);

        ~Hex();

    };
}

#endif