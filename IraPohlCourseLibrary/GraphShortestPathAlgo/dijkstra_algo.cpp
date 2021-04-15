#include "dijkstra_algo.hpp"

// Dijkstra's Algorithm namespace functions ----------------------
// Private ----------------------

vector<int> ipc::ShortestPath::buildPath(unordered_map<int, int> cameFrom, int fromNode, int toNode)
{
    vector<int> path;

    int current = toNode;

    while(current != fromNode)
    {
        path.insert(path.begin(), current);
        current = cameFrom[current];
    }
    path.insert(path.begin(), fromNode);

    return path;
}

// Public ----------------------
pair<vector<int>, int> ipc::ShortestPath::dijkstra(ipc::Graph* g, int fromNode, int toNode)
{
    if ((!g->isValid(fromNode) || !g->isValid(toNode)) || !g->hasEdges(fromNode)) return {};

    PriorityQueue frontier;
    frontier.insert(fromNode, fromNode, 0);

    unordered_map<int, int> cameFrom;
    unordered_map<int, int> costSoFar;

    cameFrom[fromNode] = fromNode;
    costSoFar[fromNode] = 0;

    while(!frontier.empty())
    {
        ipc::detail::Node<ipc::detail::vertice>* current = frontier.popHead();
        int currentNode = current->data->vertice;

        if(currentNode == toNode) break;

        for(auto nextNode : g->neighbors(currentNode))
        {
            int newCost = costSoFar[currentNode] + g->cost(currentNode, nextNode);


            if(costSoFar.find(nextNode) == costSoFar.end() || newCost < costSoFar[nextNode])
            {
                costSoFar[nextNode] = newCost;
                frontier.insert(nextNode, currentNode, newCost);
                cameFrom[nextNode] = currentNode;
            }
        }
    }
    return make_pair(ipc::ShortestPath::buildPath(cameFrom, fromNode, toNode), costSoFar[toNode]);
}

pair<vector<int>, int> ipc::ShortestPath::dijkstraHex(ipc::Graph* g, int fromNode, int toNode, vector<int> validNodes)
{
    if ((!g->isValid(fromNode) || !g->isValid(toNode)) || !g->hasEdges(fromNode)) return {};

    bool pathFound = false;

    PriorityQueue frontier;
    frontier.insert(fromNode, fromNode, 0);

    unordered_map<int, int> cameFrom;
    unordered_map<int, int> costSoFar;

    cameFrom[fromNode] = fromNode;
    costSoFar[fromNode] = 0;

    if (DebugLevelShortestPath > 1) cout << "Dijkstra Path from " << fromNode << " to " << toNode << endl;

    while(!frontier.empty())
    {
        ipc::detail::Node<ipc::detail::vertice>* current = frontier.popHead();
        int currentNode = current->data->vertice;

        if (DebugLevelShortestPath > 1) cout << "Current node: " << currentNode << endl;

        if(currentNode == toNode) 
        {
            pathFound = true;
            break;
        }

        for(auto nextNode : g->neighbors(currentNode))
        {
            if (DebugLevelShortestPath > 1) cout << "To node: " << nextNode << endl;
            
            if(find(validNodes.begin(), validNodes.end(), g->cost(nextNode)) != validNodes.end())
            {
                int newCost = costSoFar[currentNode] + g->cost(currentNode, nextNode);
                if (DebugLevelShortestPath > 1) cout << "New Cost: " << newCost << endl;

                if(costSoFar.find(nextNode) == costSoFar.end() || newCost < costSoFar[nextNode])
                {
                    costSoFar[nextNode] = newCost;
                    frontier.insert(nextNode, currentNode, newCost);
                    cameFrom[nextNode] = currentNode;
                }
            }
        }
    }
    return (pathFound) ? make_pair(ipc::ShortestPath::buildPath(cameFrom, fromNode, toNode), costSoFar[toNode]) : make_pair(vector<int>(), -1);
}

void ipc::ShortestPath::printPath(vector<int> v)
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
