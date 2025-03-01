// TicTacToeGameState.cpp
#include "TicTacToeGameState.h"
#include "../Interface/Types.h"
#include <iostream>
#include <assert.h>
#include <string>

#define SHOWINDEXES 1

TicTacToeGameState::TicTacToeGameState()
{
    Clear();
}

void TicTacToeGameState::Clear()
{
    memset(m_cells, 0, sizeof(TicTacToeCellState) * kBoardArraySize);
}

int TicTacToeGameState::CheckForWinner() const
{
    // rows
    for (int i = 0; i < kBoardHeight; ++i)
    {
        int baseIndex = i * kBoardWidth;
        if (m_cells[baseIndex] != TicTacToeCellState::kEmpty && m_cells[baseIndex] == m_cells[baseIndex + 1] && m_cells[baseIndex] == m_cells[baseIndex + 2])
            return static_cast<int>(m_cells[baseIndex + i]);
    }

    // columns
    for (int i = 0; i < kBoardWidth; ++i)
    {
        if (m_cells[i] != TicTacToeCellState::kEmpty && m_cells[i] == m_cells[i + kBoardWidth] && m_cells[i] == m_cells[i + (kBoardWidth * 2)])
            return static_cast<int>(m_cells[i]);
    }

    // diag
    if (m_cells[0] != TicTacToeCellState::kEmpty && m_cells[0] == m_cells[kBoardWidth + 1] && m_cells[0] == m_cells[(kBoardWidth * 2) + 2])
        return static_cast<int>(m_cells[0]);
    if (m_cells[kBoardWidth - 1] != TicTacToeCellState::kEmpty && m_cells[kBoardWidth - 1] == m_cells[kBoardWidth + 1] && m_cells[kBoardWidth - 1] == m_cells[kBoardWidth * 2])
        return static_cast<int>(m_cells[kBoardWidth - 1]);

    return 0;
}

void TicTacToeGameState::MakeMove(const Move& move)
{
    assert(move.player == 1 || move.player == 2);  // 1 == X, 2 == O
    assert(move.boardIndex >= 0 && move.boardIndex < kBoardArraySize);  // board index
    assert(m_cells[move.boardIndex] == TicTacToeCellState::kEmpty);  // must be a blank square

    m_cells[move.boardIndex] = static_cast<TicTacToeCellState>(move.player);
}

void TicTacToeGameState::Draw() const
{
    for (int y = 0; y < kBoardHeight; ++y)
    {
        for (int x = 0; x < kBoardWidth; ++x)
        {
            int index = GetIndexFromPos(x, y);
            switch (m_cells[index])
            {
            case TicTacToeCellState::kEmpty:
#if  SHOWINDEXES
                    std::cout << std::to_string(index + 1) + " ";
#else
                std::cout << "_ ";
#endif

                    break;
                case TicTacToeCellState::kX:
                    std::cout << "X ";
                    break;
                case TicTacToeCellState::kO:
                    std::cout << "O ";
                    break;
                default:
                    assert(0 && "Bad cell state");
                    break;
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

Moves TicTacToeGameState::GetLegalMoves(int playerIndex) const
{
    Moves moves;
    moves.reserve(kMaxMoves);

    for (int i = 0; i < kBoardArraySize; ++i)
    {
        if (m_cells[i] == TicTacToeCellState::kEmpty)
            moves.emplace_back(playerIndex, i);
    }

    return moves;
}

GameStateHashType TicTacToeGameState::GetHash() const
{
    unsigned long long hash = 0;
    for (int i = 0; i < kBoardArraySize; ++i)
    {
        unsigned char rawVal = static_cast<unsigned char>(m_cells[i]);
        hash |= (rawVal << i * 2);
    }
    return hash;
}
