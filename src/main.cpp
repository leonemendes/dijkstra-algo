#include <iostream>
#include <chrono>

#include "main.hpp"
#include "iplib.hpp"

// Calling namespace library functions
using namespace std::chrono;

using ipc::Graph;
using ipc::ShortestPath;
using ipc::MonteCarloGraph;
using ipc::MinSpanTree;
using ipc::Hex;

int main()
{
    auto start = high_resolution_clock::now();
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


    // Graph g(10);

    // g.addEdge(0,1,4);
    // g.addEdge(0,2,3);
    // g.addEdge(0,4,7);
    // g.addEdge(0,6,1);

    // g.addEdge(1,3,1);

    // g.addEdge(2,4,4);
    // g.addEdge(2,0,3);

    // g.addEdge(3,5,1);

    // g.addEdge(4,5,1);
    // g.addEdge(4,6,5);
    // g.addEdge(4,8,3);

    // g.addEdge(5,7,2);
    // g.addEdge(5,8,4);

    // g.addEdge(6,9,1);

    // g.addEdge(7,5,2);
    // g.addEdge(7,8,3);

    // g.addEdge(8,6,5);

    // g.print();

    // ShortestPath sp(&g);

    // sp.path(0,8);
    // sp.printPath();
    // cout << "Path cost:" << sp.pathCost() << endl;

    // MonteCarloGraph m(200, 0.07, false, true);

    // m.print();

    // ShortestPath sp(&m);

    // sp.path(12,142);
    // sp.printPath();
    // cout << "Path cost:" << sp.pathCost() << endl;

    // MinSpanTree mst(&m);

    // mst.treeGraph()->print();


    // Graph g(7, false);

    // g.addEdge(0,1,2);
    // g.addEdge(0,2,3);

    // g.addEdge(1,2,2);
    // g.addEdge(1,3,4);
    // g.addEdge(1,4,6);
    // g.addEdge(1,5,4);

    // g.addEdge(2,5,5);

    // g.addEdge(3,4,5);
    // g.addEdge(3,6,3);

    // g.addEdge(5,4,4);

    // g.addEdge(6,4,5);

    // g.print();

    // ShortestPath sp(&g);

    // sp.path(0,6);
    // sp.printPath();
    // cout << "Path cost:" << sp.pathCost() << endl;

    // MinSpanTree mst(&g);

    // mst.treeGraph()->print();

    Hex board(20);

    // board.print();
    board.printBoard();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duration time: " << duration.count() << "us" << endl;

    return 0;
}
