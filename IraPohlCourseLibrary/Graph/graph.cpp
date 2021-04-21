#include "graph.hpp"


// Graph Class functions ----------------------

// Private ----------------------
void ipc::Graph::initVertices(int numOfVertices, int value)
{
    this->vertices = new ipc::detail::vertice[numOfVertices];

    for(int v = 0; v < numOfVertices; v++)
    {
        this->vertices[v] = {v, -1, value}; 
    }
}

void ipc::Graph::initEdges(int numOfVertices)
{
    this->edges = new LinkedList<ipc::detail::edge>*[numOfVertices];

    for (int v = 0; v < numOfVertices; v++)
    {
        this->edges[v] = nullptr;
    }
}

ReturnStatus ipc::Graph::addEdgeSorted(ipc::detail::Node<ipc::detail::edge>* nodeToSort)
{

    ipc::detail::Node<ipc::detail::edge>* tmp = this->edges[nodeToSort->data->fromNode->vertice]->h();


    while(tmp != nullptr)
    {
        if(nodeToSort->data->value < tmp->data->value)
        {
            if(tmp == this->edges[nodeToSort->data->fromNode->vertice]->h()) this->edges[nodeToSort->data->fromNode->vertice]->prependNode(nodeToSort);
            else
            {
                nodeToSort->prev = tmp->prev;
                nodeToSort->next = tmp;

                tmp->prev->next = nodeToSort;
                tmp->prev = nodeToSort;
            }
            break;
        }
        else if(tmp->next == nullptr)
        {
            nodeToSort->prev = tmp;
            nodeToSort->next = tmp->next;
            tmp->next = nodeToSort;
            break;
        }
        tmp = tmp->next;
    }

    return ReturnSuccess;
}


// Public ----------------------

// Constructor
ipc::Graph::Graph(int numOfVertices, int verticeBaseCost, bool isDirected):numOfVertices(numOfVertices), isDirected(isDirected){ ipc::Graph::init(numOfVertices, verticeBaseCost, isDirected); }

ipc::Graph::Graph(){}

ReturnStatus ipc::Graph::init(int numOfVertices, int verticeBaseCost, bool isDirected)
{
    if (DebugLevelGraph > 3) cout << "Class initialized." << endl;
    this->numOfVertices = numOfVertices;
    this->isDirected = isDirected;
    ipc::Graph::initVertices(numOfVertices, verticeBaseCost);
    ipc::Graph::initEdges(numOfVertices);

    return ReturnSuccess;
}

bool ipc::Graph::isDirectedFlag(){ return this->isDirected; }

int ipc::Graph::v(){ return this->numOfVertices; }

bool ipc::Graph::isValid(int v)
{
    if(v >= numOfVertices || v < 0)
    {
        if (DebugLevelGraph > 1) cout << "Input node " << v << " does not exist." << endl;
        return false;           
    }
    else return true;
}

bool ipc::Graph::hasEdges(int v)
{
    if(this->edges[v] == nullptr)
    {
        if (DebugLevelGraph > 1) cout << "Input node has no edges." << endl;
        return false;           
    }
    else return true;
}

int ipc::Graph::e(int fromNode)
{
    if(!ipc::Graph::isValid(fromNode)) return -1;
    if(this->edges[fromNode] == nullptr) return 0;
    return this->edges[fromNode]->size(); 
}


int ipc::Graph::cost(int fromNode, int toNode)
{
    ipc::detail::Node<ipc::detail::edge>* tmp = ipc::Graph::isAdjacent(fromNode, toNode);

    if (tmp == nullptr) return ReturnError;
    else return tmp->data->value;
}

ReturnStatus ipc::Graph::setEdgeValue(int fromNode, int toNode, int value, bool directed)
{
    if(!this->isDirected && directed) ipc::Graph::setEdgeValue(toNode, fromNode, value, false);

    if (!ipc::Graph::isValid(fromNode) || !ipc::Graph::isValid(toNode))
    {
        return ReturnError;
    }

    ipc::detail::Node<ipc::detail::edge>* chgNode = isAdjacent(fromNode, toNode);

    if(chgNode == nullptr)
    {
        if (DebugLevelGraph > 3) cout << "Vertice is not on the list." << endl;
        return ReturnError;
    }

    if (chgNode->data->value == value)
    {
        if (DebugLevelGraph > 3) cout << "Value remains the same." << endl;
        return ReturnWarning;
    }
    
    chgNode->data->value = value;
    if(chgNode->prev != nullptr) chgNode->prev->next = chgNode->next;
    else this->edges[fromNode]->setHeadPointer(chgNode->next);

    if(chgNode->next != nullptr) chgNode->next->prev = chgNode->prev;

    return ipc::Graph::addEdgeSorted(chgNode);
}

int ipc::Graph::cost(int fromNode)
{
    if (!ipc::Graph::isValid(fromNode)) return ReturnError;
    else return this->vertices[fromNode].value;
}

ReturnStatus ipc::Graph::setNodeValue(int fromNode, int value)
{
    if (fromNode > this->numOfVertices) return ReturnError;
    else this->vertices[fromNode].value = value;

    return ReturnSuccess;
}

ipc::detail::edge* ipc::Graph::newEdge(int fromNode, int toNode, int value)
{
    ipc::detail::edge* newEdge = new ipc::detail::edge {.fromNode = &this->vertices[fromNode], .toNode = &this->vertices[toNode],  .value = value};

    return newEdge;
}

ipc::detail::Node<ipc::detail::edge>* ipc::Graph::isAdjacent(int fromNode, int toNode)
{
    if (!ipc::Graph::isValid(fromNode) || !ipc::Graph::isValid(toNode))
    {
        return nullptr;
    }

    if(!ipc::Graph::hasEdges(fromNode))
    {
        return nullptr;
    }


    ipc::detail::Node<ipc::detail::edge>* tmp = this->edges[fromNode]->h();
    
    while(true)
    {
        if (tmp->data->toNode->vertice == toNode)
        {
            if (DebugLevelGraph > 3) cout << "Node " << toNode << " found." << endl;
            return tmp;
        }
        if (tmp->next == nullptr) break;
        else tmp = tmp->next;
    }
    if (DebugLevelGraph > 1) cout << "Node " << toNode << " not found." << endl;
    return nullptr;
}

ReturnStatus ipc::Graph::addEdge(int fromNode, int toNode, int value, bool directed)
{
    if(!this->isDirected && directed) ipc::Graph::addEdge(toNode, fromNode, value, false);

    if (!ipc::Graph::isValid(fromNode) || !ipc::Graph::isValid(toNode))
    {
        return ReturnError;
    }

    else if (ipc::Graph::isAdjacent(fromNode, toNode) != nullptr)
    {
        if (DebugLevelGraph > 2) cout << "WARNING: Nodes are already connected." << endl;
        return ReturnWarning;
    }

    else if(!ipc::Graph::hasEdges(fromNode))
    {
        this->edges[fromNode] = new LinkedList<ipc::detail::edge>; 
        this->edges[fromNode]->prepend(ipc::Graph::newEdge(fromNode, toNode, value));

        if (DebugLevelGraph > 3) cout << "First element added." << endl;

        return ReturnSuccess;
    }

    else return ipc::Graph::addEdgeSorted(this->edges[fromNode]->newNode(ipc::Graph::newEdge(fromNode, toNode, value)));
}

ReturnStatus ipc::Graph::removeEdge(int fromNode, int toNode, bool directed)
{
    if(!this->isDirected && directed) ipc::Graph::removeEdge(toNode, fromNode, false);

    if (!ipc::Graph::isValid(fromNode) || !ipc::Graph::isValid(toNode))
    {
        return ReturnError;
    }

    ipc::detail::Node<ipc::detail::edge>* tmp = ipc::Graph::isAdjacent(fromNode, toNode);

    if (tmp == nullptr)
    {
        if (DebugLevelGraph > 2) cout << "WARNING: Nodes are already disconnected." << endl;
        return ReturnWarning;
    }

    else
    {
        if (tmp->next != nullptr) tmp->next->prev = tmp->prev;
        if (tmp->prev != nullptr) tmp->prev->next = tmp->next;
        else this->edges[fromNode] = nullptr;
    }
    delete tmp;

    if (DebugLevelGraph > 3) cout << "Edge removed." << endl;
    return ReturnSuccess;
}

vector<int> ipc::Graph::neighbours(int fromNode)
{
    if(!isValid(fromNode)) return {};

    if(hasEdges(fromNode))
    {
            vector<int> neigh;
            ipc::detail::Node<ipc::detail::edge>* tmp = this->edges[fromNode]->h();
            
            while(tmp != nullptr)
            {
                neigh.insert(neigh.end(), tmp->data->toNode->vertice);
                tmp = tmp->next;
            }
            return neigh;
    }
    else return {};
}

void ipc::Graph::print()
{
    cout << "Graph Representation:" << endl;
    for (int v = 0; v < this->numOfVertices; v++){
        cout << v << "-> ";
        if(ipc::Graph::hasEdges(v)){
            ipc::detail::Node<ipc::detail::edge>* tmp = this->edges[v]->h();
            
            while(tmp != nullptr)
            {
                cout << "(" << tmp->data->toNode->vertice <<", " << tmp->data->value <<")";
                if(tmp->next != nullptr) cout << ", ";
                tmp = tmp->next;
            }
        }
        cout << endl;
    }
}

// Destructor
ipc::Graph::~Graph()
{
    if (DebugLevelGraph > 3) cout << "Graph Class destructor called." << endl;

    for (int v = 0; v < this->numOfVertices; v++)
    {
        if(this->edges[v] != nullptr) 
        {
            ipc::detail::Node<ipc::detail::edge>* tmp = this->edges[v]->h();
            
            while(tmp != nullptr)
            {
                delete tmp->data;
                tmp = tmp->next;
            }
            
            delete this->edges[v];
        }
    }

    delete [] this->vertices;
    delete [] this->edges;

}