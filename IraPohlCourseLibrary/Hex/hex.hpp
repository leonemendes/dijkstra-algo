#ifndef HEX_H
#define HEX_H

// Libraries
#include <utility>
#include <iomanip>

// Library headerfile
#include "graph.hpp"

// Using from other namespaces
using std::pair;
using std::setw;


// Important defines
enum class Color
{
    None = -1, 
    Red = 1, 
    Blue = 2,    
};


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

        ReturnStatus placeStone(int pos, Color c);

        ReturnStatus placeStone(int i, char j, Color c);

        void printBoard();

        ~Hex();

    };
}

#endif