// ConnectFourBoard.cpp
#pragma once

#include "ConnectFourBoard.h"
#include <iostream>

ConnectFourBoard::ConnectFourBoard()
    : m_currentPlayer(Player::kRed)
{
    //
}

void ConnectFourBoard::StartGame()
{
    m_currentState.Clear();
}

void ConnectFourBoard::MakeMove(const Move& move)
{
    m_currentState.MakeMove(move);
    m_currentPlayer = (m_currentPlayer == Player::kRed ? Player::kBlack : Player::kRed);
}

Moves ConnectFourBoard::GetLegalMoves() const
{
    Moves moves;

    // get all columns that are valid to make moves from
    std::vector<bool> validColumns = std::move(m_currentState.GetValidColumns());

    // fill out the moves array
    moves.reserve(ConnectFourGameState::kMaxMoves);
    for (int i = 0; i < (int)validColumns.size(); ++i)
    {
        if (validColumns[i])
            moves.emplace_back((int)m_currentPlayer, i);
    }

    return moves;
}

int ConnectFourBoard::GetWinner() const
{
    return m_currentState.CheckForWinner();
}

void ConnectFourBoard::PrintWinner() const
{
    switch (GetWinner())
    {
        case 0:
            std::cout << "\n*** Tie ***\n";
            break;

        case 1:
            std::cout << "*** Red (X) Has Won! ***\n";
            break;

        case 2:
            std::cout << "*** Black (O) Has Won! ***\n";
            break;

        default:
            std::cout << "*** ERROR ***\n";
            break;
    }
}

void ConnectFourBoard::Draw() const
{
    m_currentState.Draw();

    if (m_currentPlayer == Player::kRed)
        std::cout << "Red (X) to move.\n";
    else if (m_currentPlayer == Player::kBlack)
        std::cout << "Black (O) to move.\n";
    else
        std::cout << "Unknown move...\n";
}

Board* ConnectFourBoard::Clone() const
{
    ConnectFourBoard* pClone = new ConnectFourBoard(*this);  // copy-construct a new board
    return pClone;
}

GameStateHashType ConnectFourBoard::GetBoardHash() const
{
    GameStateHashType stateHash = m_currentState.GetHash();
    if (m_currentPlayer == Player::kRed)
        stateHash[kHashBitsetSize - 1] = true;
    return stateHash;
}
