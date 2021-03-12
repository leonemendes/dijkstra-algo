#include <iostream>
#include <vector>
#include <algorithm>

#include "../../standard_defines.h"

using std::cout;
using std::endl;
using std::ostream;
using std::min;
using std::vector;
using std::find;

// Dense graphs -> matrix representation || sparse graphs -> list representation (most of the life problems are sparse)

namespace MyLibrary
{
    namespace detail
    {
        template<class T>
        class Node
        {
            public:
            T* data;
            
            Node<T>* prev;
            Node<T>* next;
        };      
    }

    template <class T>
    class LinkedList
    {
        private:
        detail::Node<T>* head;

        public:
        LinkedList():head(nullptr)
        {
            if (DebugLevel > 3) cout << "LinkedList Class constructor called." << endl;
        }

        detail::Node<T>* h()
        {
            return this->head;
        }
        
        void setHeadPointer(detail::Node<T>* n){ this->head = n; }

        detail::Node<T>* newNode(T* n, detail::Node<T>* prev = nullptr, detail::Node<T>* next = nullptr)
        {
            detail::Node<T>* result = new detail::Node<T>{.data = n, .prev = prev, .next = next};

            return result;
        }
        
        ReturnStatus prependNode(detail::Node<T>* n)
        {
            n->next = this->head;
            if (this->head != nullptr) this->head->prev = n;
            setHeadPointer(n);

            if (DebugLevel > 3) cout << "Node added." << endl;

            return ReturnSuccess;
        }

        ReturnStatus prepend(T* n)
        {
            detail::Node<T>* tmp = newNode(n);

            return prependNode(tmp);
        }

        ReturnStatus popHead()
        {
            if(this->head == nullptr) return ReturnWarning;
            else
            {
                detail::Node<T>* tmp = this->head;
                setHeadPointer(this->head->next);

                delete tmp;
                return ReturnSuccess;
            }
        }

        int size()
        {
            if (DebugLevel > 3) cout << "Size function called." << endl;
            int size = 0;

            detail::Node<T>* current = this->head;

            while(current != nullptr)
            {
                size++;
                current = current->next;
            } 
            if (DebugLevel > 3) cout << "Size:" << size << endl;

            return size;
        }

        ~LinkedList()
        {
            if (DebugLevel > 3) cout << "LinkedList Class destructor called." << endl;

            detail::Node<T>* current = this->head;

            while(current != nullptr)
            {
                current = current->next;
                delete this->head;
                this->head = current;
            }
        }

    };
}

struct vertice
{
    int vertice, value;
};

struct edge
{
    struct vertice* fromNode;
    struct vertice* toNode;

    int cost;
};

class Graph
{
    private:
    vertice* vertices;
    MyLibrary::LinkedList<edge>** edges;
    int numOfVertices;

    void initVertices(int numOfVertices)
    {
        this->vertices = new vertice[numOfVertices];

        for(int v = 0; v < numOfVertices; v++)
        {
            this->vertices[v] = {v, 0}; 
        }
    }

    void initEdges(int numOfVertices)
    {
        this->edges = new MyLibrary::LinkedList<edge>*[numOfVertices];

        for (int v = 0; v < numOfVertices; v++)
        {
            this->edges[v] = nullptr;
        }
    }

    ReturnStatus addEdgeSorted(MyLibrary::detail::Node<edge>* nodeToSort)
    {

        MyLibrary::detail::Node<edge>* tmp = this->edges[nodeToSort->data->fromNode->vertice]->h();


        while(tmp != nullptr)
        {
            if(nodeToSort->data->cost < tmp->data->cost)
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

    public:
    Graph(int numOfVertices = 1):numOfVertices(numOfVertices)
    {
        if (DebugLevel > 3) cout << "Class constructor called." << endl;
        initVertices(numOfVertices);
        initEdges(numOfVertices);
    }


    int v(){ return numOfVertices; }

    bool isValid(int v)
    {
        if(v >= numOfVertices)
        {
            if (DebugLevel > 1) cout << "Input node do not exist." << endl;
            return false;           
        }
        else return true;
    }

    bool hasEdges(int v)
    {
        if(this->edges[v] == nullptr)
        {
            if (DebugLevel > 1) cout << "Input node has no edges." << endl;
            return false;           
        }
        else return true;
    }

    int e(int fromNode)
    {
        if(!isValid(fromNode)) return -1;
        if(this->edges[fromNode] == nullptr) return 0;
        return this->edges[fromNode]->size(); 
    }


    int getEdgeValue(int fromNode, int toNode)
    {
        MyLibrary::detail::Node<edge>* tmp = isAdjacent(fromNode, toNode);

        if (tmp == nullptr) return ReturnError;
        else return tmp->data->cost;
    }

    ReturnStatus setEdgeValue(int fromNode, int toNode, int cost)
    {
        if (!isValid(fromNode) || !isValid(toNode))
        {
            return ReturnError;
        }

        MyLibrary::detail::Node<edge>* chgNode = isAdjacent(fromNode, toNode);

        if(chgNode == nullptr)
        {
            if (DebugLevel > 3) cout << "Vertice is not on the list." << endl;
            return ReturnError;
        }

        if (chgNode->data->cost == cost)
        {
            if (DebugLevel > 3) cout << "Value remains the same." << endl;
            return ReturnWarning;
        }
        
        chgNode->data->cost = cost;
        if(chgNode->prev != nullptr) chgNode->prev->next = chgNode->next;
        else this->edges[fromNode]->setHeadPointer(chgNode->next);

        if(chgNode->next != nullptr) chgNode->next->prev = chgNode->prev;

        return addEdgeSorted(chgNode);
    }

    int getNodeValue(int fromNode)
    {
        if (!isValid(fromNode)) return ReturnError;
        else return this->vertices[fromNode].value;
    }

    ReturnStatus setNodeValue(int fromNode, int value)
    {

        if (fromNode > this->numOfVertices) return ReturnError;
        else this->vertices[fromNode].value = value;

        return ReturnSuccess;
    }

    edge* newEdge(int fromNode, int toNode, int cost = 1)
    {
        edge* newEdge = new edge {.fromNode = &this->vertices[fromNode], .toNode = &this->vertices[toNode],  .cost = cost};

        return newEdge;
    }

    MyLibrary::detail::Node<edge>* isAdjacent(int fromNode, int toNode)
    {
        if (!isValid(fromNode) || !isValid(toNode))
        {
            return nullptr;
        }

        if(!hasEdges(fromNode))
        {
            return nullptr;
        }


        MyLibrary::detail::Node<edge>* tmp = this->edges[fromNode]->h();
        
        while(true)
        {
            if (tmp->data->toNode->vertice == toNode)
            {
                if (DebugLevel > 3) cout << "Node " << toNode << " found." << endl;
                return tmp;
            }
            if (tmp->next == nullptr) break;
            else tmp = tmp->next;
        }
        if (DebugLevel > 1) cout << "Node " << toNode << " not found." << endl;
        return nullptr;
    }

    ReturnStatus addEdge(int fromNode, int toNode, int cost = 1)
    {
        if (!isValid(fromNode) || !isValid(toNode))
        {
            return ReturnError;
        }

        else if (isAdjacent(fromNode, toNode) != nullptr)
        {
            if (DebugLevel > 2) cout << "WARNING: Nodes are already connected." << endl;
            return ReturnWarning;
        }

        else if(!hasEdges(fromNode))
        {
            this->edges[fromNode] = new MyLibrary::LinkedList<edge>; 
            this->edges[fromNode]->prepend(newEdge(fromNode, toNode, cost));

            if (DebugLevel > 3) cout << "First element added." << endl;

            return ReturnSuccess;
        }

        else return addEdgeSorted(this->edges[fromNode]->newNode(newEdge(fromNode, toNode, cost)));
    }

    ReturnStatus removeEdge(int fromNode, int toNode)
    {
        if (!isValid(fromNode) || !isValid(toNode))
        {
            return ReturnError;
        }

        MyLibrary::detail::Node<edge>* tmp = isAdjacent(fromNode, toNode);

        if (tmp == nullptr)
        {
            if (DebugLevel > 2) cout << "WARNING: Nodes are already disconnected." << endl;
            return ReturnWarning;
        }

        else
        {
            if (tmp->next != nullptr) tmp->next->prev = tmp->prev;
            if (tmp->prev != nullptr) tmp->prev->next = tmp->next;
            else this->edges[fromNode] = nullptr;
        }
        delete tmp;

        if (DebugLevel > 3) cout << "Edge removed." << endl;
        return ReturnSuccess;
    }

    vector<int> neighbors(int fromNode)
    {
        if(!isValid(fromNode)) return {};

        if(hasEdges(fromNode))
        {
                vector<int> neigh;
                MyLibrary::detail::Node<edge>* tmp = this->edges[fromNode]->h();
                
                while(tmp != nullptr)
                {
                    neigh.insert(neigh.end(), tmp->data->toNode->vertice);
                    tmp = tmp->next;
                }
                return neigh;
        }
        else return {};
    }

    void print()
    {
        for (int v = 0; v < this->numOfVertices; v++){
            cout << v << ": ";
            if(hasEdges(v)){
                MyLibrary::detail::Node<edge>* tmp = this->edges[v]->h();
                
                while(tmp != nullptr)
                {
                    cout << "->(" << tmp->data->toNode->vertice <<", " << tmp->data->cost <<"),";
                    tmp = tmp->next;
                }
            }
            cout << endl;
        }
    }

    ~Graph()
    {
        if (DebugLevel > 3) cout << "Graph Class destructor called." << endl;

        for (int v = 0; v < this->numOfVertices; v++)
        {
            if(this->edges[v] != nullptr) 
            {
                MyLibrary::detail::Node<edge>* tmp = this->edges[v]->h();
                
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

};

class PriorityQueue
{
    private:
    MyLibrary::LinkedList<vertice>* queue;

    vertice* newVertice(int v, int val = -1)
    {
        vertice* result = new vertice{ .vertice = v, .value = val };

        return result;
    }

    ReturnStatus insertNodeSorted(MyLibrary::detail::Node<vertice>* nodeToSort)
    {
        MyLibrary::detail::Node<vertice>* tmp = this->queue->h();


        while(tmp != nullptr)
        {
            if(nodeToSort->data->value < tmp->data->value)
            {

                if(tmp == this->queue->h()) this->queue->prependNode(nodeToSort);
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




    public:
    PriorityQueue(MyLibrary::LinkedList<vertice>* head = nullptr):queue(head)
    {
        if (DebugLevel > 3) cout << "PriorityQueue Class constructor called." << endl;
    }

    int size(){ this->queue->size(); }

    ReturnStatus chgPriority(int v, int val, bool smallest = true)
    {
        MyLibrary::detail::Node<vertice>* chgNode = contains(v);

        if(chgNode == nullptr)
        {
            if (DebugLevel > 3) cout << "Vertice is not on the list." << endl;
            return ReturnError;
        }

        if (chgNode->data->value == val)
        {
            if (DebugLevel > 3) cout << "Value remains the same." << endl;
            return ReturnWarning;
        }  

        if (chgNode->data->value < val && smallest)
        {
            if (DebugLevel > 3) cout << "Old value is smaller." << endl;
            return ReturnWarning;
        }

        chgNode->data->value = val;
        if(chgNode->prev != nullptr) chgNode->prev->next = chgNode->next;
        else this->queue->setHeadPointer(chgNode->next);
        if(chgNode->next != nullptr) chgNode->next->prev = chgNode->prev;

        return insertNodeSorted(chgNode);

    }

    MyLibrary::detail::Node<vertice>* contains(int v)
    {
        MyLibrary::detail::Node<vertice>* tmp = this->queue->h();
        
        while(true)
        {
            if (tmp->data->vertice == v)
            {
                if (DebugLevel > 3) cout << "Vertice " << v << " found in queue." << endl;
                return tmp;
            }
            if (tmp->next == nullptr) break;
            else tmp = tmp->next;
        }
        if (DebugLevel > 1) cout << "Vertice " << v << " not found in queue." << endl;

        return nullptr;  
    }

    vertice* top(){ return this->queue->h()->data; }

    ReturnStatus insert(int v, int val)
    {
        if(this->queue == nullptr)
        {
            this->queue = new MyLibrary::LinkedList<vertice>;
            this->queue->prepend(newVertice(v, val));

            if (DebugLevel > 3) cout << "PQ: First element added." << endl;

            return ReturnSuccess;
        }

        if(contains(v) != nullptr)
        {
            if (DebugLevel > 3) cout << "Vertice already exists. Changing priority..." << endl;
            return chgPriority(v, val);
        }

        return insertNodeSorted(this->queue->newNode(newVertice(v, val)));
    }

    ReturnStatus minPriority()
    {
        return this->queue->popHead();
    }

    ReturnStatus remove(int v)
    {
        MyLibrary::detail::Node<vertice>* tmp = contains(v);
        if(tmp == nullptr) return ReturnNotFound;

        else
        {
            if (tmp->next != nullptr) tmp->next->prev = tmp->prev;
            if (tmp->prev != nullptr) tmp->prev->next = tmp->next;
            else this->queue = nullptr;
        }
        delete tmp;
        return ReturnSuccess;
    }
    
    void print()
    {
        MyLibrary::detail::Node<vertice>* tmp = this->queue->h();
        
        while(tmp != nullptr)
        {
            cout << "(" << tmp->data->vertice <<"," << tmp->data->value << "), ";
            tmp = tmp->next;
        }
        cout << endl;
    }

    ~PriorityQueue()
    {
        if (DebugLevel > 3) cout << "PriorityQueue Class destructor called." << endl;

        MyLibrary::detail::Node<vertice>* tmp = this->queue->h();
        
        while(tmp != nullptr)
        {
            delete tmp->data;
            tmp = tmp->next;
        }

        delete queue;

    }
};

class ShortestPath
{
    private:
    Graph* g;
    PriorityQueue* q;
    vector<int> v;

    // void print(int fromNode, int toNode)
    // {
    //     MyLibrary::detail::Node<edge>* tmp = g->
    // }

    ReturnStatus recursivePath(int fromNode, int toNode, int cost, int lastNode, bool firstNode = true)
    {
        vector<int> neigh = g->neighbors(fromNode);
        if(neigh.empty()) return ReturnEndOfLoop;

        MyLibrary::detail::Node<edge>* tmp;

        if(!firstNode)
        {
            cost+= g->getEdgeValue(lastNode, fromNode);
            cout << "Cost updated: " << cost << endl;
        }
        
        int status = q->insert(fromNode, cost);
        cout<< "Node: " << fromNode << " cost: " << cost << endl;

        if (status == ReturnWarning) return ReturnWarning;

        if(fromNode == toNode) 
        {
            return ReturnSuccess;
        }

        cout << "Last Node: " << lastNode << " From Node: " << fromNode << " bool: " << firstNode << endl;
        tmp = g->isAdjacent(fromNode, neigh[0]);

        while(tmp != nullptr)
        {
            cout << "Inside " << fromNode << " neighbors." << endl;

            int nextNode = tmp->data->toNode->vertice;

            if(recursivePath(nextNode, toNode, cost, fromNode, false) == ReturnSuccess)
            {
                v.insert(v.begin(), fromNode);
                break;
            }

            tmp = tmp->next;
        }
        cout << "End of " << fromNode << " neighbors." << endl;
        return ReturnEndOfLoop;
    }

    public:
    ShortestPath(Graph* g, PriorityQueue* q = new PriorityQueue, vector<int> v = {}):g(g), q(q), v(v){}

    ReturnStatus path(int fromNode, int toNode)
    {
        if ((!g->isValid(fromNode) || !g->isValid(toNode)) || !g->hasEdges(fromNode))
        {
            return ReturnError;

        }

        int cost = 0;

        recursivePath(fromNode, toNode, cost, fromNode);

        if(v.size() > 1)
        {
            v.insert(v.begin(), fromNode);
            v.insert(v.end(), toNode);
        }

        return ReturnSuccess;
    }

    void printQueue()
    {
        if(q != nullptr) q->print();
    }

    void printPath()
    {
        if(v.empty()) return;
        
        for(auto x: v)
        {
            cout << x << "->";
        }
        cout << endl;
    }

    ~ShortestPath()
    {
        if (DebugLevelShortestPath > 0) cout << "ShortestPath Class destructor called." << endl;
        if(q!= nullptr) delete q;
    }

};

int main()
{
    // Graph g(5);
    
    // cout << "Number of vertices: " << g.v() << endl;
    // cout << "Number of edges of node 0: " << g.e(0) << endl;

    // cout << "Non adjacency test on vertice 0: ";
    // g.isAdjacent(0, 1);

    // cout << "Adjacency test: " << endl;
    // g.addEdge(0, 1);
    // g.print();
    // g.isAdjacent(0, 1);

    // cout << "Remove test: " << endl;
    // g.removeEdge(0, 1);
    // g.print();
    // g.isAdjacent(0, 1);

    // g.addEdge(0, 1, 1);
    // g.addEdge(0, 2, 1);
    // g.addEdge(0, 3, 2);
    // g.addEdge(0, 4, 3);
    // g.print();
    // cout << "Number of edges of node 0: " << g.e(0) << endl;


    // cout << "Get edge Value test: " << g.getEdgeValue(0, 1) << endl;

    // cout << "Set edge Value (to 2) test." << endl;
    // g.setEdgeValue(0, 1, 3);
    // cout << "Edge Value: " << g.getEdgeValue(0, 1) << endl;
    // g.print();

    // PriorityQueue q;

    // q.insert(3,3);
    // q.insert(5,2);
    // q.insert(7,4);

    // q.print();

    // q.insert(7,1);

    // q.print();


    Graph g(10);

    g.addEdge(0,1,4);
    g.addEdge(0,2,3);
    g.addEdge(0,4,7);
    g.addEdge(0,6,1);

    g.addEdge(1,3,1);

    g.addEdge(2,4,4);
    g.addEdge(2,0,3);

    g.addEdge(3,5,1);

    g.addEdge(4,5,1);
    g.addEdge(4,6,5);
    g.addEdge(4,8,3);

    g.addEdge(5,7,2);
    g.addEdge(5,8,4);

    g.addEdge(6,9,1);

    g.addEdge(7,5,2);
    g.addEdge(7,8,3);

    g.addEdge(8,6,5);

    g.print();

    ShortestPath sp(&g);

    sp.path(0,8);
    sp.printQueue();
    sp.printPath();

    return 0;
}
