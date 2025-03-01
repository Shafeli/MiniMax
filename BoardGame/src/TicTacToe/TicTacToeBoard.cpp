// TicTacToeBoard.cpp
#include "TicTacToeBoard.h"
#include <iostream>

TicTacToeBoard::TicTacToeBoard()
    : m_currentPlayer(Player::kX)
{
    //
}

void TicTacToeBoard::StartGame()
{
    m_currentState.Clear();
}

void TicTacToeBoard::MakeMove(const Move& move)
{
    m_currentState.MakeMove(move);
    m_currentPlayer = (m_currentPlayer == Player::kX ? Player::kO: Player::kX);
}

void TicTacToeBoard::PrintWinner() const
{
    switch (GetWinner())
    {
        case 0:
            std::cout << "\n*** Tie ***\n";
            break;

        case 1:
            std::cout << "*** X Has Won! ***\n";
            break;

        case 2:
            std::cout << "*** O Has Won! ***\n";
            break;

        default:
            std::cout << "*** ERROR ***\n";
            break;
    }
}

void TicTacToeBoard::Draw() const
{
    m_currentState.Draw();

    if (m_currentPlayer == Player::kX)
        std::cout << "X to move.\n";
    else if (m_currentPlayer == Player::kO)
        std::cout << "O to move.\n";
    else
        std::cout << "Unknown move...\n";
}

Board* TicTacToeBoard::Clone() const
{
    TicTacToeBoard* pClone = new TicTacToeBoard(*this);  // copy-construct a new board
    return pClone;
}

GameStateHashType TicTacToeBoard::GetBoardHash() const
{
    GameStateHashType stateHash = m_currentState.GetHash();
    if (m_currentPlayer == Player::kX)
        stateHash[kHashBitsetSize - 1] = true;
    return stateHash;
}

