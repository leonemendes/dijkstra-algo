#include "dijkstra_algo.hpp"

ReturnStatus ipc::ShortestPath::recursivePath(int fromNode, int toNode, int cost, int lastNode, bool firstNode)
{
    vector<int> neigh = g->neighbors(fromNode);
    if(neigh.empty()) return ReturnEndOfLoop;

    detail::Node<detail::edge>* tmp;

    if(!firstNode)
    {
        cost+= g->getEdgeValue(lastNode, fromNode);
        cout << "Cost updated: " << cost << endl;
    }
    
    int status = q->insert(fromNode, lastNode, cost);
    cout<< "Node: " << fromNode << " cost: " << cost << endl;

    if (status == ReturnWarning) return ReturnWarning;

    if(fromNode == toNode)
    {
        this->cost = cost;
        return ReturnSuccess;
    }

    cout << "Last Node: " << lastNode << " From Node: " << fromNode << " bool: " << firstNode << endl;
    tmp = g->isAdjacent(fromNode, neigh[0]);

    while(tmp != nullptr)
    {
        cout << "Inside " << fromNode << " neighbors." << endl;

        int nextNode = tmp->data->toNode->vertice;

        if(recursivePath(nextNode, toNode, cost, fromNode, false) == ReturnSuccess) break;

        tmp = tmp->next;
    }
    cout << "End of " << fromNode << " neighbors." << endl;
    return ReturnEndOfLoop;
}

ipc::ShortestPath::ShortestPath(Graph* g, PriorityQueue* q, vector<int> v):g(g), q(q), v(v), cost(0){}

ReturnStatus ipc::ShortestPath::path(int fromNode, int toNode)
{
    if ((!g->isValid(fromNode) || !g->isValid(toNode)) || !g->hasEdges(fromNode))
    {
        return ReturnError;

    }

    int cost = 0;

    ipc::ShortestPath::recursivePath(fromNode, toNode, cost, fromNode);

    detail::Node<detail::vertice>* tmp = q->contains(toNode);

    while(tmp != nullptr)
    {
        v.insert(v.begin(), tmp->data->vertice);
        if (tmp->data->vertice == fromNode) break;

        tmp = q->contains(tmp->data->fromVertice);
    }


    return ReturnSuccess;
}

void ipc::ShortestPath::printQueue()
{
    if(q != nullptr) q->print();
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

ipc::ShortestPath::~ShortestPath()
{
    if (DebugLevelShortestPath > 0) cout << "ShortestPath Class destructor called." << endl;
    if(q!= nullptr) delete q;
}
