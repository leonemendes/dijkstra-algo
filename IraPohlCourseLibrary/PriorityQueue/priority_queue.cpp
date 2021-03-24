#include "priority_queue.hpp"

ipc::LinkedList<ipc::detail::vertice>* queue;

ipc::detail::vertice* ipc::PriorityQueue::newVertice(int v, int fromV, int val)
{
    ipc::detail::vertice* result = new ipc::detail::vertice{ .vertice = v, .fromVertice = fromV, .value = val };

    return result;
}

ReturnStatus ipc::PriorityQueue::insertNodeSorted(ipc::detail::Node<ipc::detail::vertice>* nodeToSort)
{
    ipc::detail::Node<ipc::detail::vertice>* tmp = this->queue->h();


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

ipc::PriorityQueue::PriorityQueue(LinkedList<ipc::detail::vertice>* head):queue(head)
{
    if (DebugLevelPq > 3) cout << "PriorityQueue Class constructor called." << endl;
}

int ipc::PriorityQueue::size(){ return this->queue->size(); }

ReturnStatus ipc::PriorityQueue::chgPriority(int v, int fromV, int val, bool smallest)
{
    ipc::detail::Node<ipc::detail::vertice>* chgNode = ipc::PriorityQueue::contains(v);

    if(chgNode == nullptr)
    {
        if (DebugLevelPq > 3) cout << "Vertice is not on the list." << endl;
        return ReturnError;
    }

    if (chgNode->data->value == val)
    {
        if (DebugLevelPq > 3) cout << "Value remains the same." << endl;
        return ReturnWarning;
    }  

    if (chgNode->data->value < val && smallest)
    {
        if (DebugLevelPq > 3) cout << "Old value is smaller." << endl;
        return ReturnWarning;
    }

    chgNode->data->value = val;
    chgNode->data->fromVertice = fromV;
    if(chgNode->prev != nullptr) chgNode->prev->next = chgNode->next;
    else this->queue->setHeadPointer(chgNode->next);
    if(chgNode->next != nullptr) chgNode->next->prev = chgNode->prev;

    return ipc::PriorityQueue::insertNodeSorted(chgNode);

}

ipc::detail::Node<ipc::detail::vertice>* ipc::PriorityQueue::contains(int v)
{
    if (this->queue == nullptr) return nullptr;
    ipc::detail::Node<ipc::detail::vertice>* tmp = this->queue->h();
    
    while(tmp != nullptr)
    {
        if (tmp->data->vertice == v)
        {
            if (DebugLevelPq > 3) cout << "Vertice " << v << " found in queue." << endl;
            return tmp;
        }
        else tmp = tmp->next;
    }
    if (DebugLevelPq > 1) cout << "Vertice " << v << " not found in queue." << endl;

    return nullptr;  
}

ipc::detail::vertice* ipc::PriorityQueue::top(){ return this->queue->h()->data; }

ReturnStatus ipc::PriorityQueue::insert(int v, int fromV, int val)
{
    if(this->queue == nullptr)
    {
        this->queue = new LinkedList<ipc::detail::vertice>;
        this->queue->prepend(ipc::PriorityQueue::newVertice(v, fromV, val));

        if (DebugLevelPq > 3) cout << "PQ: First element added." << endl;

        return ReturnSuccess;
    }

    if(ipc::PriorityQueue::contains(v) != nullptr)
    {
        if (DebugLevelPq > 3) cout << "Vertice already exists. Changing priority..." << endl;
        return ipc::PriorityQueue::chgPriority(v, fromV, val);
    }

    return ipc::PriorityQueue::insertNodeSorted(this->queue->newNode(ipc::PriorityQueue::newVertice(v, fromV, val)));
}

ipc::detail::Node<ipc::detail::vertice>* ipc::PriorityQueue::minPriority()
{
    return this->queue->popHead();
}

ReturnStatus ipc::PriorityQueue::fromQueueToType(ipc::Graph* g)
{
    if(g == nullptr) return ReturnError;

    ipc::detail::Node<ipc::detail::vertice>* tmp = this->queue->h();

    while(tmp != nullptr)
    {
        if (DebugLevelPq > 3) cout << "From: " << tmp->data->fromVertice << " to: " << tmp->data->vertice << " cost: " << tmp->data->value << endl;
        g->addEdge(tmp->data->fromVertice, tmp->data->vertice, tmp->data->value);
        tmp = tmp->next;
    }
    
    return ReturnSuccess;
}

ReturnStatus ipc::PriorityQueue::fromQueueToType(vector<int> &v, int toNode, int fromNode)
{
    ipc::detail::Node<ipc::detail::vertice>* tmp = this->contains(toNode);
 
    while(tmp != nullptr)
    {
        v.insert(v.begin(), tmp->data->vertice);
        if (tmp->data->vertice == fromNode) break;

        tmp = this->contains(tmp->data->fromVertice);
    }

    return ReturnSuccess;
}

ReturnStatus ipc::PriorityQueue::remove(int v)
{
    ipc::detail::Node<ipc::detail::vertice>* tmp = ipc::PriorityQueue::contains(v);
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

void ipc::PriorityQueue::print()
{
    ipc::detail::Node<ipc::detail::vertice>* tmp = this->queue->h();
    
    while(tmp != nullptr)
    {
        cout << "(" << tmp->data->fromVertice <<"->" << tmp->data->vertice << ", " << tmp->data->value << "), ";
        tmp = tmp->next;
    }
    cout << endl;
}

ipc::PriorityQueue::~PriorityQueue()
{
    if (DebugLevelPq > 3) cout << "PriorityQueue Class destructor called." << endl;

    ipc::detail::Node<ipc::detail::vertice>* tmp = this->queue->h();
    
    while(tmp != nullptr)
    {
        delete tmp->data;
        tmp = tmp->next;
    }

    delete queue;

}
