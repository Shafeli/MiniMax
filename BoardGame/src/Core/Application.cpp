// Application.cpp
#include "Application.h"
#include "../Interface/Move.h"

#include <iostream>
#include <time.h>
#include <conio.h>

#define TWO_HUMAN_PLAYERS 0  // set this to 1 in order to have two human players (turns off AI)


//---------------------------------------------------------------------------------------------------------------------
// Constructor.
//---------------------------------------------------------------------------------------------------------------------
Application::Application()
    : m_ai(&m_board)
{
    srand((unsigned int)time(0));
}

//---------------------------------------------------------------------------------------------------------------------
// Runs the main loop of the application.
//---------------------------------------------------------------------------------------------------------------------
void Application::Run()
{
    while (true)
    {
        system("cls");
        m_board.Draw();

        // player move
        ProcessPlayerMove();
        m_board.Draw();

        // check for a winner
        if (CheckForWinner())
            break;

        // second player move
#if TWO_HUMAN_PLAYERS
        ProcessPlayerMove(2);
#else
        ProcessAiMove();
#endif

        // check for a winner
        if (CheckForWinner())
            break;
    }
}

//---------------------------------------------------------------------------------------------------------------------
// Processes the human player's move.  This handles all the input and validation.
//      -playerIndex:   The index of the player making the move.  Defaults to 1.
//---------------------------------------------------------------------------------------------------------------------
void Application::ProcessPlayerMove(int playerIndex /*= 1*/)
{
    char choice = 0;

    while (choice < '1' || choice > '9')
        choice = _getch();
    Move playerMove(playerIndex, (choice & 0x0000000f) - 1);  // convert to decimal; using -1 because it's an index
    m_board.MakeMove(playerMove);
}

//---------------------------------------------------------------------------------------------------------------------
// Processes the AI player's move.
//---------------------------------------------------------------------------------------------------------------------
void Application::ProcessAiMove()
{
    Move opponentMove = m_ai.FindBestMove();

    m_board.MakeMove(opponentMove);
}

//---------------------------------------------------------------------------------------------------------------------
// Checks to see if there's a winner and prints out the info if there is.
//      -return:    true if there's a winner, false if not.
//---------------------------------------------------------------------------------------------------------------------
bool Application::CheckForWinner() const
{
    int winner = m_board.GetWinner();
    if (winner != 0)
    {
        m_board.Draw();
        m_board.PrintWinner();
        return true;
    }

    return false;
}
