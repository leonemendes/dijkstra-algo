#include "dijkstra_algo.hpp"

// Dijkstra's Algorithm Class functions ----------------------

// Private ----------------------
ReturnStatus ipc::ShortestPath::recursivePath(PriorityQueue* q, PriorityQueue* tmpQ, int fromNode, int toNode, int cost, int lastNode, vector<int> specificCost, bool firstNode)
{
    vector<int> neigh = g->neighbors(fromNode);
    if(neigh.empty()) return ReturnEndOfLoop;

    detail::Node<detail::edge>* tmp;

    int tmpCost = (!specificCost.empty()) ? g->getNodeValue(fromNode) : g->getEdgeValue(lastNode, fromNode);

    if(!firstNode)
    {
        if(!specificCost.empty() && (find(specificCost.begin(), specificCost.end(), tmpCost) == specificCost.end()))
        {
            if(DebugLevelShortestPath > 1) cout << "Node " << fromNode << " does not match specific cost " << endl;
            return ReturnEndOfLoop;
        }
        cost+= tmpCost;
        if(DebugLevelShortestPath > 1) cout << "Cost updated: " << cost << endl;
    }

    
    int status = q->insert(fromNode, lastNode, cost);
    if(DebugLevelShortestPath > 1) cout<< "Node: " << fromNode << " cost: " << cost << endl;

    if (status == ReturnWarning) return ReturnWarning;

    if(fromNode == toNode)
    {
        this->cost = cost;
        this->pathFound = true;
        if(DebugLevelShortestPath > 1) cout << "Found a path." << endl;
        return ReturnSuccess;
    }

    if(DebugLevelShortestPath > 1) cout << "Last Node: " << lastNode << " From Node: " << fromNode << " bool: " << firstNode << endl;
    tmp = g->isAdjacent(fromNode, neigh[0]);

    while(tmp != nullptr)
    {

        int nextNode = tmp->data->toNode->vertice;

        if(DebugLevelShortestPath > 1) cout << "Inside " << fromNode << " neighbors: " << nextNode << endl;

        if(recursivePath(q, tmpQ, nextNode, toNode, cost, fromNode, specificCost, false) == ReturnSuccess) break;

        tmp = tmp->next;
    }
    if(DebugLevelShortestPath > 1) cout << "End of " << fromNode << " neighbors." << endl;
    tmpQ->insert(fromNode,-1,-1);
    return ReturnEndOfLoop;
}

// Public ----------------------

// Constructor
ipc::ShortestPath::ShortestPath(Graph* g, vector<int> v):g(g), pathFound(false), cost(0), v(v){}

ReturnStatus ipc::ShortestPath::path(int fromNode, int toNode, vector<int> specificCost)
{
    if ((!g->isValid(fromNode) || !g->isValid(toNode)) || !g->hasEdges(fromNode)) return ReturnError;

    int cost = 0;

    PriorityQueue* q = new PriorityQueue;
    PriorityQueue* tmpQ = new PriorityQueue;

    ipc::ShortestPath::recursivePath(q, tmpQ, fromNode, toNode, cost, fromNode, specificCost);
    
    if(this->pathFound)
    {
        if(DebugLevelShortestPath > 1) cout << "Shortest path found!" << endl;
        this->v.clear();
        q->fromQueueToType(this->v, toNode, fromNode);
        this->pathFound = false;
        return ReturnSuccess;
    }
    if(DebugLevelShortestPath > 1) cout << "Shortest path not found!" << endl;
    return ReturnNotFound;
}

void ipc::ShortestPath::printPath()
{
    if(v.empty()) return;

    cout<< "Dijkstra shortest Path: ";
    
    for(auto x: v)
    {
        cout << x;
        if (x != v.back()) cout << "->";
    }
    cout << endl;
}

int ipc::ShortestPath::pathCost(){ return this->cost; }

// Destructor
ipc::ShortestPath::~ShortestPath(){}
