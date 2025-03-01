// Application.h
#pragma once

// If 1, the game is tic-tac-toe.  If 0, it is connect four.
#define PLAY_TIC_TAC_TOE 1

#if PLAY_TIC_TAC_TOE
    #include "../TicTacToe/TicTacToeBoard.h"
#else
    #include "../ConnectFour/ConnectFourBoard.h"
#endif

#include "../GenericImplementations/RandomAi.h"

class Application
{
#if PLAY_TIC_TAC_TOE
    TicTacToeBoard m_board;
#else
    ConnectFourBoard m_board;
#endif

    RandomAi m_ai;  // TODO: Replace this with your AI implementation

public:
    Application();

    void Run();

private:
    void ProcessPlayerMove(int playerIndex = 1);
    void ProcessAiMove();
    bool CheckForWinner() const;
};

