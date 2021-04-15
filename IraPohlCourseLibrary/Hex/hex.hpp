#ifndef HEX_H
#define HEX_H

// Libraries
#include <utility>
#include <iomanip>
#include <exception>
#include <string>
#include <cstdlib>          // abs



// Library headerfile
#include "graph.hpp"
#include "sp_algo.hpp"
#include "prob_functions.hpp"

// Using from other namespaces
using std::pair;
using std::cerr;
using std::exception;
using std::setw;
using std::string;
using std::abs;



namespace ipc
{
    namespace detail
    {
        enum class HexColor
        {
            None = -1,
            Null = 0,
            Empty = 1,  
            Blue = 2, 
            Red = 3,   
        };

        enum class BoardSide
        {
            None = -1,
            Top = 0,
            Right = 1,
            Bottom = 2,
            Left = 3,
        };

        enum class PcLevel
        {
            Null = -1,
            Dumb = 0,
            Easy = 1,
        };

        class Player
        {
            public:
            HexColor color;
            bool isPlayerPc;
            PcLevel level;
            vector<int> movements;
            BoardSide touched;
        };

    }

    class Hex : public Graph
    {
        private:
        int size;
        detail::HexColor winner;

        bool isValidSquarePos(pair<int,int> pos);

        int validInd(int fromNode);

        void initPlayers();

        pair<vector<int>,int> minPathToSide(int fromNode, detail::BoardSide side = detail::BoardSide::None, vector<int> colors = {});

        detail::BoardSide closestSide(int fromNode, detail::HexColor color = detail::HexColor::None);

        detail::BoardSide opositeSide(detail::BoardSide side);

        detail::HexColor nodeColor(int fromNode);

        vector<int> boardSide(detail::BoardSide side);

        detail::Player* playerSelect(detail::HexColor p);

        bool isPlayerSide(detail::HexColor p, detail::BoardSide side);

        detail::BoardSide nodeSide(int fromNode);

        public:
        bool endGame;
        detail::Player* player;

        Hex(int size);

        bool isValidSize(int size);

        pair<int, int> indexToSquarePos(int fromNode);

        int squarePosToIndex(int i, int j);

        int squarePosToIndex(pair<int,int> p);

        int squarePosToIndex(pair<char,int> p);

        int heuristic(int fromNode, int toNode);

        ReturnStatus genBoard();

        vector<int> neigh(int fromNode);

        ReturnStatus placeStone(int pos, detail::HexColor c);

        ReturnStatus placeStone(pair<char,int> p, detail::HexColor c);

        ReturnStatus placeStone(pair<int,int> p, detail::HexColor c);

        ReturnStatus minPath(int fromNode, int toNode, vector<int> colors = {});

        ReturnStatus smartMove(detail::HexColor player, detail::PcLevel level = detail::PcLevel::Null);

        vector<int> isWinner(int fromNode, vector<int> colors = {static_cast<int>(ipc::detail::HexColor::Null)});

        void gameReport();

        void printPath(vector<int> v);

        void printBoard();

        ~Hex();

    };
}

#endif