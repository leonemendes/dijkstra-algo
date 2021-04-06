#include "hex.hpp"

// HEX Class functions ----------------------

// Private ----------------------
bool ipc::Hex::isValidSquarePos(pair<int,int> pos)
{
    return((pos.first >= 0 && pos.first < this->size) && (pos.second >= 0 && pos.second < this->size)) ? true : false;
}

int ipc::Hex::validInd(int fromNode)
{
    return (this->isValid(fromNode)) ? fromNode : ReturnError;
}

// Public ----------------------

// Constructor
ipc::Hex::Hex(int size):ipc::Graph(size * size, false), size(size){ ipc::Hex::genBoard(); }

bool ipc::Hex::isValidSize(int size)
{
    return (size >= 3 && size <= 26) ? true : false;
}

pair<int, int> ipc::Hex::indexToSquarePos(int fromNode)
{
    pair<int, int> pos;

    pos.first = fromNode / this->size;
    pos.second = fromNode % this->size;

    return (ipc::Hex::isValidSquarePos(pos)) ? pos : pair<int,int>(-1,-1);
}

int ipc::Hex::squarePosToIndex(int i, int j)
{
    return i * this->size + j;
}

int ipc::Hex::squarePosToIndex(pair<int,int> p)
{
    return p.first * this->size + p.second;
}

int ipc::Hex::squarePosToIndex(pair<char,int> p)
{
    return p.second * this->size + static_cast<int>(p.first - 65);
}

ReturnStatus ipc::Hex::genBoard()
{
    try
    {
        if(ipc::Hex::isValidSize(this->size))
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
        else throw this->size;;
    }
    catch(int x)
    {
        cerr << CoutColorStart + CoutColorBoldOn + CoutColorRed << "ERROR: Size " << x << " is wrong! It must be between 3 and 26." << CoutColorEnd << endl;
        this->size = -1;
        return ReturnError;
    }
}

vector<int> ipc::Hex::neigh(int fromNode)
{
    if(!ipc::Hex::isValidSize(this->size)) return {};

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

ReturnStatus ipc::Hex::placeStone(int pos, HexColor c)
{
    return this->setNodeValue(pos, static_cast<int> (c));
}

ReturnStatus ipc::Hex::placeStone(pair<char,int> p, HexColor c)
{
    if(!ipc::Hex::isValidSize(this->size)) return ReturnError;
    if(static_cast<HexColor>(this->getNodeValue(this->squarePosToIndex(p))) != HexColor::None) return ReturnError;
    return this->setNodeValue(this->squarePosToIndex(p), static_cast<int> (c));
}

void ipc::Hex::printBoard()
{
    if(!ipc::Hex::isValidSize(this->size)) return;

    for(int i = 0; i < this->size + 4; i++)
    {
        cout << string(i, ' ');
        for(int j = 0; j < this->size + 4; j++)
        {
            if(i == 0)
            {
                if(j <= 2 || j >= this->size + 3) cout << "   ";
                else cout << static_cast<char>(65 + (j - 3)) << "   ";
            }
            else if(i == this->size + 3)
            {
                if(j == 0) cout << string(i - 5, ' ');
                if(j <= 2 || j >= this->size + 3) cout << "  ";
                else cout << static_cast<char>(65 + (j - 3)) << "   ";
            }
            else if((j == 0 || j == this->size + 3) && i > 1 && i < this->size + 2) 
            {
                if(j == 0) cout << string(i, ' ');
                cout << i - 2 << " ";
                if(i - 2 < 10) cout << " ";
            }
            else if(i == 1)
            {
                if(j == 0) cout << string(i + 1, ' ');
                if(j <= 2 || j >= this->size + 3) cout << "  ";
                else cout << CoutColorStart + CoutColorBoldOn + CoutColorRed << "*   " << CoutColorEnd;
            }
            else if(i == this->size + 2)
            {
                if(j == 0) cout << string(i - 1, ' ');
                if(j < 2 || j >= this->size + 2) cout << "  ";
                else cout << CoutColorStart + CoutColorBoldOn + CoutColorRed << "*   " << CoutColorEnd;
            }
            else if(j == 1 || j == this->size + 2) cout << CoutColorStart + CoutColorBoldOn + CoutColorBlue << "* " << CoutColorEnd;
            else
            {
                int line = i -2, col = j - 2;
                int val = this->getNodeValue(this->squarePosToIndex(line,col));
                switch (static_cast<HexColor> (val)) {
                    case HexColor::None: 
                        cout << ". ";
                        break;

                    case HexColor::Red: 
                        cout << CoutColorStart + CoutColorBoldOn + CoutColorRed << "x " << CoutColorEnd;;
                        break;

                    case HexColor::Blue: 
                        cout << CoutColorStart + CoutColorBoldOn + CoutColorBlue << "o " << CoutColorEnd;
                        break;
                    
                    default:
                        cout << "! ";
                }
                if(j < this->size + 1) cout << "- ";
            }
        }
        cout << endl; 
        if(i > 1 && i < this->size + 1)
        {
            int k = 0;
            cout << string(i + 6, ' ');
            cout << string(i, ' ');
            while(k < this->size - 1)
            {
                cout << "\\ / ";
                k++;
            }
            cout << "\\" << endl;
        }
    }
}

// Destructor
ipc::Hex::~Hex(){ if(DebugLevelHex > 0) cout << "HEX Class destructor called." << endl; };