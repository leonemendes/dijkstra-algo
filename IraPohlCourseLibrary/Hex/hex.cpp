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

ReturnStatus ipc::Hex::placeStone(int pos, Color c)
{
    return this->setNodeValue(pos, static_cast<int> (c));
}

ReturnStatus ipc::Hex::placeStone(int i, char j, Color c)
{
    return this->setNodeValue(this->squarePosToIndex(static_cast<int>(i - 65), j), static_cast<int> (c));
}

void ipc::Hex::printBoard()
{
    for(int i = 0; i < this->size + 4; i++)
    {
        cout << string(i, ' ');
        for(int j = 0; j < this->size + 4; j++)
        {
            if(i == 0)
            {
                if(j <= 2 || j >= this->size + 3) cout << "  ";
                else cout << static_cast<char>(65 + (j - 3)) << " ";
            }
            else if(i == this->size + 3)
            {
                if(j <= 2 || j >= this->size + 3) cout << " ";
                else cout << static_cast<char>(65 + (j - 3)) << " ";
            }
            else if((j == 0 || j == this->size + 3) && i > 1 && i < this->size + 2) 
            {
                cout << i - 1 << " ";
                if(i -1 < 10) cout << " ";
            }
            else if(i == 1)
            {
                if(j <= 2 || j >= this->size + 3) cout << "  ";
                else cout << CoutColorStart + CoutColorBoldOn + CoutColorRed << "x " << CoutColorEnd;
            }
            else if(i == this->size + 2)
            {
                if(j < 2 || j >= this->size + 2) cout << "  ";
                else cout << CoutColorStart + CoutColorBoldOn + CoutColorRed << "x " << CoutColorEnd;
            }
            else if(j == 1 || j == this->size + 2) cout << CoutColorStart + CoutColorBoldOn + CoutColorBlue << "o " << CoutColorEnd;
            else
            {
                int val = this->getNodeValue(this->squarePosToIndex(i,j));
                switch (static_cast<Color> (val)) {
                    case Color::None: 
                        cout << "- ";
                        break;

                    case Color::Red: 
                        cout << CoutColorStart + CoutColorBoldOn + CoutColorRed << "x " << CoutColorEnd;;
                        break;

                    case Color::Blue: 
                        cout << CoutColorStart + CoutColorBoldOn + CoutColorBlue << "o " << CoutColorEnd;
                        break;
                    
                    default:
                        cout << "! ";
                }
            }
        }
        cout << endl; 
    }
}

// Destructor
ipc::Hex::~Hex(){};