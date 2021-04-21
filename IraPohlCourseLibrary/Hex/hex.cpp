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

void ipc::Hex::initPlayers()
{
    this->player = new ipc::detail::Player[2];
    this->player[0] = {.color = ipc::detail::HexColor::Blue, .isPlayerPc = false,
     .level = ipc::detail::PcLevel::Null, .movements = {}, .touched = ::ipc::detail::BoardSide::None};
    this->player[1] = {.color = ipc::detail::HexColor::Red, .isPlayerPc = false,
     .level = ipc::detail::PcLevel::Null, .movements = {}, .touched = ::ipc::detail::BoardSide::None};
}

pair<vector<int>,int> ipc::Hex::minPathToSide(int fromNode, ipc::detail::BoardSide side, vector<int> colors, bool countPaths)
{

    pair<vector<int>,int> pathNCost;
    pathNCost.first = {};
    pathNCost.second = 10000;                   // just a big number
    int pathCounter = 0;
    ipc::detail::HexColor avoid = (this->nodeColor(fromNode) == ipc::detail::HexColor::Blue) ? ipc::detail::HexColor::Red : ipc::detail::HexColor::Blue;

    if(side == ipc::detail::BoardSide::None) side = ipc::Hex::closestSide(fromNode);

    vector<int> nodes = this->boardSide(side);

    for(auto toNode : nodes)
    {
        if(DebugLevelHex > 3) cout << "Looking for path between " << fromNode << " and " << toNode << "..." << endl;
        if(this->nodeColor(toNode) != avoid)
        {
            pair<vector<int>,int> tmpDijkstra = ipc::ShortestPath::aStarHex(dynamic_cast<ipc::Graph*>(this), fromNode, toNode, colors);
            if(!tmpDijkstra.first.empty())
            {
                pathCounter ++;
                if(tmpDijkstra.second < pathNCost.second && tmpDijkstra.second >= 0)
                {
                    if(DebugLevelHex > 4) cout << "From " << fromNode << " to " << toNode << " with cost: " << tmpDijkstra.second << endl;
                    pathNCost = tmpDijkstra;
                }
            }

        }
    }
    if(pathNCost.first.size() == 1)
    {
        pathNCost.second = 1000;
        pathCounter = 0;
    }

    if(countPaths) return make_pair(pathNCost.first, pathCounter);
    return pathNCost;
}

ipc::detail::BoardSide ipc::Hex::closestSide(int fromNode, ipc::detail::HexColor color)
{
    pair<int,int> pos = this->indexToSquarePos(fromNode);
    if(color == detail::HexColor::None) color = this->nodeColor(fromNode);
    
    if(color == ipc::detail::HexColor::Red) return (pos.first <= this->size / 2) ? ipc::detail::BoardSide::Top : ipc::detail::BoardSide::Bottom;

    else if(color == ipc::detail::HexColor::Blue) return (pos.second <= this->size / 2) ? ipc::detail::BoardSide::Left : ipc::detail::BoardSide::Right;

    else return (pos.first < pos.second) ? ((pos.first <= this->size / 2) ? 
        ipc::detail::BoardSide::Top : ipc::detail::BoardSide::Bottom) : (pos.second <= this->size / 2) ? ipc::detail::BoardSide::Left : ipc::detail::BoardSide::Right;
}

ipc::detail::BoardSide ipc::Hex::opositeSide(ipc::detail::BoardSide side)
{
    if(side == ipc::detail::BoardSide::Bottom) return ipc::detail::BoardSide::Top;
    else if(side == ipc::detail::BoardSide::Top) return ipc::detail::BoardSide::Bottom;
    else if(side == ipc::detail::BoardSide::Left) return ipc::detail::BoardSide::Right;
    else if(side == ipc::detail::BoardSide::Right) return ipc::detail::BoardSide::Left;
    else return ipc::detail::BoardSide::None;
}

ipc::detail::HexColor ipc::Hex::nodeColor(int fromNode)
{
    return static_cast<ipc::detail::HexColor>(this->cost(fromNode));
}

vector<int> ipc::Hex::boardSide(ipc::detail::BoardSide side)
{
    vector<int> slots;
    switch (side)
    {
    case ipc::detail::BoardSide::Top:
        for(int i = 0; i < this->size; i++) slots.push_back(i);
        break;

    case ipc::detail::BoardSide::Left:
        for(int i = 0; i < this->size * this->size; i += this->size) slots.push_back(i);
        break;

    case ipc::detail::BoardSide::Bottom:
        for(int i = this->size * (this->size - 1); i < this->size * this->size; i++) slots.push_back(i);
        break;

    case ipc::detail::BoardSide::Right:
        for(int i = this->size - 1; i < this->size * this->size; i += this->size) slots.push_back(i);
        break;
    default:
        slots = {};
        break;
    }
    return slots;
}

ipc::detail::Player* ipc::Hex::playerSelect(ipc::detail::HexColor p)
{
    return (p == ipc::detail::HexColor::Blue) ? &this->player[0] : &this->player[1];
}

bool ipc::Hex::isPlayerSide(ipc::detail::HexColor player, ipc::detail::BoardSide side)
{
    if(player == ipc::detail::HexColor::Blue)
        return (side == ipc::detail::BoardSide::Left || side == ipc::detail::BoardSide::Right) ? true : false;

    if(player == ipc::detail::HexColor::Red)
        return (side == ipc::detail::BoardSide::Top || side == ipc::detail::BoardSide::Bottom) ? true : false;
    else return false;
}

ipc::detail::BoardSide ipc::Hex::nodeSide(int fromNode, ipc::detail::HexColor color)
{
    pair<int,int> pos = this->indexToSquarePos(fromNode);
    if(color == ipc::detail::HexColor::None) color = this->nodeColor(fromNode);

    if(color == ipc::detail::HexColor::None || color == ipc::detail::HexColor::Empty) return ipc::detail::BoardSide::None;
    
    if(pos.first == 0)
    {
        if(pos.second == 0) return (color == ipc::detail::HexColor::Blue) ? ipc::detail::BoardSide::Left : ipc::detail::BoardSide::Top;
        if(pos.second == this->size - 1) return (color == ipc::detail::HexColor::Blue) ? ipc::detail::BoardSide::Right : ipc::detail::BoardSide::Top;
        else return ipc::detail::BoardSide::Top;
    }

    else if(pos.first == this->size - 1)
    {
        if(pos.second == 0) return (color == ipc::detail::HexColor::Blue) ? ipc::detail::BoardSide::Left : ipc::detail::BoardSide::Bottom;
        if(pos.second == this->size - 1) return (color == ipc::detail::HexColor::Blue) ? ipc::detail::BoardSide::Right : ipc::detail::BoardSide::Bottom;
        else return ipc::detail::BoardSide::Bottom;
    }

    else if(pos.second == 0) return ipc::detail::BoardSide::Left;

    else if(pos.first == this->size - 1) return ipc::detail::BoardSide::Right;
    
    return ipc::detail::BoardSide::None;
}

bool ipc::Hex::isPlayerNodeSide(ipc::detail::HexColor player, int fromNode)
{
    return this->isPlayerSide(player, this->nodeSide(fromNode, player));
}

// Public ----------------------

// Constructor
ipc::Hex::Hex(int size):ipc::Graph(size * size, static_cast<int>(ipc::detail::HexColor::Empty), false),
    size(size),winner(ipc::detail::HexColor::None), endGame(false), player(nullptr){ ipc::Hex::genBoard(); }

bool ipc::Hex::isValidSize(int size)
{
    return (size >= 3 && size <= 26) ? true : false;
}

// (line, column)
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

int ipc::Hex::heuristicAstar(int fromNode, int toNode)
{
    pair<int,int> fNode = this->indexToSquarePos(fromNode);
    pair<int,int> tNode = this->indexToSquarePos(toNode);

    return abs(tNode.first - fNode.first) + abs(tNode.second - fNode.second);
}

int ipc::Hex::heuristicMiniMax(ipc::detail::HexColor player, int fromNode)
{
    bool touchedOneSide = (this->playerSelect(player)->touched != ipc::detail::BoardSide::None);
    ipc::detail::BoardSide side = (touchedOneSide) ? this->opositeSide(this->playerSelect(player)->touched) : this->closestSide(fromNode, player);
    vector<int> colors = {static_cast<int>(ipc::detail::HexColor::Empty), static_cast<int>(player)};

    pair<vector<int>, int> minPath = this->minPathToSide(fromNode, side, colors, true);

    // number of possible paths to win
    int h0 = minPath.second;

    // biggest possible winner path size
    int h1 = (this->size - minPath.first.size() + 1) * static_cast<int>(touchedOneSide);

    // has same colors neighbours
    int h2 = this->heuristicMiniMaxNeighbouringFactor(player, fromNode);

    if(DebugLevelHex > 3) cout << "h0: " << h0 << " h1: " << h1 << " h2: " << h2 << endl;
    return (h0 + h1 + h2) * ((player == ipc::detail::HexColor::Blue) ? 1 : -1);
}

int ipc::Hex::heuristicMiniMaxNeighbouringFactor(ipc::detail::HexColor player, int fromNode)
{
    vector<int> neighbourhood = this->neigh(fromNode);
    int factor = 0;

    for(auto n : neighbourhood) if (this->nodeColor(n) == player) factor++;

    return factor;
}

ReturnStatus ipc::Hex::genBoard()
{
    try
    {
        if(ipc::Hex::isValidSize(this->size))
        {
            for (int fromNode = 0; fromNode < this->v(); fromNode++)
            {
                vector<int> n = this->neigh(fromNode);

                for(auto toNode : n)
                {
                    if(toNode != ReturnError) this->addEdge(fromNode, toNode, static_cast<int>(ipc::detail::HexColor::Null));

                }
            }
            this->initPlayers();
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

    if(DebugLevelHex > 1) cout << "Node " << fromNode << " has " << n.size() << " neighbours" << endl;
    return n;
}

ReturnStatus ipc::Hex::placeStone(int pos, ipc::detail::HexColor c)
{
    if(this->endGame) return ReturnWarning;
    if(static_cast<ipc::detail::HexColor>(this->cost(pos)) != ipc::detail::HexColor::Empty) return ReturnError;
    ReturnStatus status = this->setNodeValue(pos, static_cast<int> (c));
    if(status == ReturnSuccess)
    {
        ipc::detail::BoardSide side = this->nodeSide(pos);
        this->playerSelect(c)->movements.push_back(pos);
        if (DebugLevelHex > 2) this->printPath((this->playerSelect(c)->movements));
        if(this->isPlayerSide(c, side)) this->playerSelect(c)->touched = side;
        this->isWinner(pos);
    }
    return status;
}

ReturnStatus ipc::Hex::placeStone(pair<char,int> p, ipc::detail::HexColor c)
{
    if(static_cast<ipc::detail::HexColor>(this->cost(this->squarePosToIndex(p))) != ipc::detail::HexColor::Empty) return ReturnError;
    ReturnStatus status = this->setNodeValue(this->squarePosToIndex(p), static_cast<int> (c));
    if(status == ReturnSuccess)
    {
        ipc::detail::BoardSide side = this->nodeSide(this->squarePosToIndex(p));
        this->playerSelect(c)->movements.push_back(this->squarePosToIndex(p));
        if (DebugLevelHex > 2) this->printPath((this->playerSelect(c)->movements));
        if(this->isPlayerSide(c, side)) this->playerSelect(c)->touched = side;
        this->isWinner(this->squarePosToIndex(p));
    }
    return status;
}

ReturnStatus ipc::Hex::placeStone(pair<int,int> p, ipc::detail::HexColor c)
{
    if(static_cast<ipc::detail::HexColor>(this->cost(this->squarePosToIndex(p))) != ipc::detail::HexColor::Empty) return ReturnError;
    ReturnStatus status = this->setNodeValue(this->squarePosToIndex(p), static_cast<int> (c));
    if(status == ReturnSuccess)
    {
        ipc::detail::BoardSide side = this->nodeSide(this->squarePosToIndex(p));
        this->playerSelect(c)->movements.push_back(this->squarePosToIndex(p));
        if (DebugLevelHex > 2) this->printPath((this->playerSelect(c)->movements));
        if(this->isPlayerSide(c, side)) this->playerSelect(c)->touched = side;
        this->isWinner(this->squarePosToIndex(p));
    }
    return status;
}

ReturnStatus ipc::Hex::smartMove(ipc::detail::HexColor player, ipc::detail::PcLevel level)
{
    ReturnStatus status = ReturnError;
    int tries = 0;
    if(level == ipc::detail::PcLevel::Null) level = this->playerSelect(player)->level;
    pair<int,int> pos;

    if(DebugLevelHex > 2) cout << "Smart Move called" << endl;
    
    switch (level)
    {
    case ipc::detail::PcLevel::Dumb:
        if(DebugLevelHex > 2) cout << "Dumb movement" << endl;
        int randPosInd;

        this->playerSelect(player)->touched = ipc::detail::BoardSide::None;
        while (status != ReturnSuccess && tries < this->v())
        {
            randPosInd = ipc::ProbFunctions::randNum(0, this->v());
            status = this->placeStone(randPosInd, player);
            tries++;
        }
        pos = this->indexToSquarePos(randPosInd);
        cout << "PC randomly plays: " << static_cast<char>(pos.second + 65)  << pos.first << endl;
        
        break;

    case ipc::detail::PcLevel::Easy:
        if(DebugLevelHex > 2) cout << "Easy movement" << endl;

        if(this->playerSelect(player)->movements.empty())
        {
            this->playerSelect(player)->touched = ipc::detail::BoardSide::None;

            while (status != ReturnSuccess && tries < this->v())
            {
                int half = this->size/2;
                pos.first = half + tries;
                pos.second = half + tries;
                status = this->placeStone(pos, player);
                tries ++;
            }
            cout << "PC randomly plays: " << static_cast<char>(pos.second + 65)  << pos.first << endl;

        }
        else
        {
            vector<int> colors = {static_cast<int>(ipc::detail::HexColor::Empty)};
            int ind;
            while(status != ReturnSuccess)
            {
                if(tries == 0) colors.push_back(static_cast<int>(player));
                if(tries == 3) return this->smartMove(player, ipc::detail::PcLevel::Dumb);
    
                vector<int> winSeq = this->isWinner(this->playerSelect(player)->movements.back(), colors).first;
                if(DebugLevelHex > 3) this->printPath(winSeq);
                if(!winSeq.empty())
                {
                    ind = winSeq[0];

                    for(auto nextStep : winSeq)
                    {
                        if(find(this->playerSelect(player)->movements.begin(), this->playerSelect(player)->movements.end(), nextStep) == this->playerSelect(player)->movements.end())
                        {
                            ind = nextStep;
                            break;
                        }
                    }
                    status = this->placeStone(ind, player);
                }
                tries ++;
            }
            pos = this->indexToSquarePos(ind);
            cout << "PC plays: " << static_cast<char>(pos.second + 65)  << pos.first << endl;
        }
        break;

    case ipc::detail::PcLevel::Medium:
        if(this->playerSelect(player)->movements.empty())
        {
            this->playerSelect(player)->touched = ipc::detail::BoardSide::None;

            while (status != ReturnSuccess && tries < this->v())
            {
                int half = this->size/2;
                pos.first = half + tries;
                pos.second = half + tries;
                cout << "PC randomly plays: " << static_cast<char>(pos.second + 65)  << pos.first << endl;
                status = this->placeStone(pos, player);
                tries ++;
            }
        }
        else
        {
            pair<int, int> costNpath = this->miniMaxAlphaBeta(player, this->playerSelect(player)->movements.back());
            this->placeStone(costNpath.second, player);
            pos = this->indexToSquarePos(costNpath.second);
            cout << "PC plays: " << static_cast<char>(pos.second + 65)  << pos.first << endl;
        }
        break;

    case ipc::detail::PcLevel::Hard:
        {
            int ind;
            while(status != ReturnSuccess)
            {
                ind = this->monteCarloPlayer(player, 10000);
                status = this->placeStone(ind, player);
            }
            pos = this->indexToSquarePos(ind);
            cout << "PC plays: " << static_cast<char>(pos.second + 65)  << pos.first << endl;
        }
        break;
    
    case ipc::detail::PcLevel::Null:
        break;
    default:
        status = ReturnError;
        break;
    }
    return status;
}

pair<vector<int>,bool> ipc::Hex::isWinner(int fromNode, vector<int> colors)
{
    bool checkWinner = false;
    bool winnerPos = false;
    vector<int> minPath = {};
    pair<vector<int>,int> minPathOne, minPathTwo;
    ipc::detail::HexColor playerColor = this->nodeColor(fromNode);
    ipc::detail::BoardSide sideOne, sideTwo;
    string CoutColor;

    //if(this->playerSelect(playerColor)->movements.size() < this->size) return std::make_pair(minPath, winnerPos);

    if(static_cast<ipc::detail::HexColor>(colors[0]) == ipc::detail::HexColor::Null)
    {
        colors[0] = static_cast<int>(playerColor);
        checkWinner = true;
    }


    switch (playerColor)
    {
    case ipc::detail::HexColor::Blue:

        sideOne = ipc::detail::BoardSide::Left;
        sideTwo = ipc::detail::BoardSide::Right;
        CoutColor = CoutColorBlue;

    break;

    case ipc::detail::HexColor::Red:

        sideOne = ipc::detail::BoardSide::Top;
        sideTwo = ipc::detail::BoardSide::Bottom;
        CoutColor = CoutColorRed;

    break;
    
    default:
        sideOne = this->closestSide(fromNode);
        sideTwo = this->opositeSide(sideOne);

        break;
    }

    minPathOne = this->minPathToSide(fromNode, sideOne, colors);
    if(!minPathOne.first.empty())
    {
        if(DebugLevelHex > 3) cout << "Half way there!" << endl;
        minPathTwo = this->minPathToSide(fromNode, sideTwo, colors);
        if(!minPathTwo.first.empty()) 
        {
            winnerPos = true;
            if(checkWinner) this->playerSelect(playerColor)-> touched = sideOne;            
            if(this->playerSelect(playerColor)->touched != ipc::detail::BoardSide::None)
            {
                minPath = (this->playerSelect(playerColor)->touched == sideOne) ? minPathTwo.first : minPathOne.first;
            }
            else minPath = (minPathOne.second > minPathTwo.second) ? minPathTwo.first : minPathOne.first;
            
            if(checkWinner)
            {
                this->winner = playerColor;
                cout << CoutColorStart + CoutColorBoldOn + CoutColor << "PLAYER " << static_cast<int>(playerColor) - 1 << " WON!" << CoutColorEnd << endl;
                this->endGame = true; 
            }
        }
    }
    else this->playerSelect(playerColor)->touched = ipc::detail::BoardSide::None;

    return make_pair(minPath, winnerPos);
}

pair<int, int> ipc::Hex::miniMaxAlphaBeta(ipc::detail::HexColor player, int fromNode, int depth, int alpha, int beta)
{
    pair<int,int> result;
    vector<int> colors = {static_cast<int>(player)};
    result.first = this->heuristicMiniMax(player, fromNode);
    result.second = fromNode;


    if(depth == 0 || this->isWinner(fromNode, colors).second) return result;


    // Blue is the maximizing player as he is the first one to play (by definition)
    if(player == ipc::detail::HexColor::Blue)
    {
        result.first = -1000;
        this->printPath(this->neigh(fromNode));
        for(auto neighbour : this->neigh(fromNode))
        {
            if (this->nodeColor(neighbour) == ipc::detail::HexColor::Empty)
            {
                result = miniMaxAlphaBeta(ipc::detail::HexColor::Red, neighbour, depth - 1, alpha, beta);
                result.first = max(alpha, result.first);
                alpha =  max(alpha, result.first);
                if (alpha >= beta) break;
            }
        }
        cout << "Blue best move: " << result.second << endl;
        return result;
    }
    else
    {
        result.first = 1000;
        for(auto neighbour : this->neigh(fromNode))
        {
            if (this->nodeColor(neighbour) == ipc::detail::HexColor::Empty)
            {
                result = miniMaxAlphaBeta(ipc::detail::HexColor::Blue, neighbour, depth - 1, alpha, beta);
                result.first = min(beta, result.first);
                beta =  min(beta, result.first);
                if (beta <= alpha) break;
            }
        }
        cout << "Red best move: " << result.second << endl;
    }
    return result;
}

int ipc::Hex::monteCarloPlayer(ipc::detail::HexColor player, int sim)
{  

    //vector<int> nodesProb(this->size*this->size, 0);

    ipc::detail::HexColor opponent = (player == ipc::detail::HexColor::Blue) ? ipc::detail::HexColor::Red : ipc::detail::HexColor::Blue;

    volatile ipc::detail::HexColor actualPlayer;
    volatile ipc::detail::HexColor winner = ipc::detail::HexColor::None;
    vector<int> colors = {static_cast<int>(ipc::detail::HexColor::Red)};

    vector<int> fromNodes = this->boardSide(ipc::detail::BoardSide::Top);
    vector<int> toNodes = this->boardSide(ipc::detail::BoardSide::Bottom);

    vector<int> moves;

    int move = -1, bestMoveVal = 0;

    srand(time(0));

    for(int m = 0; m < this->size * this->size; m++) if(this->cost(m) == static_cast<int>(ipc::detail::HexColor::Empty)) moves.push_back(m);


    for(auto node : moves)
    {
        volatile int bestMoveValTmp = 0;

        actualPlayer = player;
        this->setNodeValue(node, static_cast<int>(actualPlayer));

        for(int s = 0; s < sim; s++)
        {
            winner = ipc::detail::HexColor::None;
            if(DebugLevelHex > 2) cout << "Monte Carlo sim: " << s << endl;
            vector<int> nodes = moves;
            

            random_shuffle(nodes.begin(), nodes.end());
            
            for(auto n : nodes)
            {
                if(DebugLevelHex > 2) cout << "node: " << n << endl;

                actualPlayer =  (actualPlayer == player) ? opponent : player;
                if(n != node) this->setNodeValue(n, static_cast<int> (actualPlayer));
            }

            for(auto fromNode : fromNodes)
            {
                if(this->nodeColor(fromNode) == ipc::detail::HexColor::Red)
                {
                    for(auto toNode : toNodes)
                    {
                        if(this->nodeColor(toNode) == ipc::detail::HexColor::Red)
                        {
                            pair<vector<int>,int> tmpDijkstra = ipc::ShortestPath::aStarHex(dynamic_cast<ipc::Graph*>(this), fromNode, toNode, colors);
                            if(!tmpDijkstra.first.empty() && tmpDijkstra.second != -1)
                            {
                                winner = ipc::detail::HexColor::Red;
                                break;
                            }
                            else winner = ipc::detail::HexColor::Blue;
                        }
                        else winner = ipc::detail::HexColor::Blue;
                    }
                }
                else winner = ipc::detail::HexColor::Blue;
            }
            for(auto n: nodes) if(n != node) this->setNodeValue(n, static_cast<int> (ipc::detail::HexColor::Empty));


            if(player == winner) bestMoveValTmp++;
        }
        this->setNodeValue(node, static_cast<int> (ipc::detail::HexColor::Empty));

        if(DebugLevelHex > 2) this->printBoard();

        if(bestMoveValTmp > bestMoveVal)
        {
            bestMoveVal = bestMoveValTmp;
            move = node;
        }

    }
    cout << "Best move probability: " << static_cast<double>(bestMoveVal)/sim << endl;

    return move;

/*
    for(int s = 0; s < sim; s++)
    {
        if(DebugLevelHex > 2) cout << "Monte Carlo sim: " << s << endl;
        vector<int> nodes(this->size*this->size, 0);
        vector<int> tmpNodesProb(this->size*this->size, 0);

        iota(nodes.begin(), nodes.end(), 0);
        random_shuffle(nodes.begin(), nodes.end());


        for(int n = 0; n < this->size * this->size; n++)
        {
            actualPlayer =  (n < this->size * this->size /2) ? player : opponent;

            if(this->cost(nodes[n]) == static_cast<int>(ipc::detail::HexColor::Empty))
            {
                if(DebugLevelHex > 2) cout << "node[" << n << "]: " << nodes[n] << endl;
                this->setNodeValue(nodes[n], static_cast<int> (actualPlayer));
                if(actualPlayer == player) tmpNodesProb[nodes[n]]++;
            }
        }

        for(auto fromNode : fromNodes)
        {
            if(this->nodeColor(fromNode) == ipc::detail::HexColor::Red)
            {
                for(auto toNode : toNodes)
                {
                    if(this->nodeColor(toNode) == ipc::detail::HexColor::Red)
                    {
                        pair<vector<int>,int> tmpDijkstra = ipc::ShortestPath::aStarHex(dynamic_cast<ipc::Graph*>(this), fromNode, toNode, colors);
                        if(!tmpDijkstra.first.empty())
                        {
                            winner = ipc::detail::HexColor::Red;
                            break;
                        }
                        else winner = ipc::detail::HexColor::Blue;
                    }
                }
            }
        }
        if(DebugLevelHex > 2) this->printBoard();

        for(int n = 0; n < this->size * this->size; n++)
        {
            if(find(this->playerSelect(player)->movements.begin(),this->playerSelect(player)->movements.end() , nodes[n]) == this->playerSelect(player)->movements.end() &&
                find(this->playerSelect(opponent)->movements.begin(),this->playerSelect(opponent)->movements.end() , nodes[n]) == this->playerSelect(opponent)->movements.end())
            {
                this->setNodeValue(nodes[n], static_cast<int> (ipc::detail::HexColor::Empty));
            }
        }

        if(DebugLevelHex > 2) this->printBoard();

        if(winner == player) transform(nodesProb.begin(), nodesProb.end(), tmpNodesProb.begin(), nodesProb.begin(), plus<int>());
    }

    cout << "Nodes Prob dist: ";
    for(auto p : nodesProb) cout << p << " ";
    cout << endl;

    return max_element(nodesProb.begin(), nodesProb.end()) - nodesProb.begin();
*/
}

void ipc::Hex::gameReport()
{
     cout << "-----------GAME LOG-------------" << endl;

    cout << CoutColorStart + CoutColorBoldOn + CoutColorBlue << "Player 1 made " << this->playerSelect(ipc::detail::HexColor::Blue)->movements.size() << " movements: " << endl;
    ipc::Hex::printPath(this->playerSelect(ipc::detail::HexColor::Blue)->movements);
    cout << CoutColorEnd;

    cout <<  CoutColorStart + CoutColorBoldOn + CoutColorRed << "Player 2 made " << this->playerSelect(ipc::detail::HexColor::Red)->movements.size() << " movements: " << endl;
    ipc::Hex::printPath(this->playerSelect(ipc::detail::HexColor::Red)->movements);
    cout << CoutColorEnd;
}

void ipc::Hex::printPath(vector<int> v)
{
    if(v.empty()) return;
    pair<int,int> pos;

    cout<< "Player path: ";
    
    for(auto x: v)
    {
        pos = this->indexToSquarePos(x);
        cout << static_cast<char>(pos.second + 65)  << pos.first;
        if (x != v.back()) cout << "->";
    }
    cout << endl;
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
                int val = this->cost(this->squarePosToIndex(line,col));
                switch (static_cast<ipc::detail::HexColor> (val)) {
                    case ipc::detail::HexColor::Empty: 
                        cout << ". ";
                        break;

                    case ipc::detail::HexColor::Red: 
                        cout << CoutColorStart + CoutColorBoldOn + CoutColorRed << "x " << CoutColorEnd;;
                        break;

                    case ipc::detail::HexColor::Blue: 
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