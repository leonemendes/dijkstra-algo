#include <iostream>
#include <chrono>

#include "main.hpp"

// From namespace
using std::cin;

// Calling namespace library functions
using namespace std::chrono;

using ipc::Graph;
using ipc::ShortestPath;
using ipc::MonteCarloGraph;
using ipc::MinSpanTree;
using ipc::Hex;

int main()
{
    int size, player = 1;
    pair<char,int> pos;

    cout << CoutColorStart + CoutColorBoldOn + CoutColorGreen << "HEX Game" << CoutColorEnd << endl;
    cout << "Set board size x (with 3 <= x <= 26): ";
    cin >> size;
    cout << "Creating a " << size << "x" << size << " board..." << endl;

    Hex board(size);
    if(!board.isValidSize(size)) return 0;
    cout << "Player 1: " << CoutColorStart + CoutColorBoldOn + CoutColorBlue <<  "Blue" << CoutColorEnd << endl;
    cout << "Player 2: " << CoutColorStart + CoutColorBoldOn + CoutColorRed <<  "Red" << CoutColorEnd << endl;

    auto gameStart = high_resolution_clock::now();
    board.printBoard();

    while(true)
    {
        auto start = high_resolution_clock::now();

        cout << "Player " << player << " turn. Set position: ";
        cin >> pos.first;
        cin >> pos.second;
        cout << endl;

        if(board.placeStone(pos, static_cast<HexColor>(player)) == ReturnError)
        {
            cout << "Position forbidden. Try again" << endl;
        }
        else player = (player == 1) ? 2 : 1;
        board.printBoard();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        cout << "Turn duration: " << duration.count() << "s" << endl;
    }

    auto gameStop = high_resolution_clock::now();
    auto gameDuration = duration_cast<minutes>(gameStop - gameStart);
    cout << "Duration time: " << gameDuration.count() << "m" << endl;

    return 0;
}
