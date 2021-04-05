#include "hex.hpp"

// HEX Class functions ----------------------

// Private ----------------------
pair<int, int> ipc::Hex::indexToSquarePos(int fromNode)
{
    pair<int, int> pos;

    pos.first = fromNode / this->size;
    pos.second = fromNode % this->size;

    return (ipc::Hex::isValidSquarePos(pos)) ? pos : pair<int,int>(-1,-1);
}

bool ipc::Hex::isValidSquarePos(pair<int,int> pos)
{
    return((pos.first >= 0 && pos.first < this->size) && (pos.second >= 0 && pos.second < this->size)) ? true : false;
}

int ipc::Hex::validInd(int fromNode)
{
    return (this->isValid(fromNode)) ? fromNode : ReturnError;
}

int ipc::Hex::squarePosToIndex(int i, int j)
{
    return i * this->size + j;
}

int ipc::Hex::squarePosToIndex(pair<int,int> p)
{
    return p.first * this->size + p.second;
}

// Public ----------------------

// Constructor
ipc::Hex::Hex(int size):ipc::Graph(size * size, false), size(size){ ipc::Hex::genBoard(); }

ReturnStatus ipc::Hex::genBoard()
{
    

    for (int fromNode = 0; fromNode < this->v(); fromNode++)
    {
        vector<int> n = ipc::Hex::neigh(fromNode);

        for(auto toNode : n)
        {
            if(toNode != ReturnError) this->addEdge(fromNode, toNode);

        }
    }
    return ReturnSuccess;
}

vector<int> ipc::Hex::neigh(int fromNode)
{
    if(!this->isValid(fromNode)) return {};
    vector<int> n;
    pair<int,int> pos = ipc::Hex::indexToSquarePos(fromNode), adjPos;
    int index;

    if(DebugLevelHex > 1) cout << "Central node: " << fromNode << " Pos: " << "(" << pos.first << ", " << pos.second << ")" << endl;

    adjPos.first = pos.first - 1;
    adjPos.second = pos.second;
    index = ipc::Hex::squarePosToIndex(adjPos);
    
    if(DebugLevelHex > 1) cout << "Pos: (" << adjPos.first << ", " << adjPos.second << "), Index: " << index << endl;
    if(ipc::Hex::isValidSquarePos(adjPos)) n.push_back(index);

    adjPos.first = pos.first - 1;
    adjPos.second = pos.second + 1;
    index = ipc::Hex::squarePosToIndex(adjPos);
    
    if(DebugLevelHex > 1) cout << "Pos: (" << adjPos.first << ", " << adjPos.second << "), Index: " << index << endl;
    if(ipc::Hex::isValidSquarePos(adjPos)) n.push_back(index);

    adjPos.first = pos.first;
    adjPos.second = pos.second - 1;
    index = ipc::Hex::squarePosToIndex(adjPos);
    
    if(DebugLevelHex > 1) cout << "Pos: (" << adjPos.first << ", " << adjPos.second << "), Index: " << index << endl;
    if(ipc::Hex::isValidSquarePos(adjPos)) n.push_back(index);

    adjPos.first = pos.first;
    adjPos.second = pos.second + 1;
    index = ipc::Hex::squarePosToIndex(adjPos);
    
    if(DebugLevelHex > 1) cout << "Pos: (" << adjPos.first << ", " << adjPos.second << "), Index: " << index << endl;
    if(ipc::Hex::isValidSquarePos(adjPos)) n.push_back(index);

    adjPos.first = pos.first + 1;
    adjPos.second = pos.second - 1;
    index = ipc::Hex::squarePosToIndex(adjPos);
    
    if(DebugLevelHex > 1) cout << "Pos: (" << adjPos.first << ", " << adjPos.second << "), Index: " << index << endl;
    if(ipc::Hex::isValidSquarePos(adjPos)) n.push_back(index);

    adjPos.first = pos.first + 1;
    adjPos.second = pos.second;
    index = ipc::Hex::squarePosToIndex(adjPos);
    
    if(DebugLevelHex > 1) cout << "Pos: (" << adjPos.first << ", " << adjPos.second << "), Index: " << index << endl;
    if(ipc::Hex::isValidSquarePos(adjPos)) n.push_back(index);

    return n;
}

// Destructor
ipc::Hex::~Hex(){};