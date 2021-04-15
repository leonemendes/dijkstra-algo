#ifndef GRAPH_H
#define GRAPH_H

// Libraries
#include <iostream>
#include <vector>

// Library headerfile
#include "defs.hpp"
#include "linked_list.hpp"


// Using from other namespaces
using std::vector;
using std::cout;
using std::endl;

namespace ipc
{
    namespace detail
    {
        struct vertice
        {
            int vertice, fromVertice, value;
        };

        struct edge
        {
            struct vertice* fromNode;
            struct vertice* toNode;

            int value;
        };
    }

    class Graph
    {
        private:
        detail::vertice* vertices;
        LinkedList<detail::edge>** edges;
        int numOfVertices;
        bool isDirected;

        void initVertices(int numOfVertices, int value = -1);

        void initEdges(int numOfVertices);

        ReturnStatus addEdgeSorted(detail::Node<detail::edge>* nodeToSort);

        public:
        Graph(int numOfVertices, int verticeBaseCost = -1, bool isDirected = true);

        Graph();

        ReturnStatus init(int numOfVertices, int verticeBaseCost = -1, bool isDirected = true);

        bool isDirectedFlag();

        int v();

        bool isValid(int v);

        bool hasEdges(int v);

        int e(int fromNode);

        int cost(int fromNode);

        ReturnStatus setNodeValue(int fromNode, int value);


        int cost(int fromNode, int toNode);

        ReturnStatus setEdgeValue(int fromNode, int toNode, int value, bool directed = true);

        detail::edge* newEdge(int fromNode, int toNode, int value = 1);

        detail::Node<detail::edge>* isAdjacent(int fromNode, int toNode);

        ReturnStatus addEdge(int fromNode, int toNode, int value = 1, bool directed = true);

        ReturnStatus removeEdge(int fromNode, int toNode, bool directed = true);

        vector<int> neighbors(int fromNode);

        void print();

        ~Graph();

    };
}



#endif