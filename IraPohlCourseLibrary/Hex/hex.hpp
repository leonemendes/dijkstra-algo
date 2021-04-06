#ifndef HEX_H
#define HEX_H

// Libraries
#include <utility>
#include <iomanip>
#include <exception>

// Library headerfile
#include "graph.hpp"

// Using from other namespaces
using std::pair;
using std::cerr;
using std::exception;
using std::setw;


// Important defines
enum class HexColor
{
    None = -1, 
    Blue = 1, 
    Red = 2,    
};


namespace ipc
{
    class Hex : public Graph
    {
        private:
        int size;

        bool isValidSquarePos(pair<int,int> pos);

        int validInd(int fromNode);

        public:
        Hex(int size);

        bool isValidSize(int size);

        pair<int, int> indexToSquarePos(int fromNode);

        int squarePosToIndex(int i, int j);

        int squarePosToIndex(pair<int,int> p);

        int squarePosToIndex(pair<char,int> p);

        ReturnStatus genBoard();

        vector<int> neigh(int fromNode);

        ReturnStatus placeStone(int pos, HexColor c);

        ReturnStatus placeStone(pair<char,int> p, HexColor c);

        void printBoard();

        ~Hex();

    };
}

#endif