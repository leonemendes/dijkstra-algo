#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Library headerfile
#include "defs.hpp"
#include "graph.hpp"


namespace ipc
{
    class PriorityQueue
    {
        private:
        LinkedList<detail::vertice>* queue;

        detail::vertice* newVertice(int v, int fromV = -1, int val = -1);

        ReturnStatus insertNodeSorted(detail::Node<detail::vertice>* nodeToSort);

        public:
        PriorityQueue(LinkedList<detail::vertice>* head = nullptr);

        int size();

        ReturnStatus chgPriority(int v, int fromV, int val, bool smallest = true);

        detail::Node<detail::vertice>* contains(int v);

        detail::vertice* top();

        ReturnStatus insert(int v, int fromV, int val);

        ReturnStatus minPriority();

        ReturnStatus remove(int v);
        
        void print();

        ~PriorityQueue();
    };

}

#endif