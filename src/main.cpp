#include <iostream>
#include <chrono>
#include <limits>

#include "main.hpp"

// From namespace
using std::cin;
using std::numeric_limits;
using std::streamsize;

// Calling namespace library functions
using namespace std::chrono;

using ipc::Graph;
using ipc::MonteCarloGraph;
using ipc::MinSpanTree;
using ipc::Hex;

int main()
{
    bool againstPc, pcAgainstPc;
    int size;
    ipc::detail::HexColor player = ipc::detail::HexColor::Blue;
    pair<char,int> pos;
    char ans;

    cout << CoutColorStart + CoutColorBoldOn + CoutColorGreen << "HEX Game" << CoutColorEnd << endl;
    cout << "Set board size x (with 3 <= x <= 26): ";
    cin >> size;
    cout << "Creating a " << size << "x" << size << " board..." << endl;

    Hex board(size);

    if(!board.isValidSize(size)) return 0;
    cout << "Player 1: " << CoutColorStart + CoutColorBoldOn + CoutColorBlue <<  "Blue" << CoutColorEnd << endl;
    cout << "Player 2: " << CoutColorStart + CoutColorBoldOn + CoutColorRed <<  "Red" << CoutColorEnd << endl;
    cout << "Play against PC (Y/N)?: ";
    cin >> ans;
    againstPc = (ans == 'Y') ? true : false;
    cout << "PC against PC (Y/N)?: ";
    cin >> ans;
    pcAgainstPc = (ans == 'Y') ? true : false;

    auto gameStart = high_resolution_clock::now();


    board.printBoard();

    while(true)
    {
        auto start = high_resolution_clock::now();

        if(againstPc && player == ipc::detail::HexColor::Red)
        {
            cout << "Player " << static_cast<int>(player) - 1 << " turn. Set position: ";
            cout << endl;
            board.smartMove(player, ipc::detail::PcLevel::Easy);
            player = ipc::detail::HexColor::Blue;

        }
        else if (pcAgainstPc && player == ipc::detail::HexColor::Blue)
        {
            cout << "Player " << static_cast<int>(player) - 1 << " turn. Set position: ";
            cout << endl;
            board.smartMove(player, ipc::detail::PcLevel::Easy);
            player = ipc::detail::HexColor::Red;

        }
        else
        {
            cout << "Player " << static_cast<int>(player) - 1 << " turn. Set position: ";
            cin >> pos.first;
            cin >> pos.second;
            cout << endl;

            if(board.placeStone(pos, player) == ReturnError)
            {
                cout << "Position forbidden. Try again" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else player = ipc::detail::HexColor::Red;
        }

        board.printBoard();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        cout << "Turn duration: " << duration.count() << "s" << endl;

        if(board.endGame) break;

    }

    board.gameReport();

    auto gameStop = high_resolution_clock::now();
    auto gameDuration = duration_cast<seconds>(gameStop - gameStart);
    cout << "Duration time: " << gameDuration.count() << "S" << endl;

    return 0;
}
