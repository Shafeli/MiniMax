// ConnectFourGameState.cpp
#include "ConnectFourGameState.h"
#include <string.h>  // for memset()
#include <assert.h>
#include <iostream>  // :(

ConnectFourGameState::ConnectFourGameState()
{
    Clear();
}

ConnectFourGameState::ConnectFourGameState(const ConnectFourGameState& right)
{
    CopyState(right);
}

ConnectFourGameState& ConnectFourGameState::operator=(const ConnectFourGameState& right)
{
    if (this == &right)
        CopyState(right);
    return (*this);
}

GameStateHashType ConnectFourGameState::GetHash() const
{
    GameStateHashType stateHash;
    for (int i = 0; i < kBoardArraySize; ++i)
    {
        stateHash <<= 2;
        stateHash |= (static_cast<int>(m_cells[i]) & 0000'0007);
    }

    return stateHash;
}

void ConnectFourGameState::Clear()
{
    memset(m_cells, 0, sizeof(CellState) * kBoardArraySize);
}

int ConnectFourGameState::CheckForWinner() const
{
    for (int y = 0; y < kBoardHeight; ++y)
    {
        for (int x = 0; x < kBoardWidth; ++x)
        {
            int index = GetIndexFromPos(x, y);
            CellState result = CheckForWinAt(x, y);

            if (result != CellState::kEmpty)
                return (int)result;
        }
    }

    return 0;
}

void ConnectFourGameState::MakeMove(const Move& move)
{
    assert(move.player == 1 || move.player == 2);  // 1 == red, 2 == black
    assert(move.boardIndex >= 0 && move.boardIndex < kBoardWidth);  // the column to drop the piece

    for (int y = 0; y < kBoardHeight; ++y)
    {
        int index = GetIndexFromPos(move.boardIndex, y);
        if (m_cells[index] == CellState::kEmpty)
        {
            m_cells[index] = static_cast<CellState>(move.player);
            return;
        }
    }

    assert(0 && "Not enough rows.");
}

std::vector<bool> ConnectFourGameState::GetValidColumns() const
{
    std::vector<bool> outColumns = { false, false, false, false, false, false, false };

    for (int x = 0; x < kBoardWidth; ++x)
    {
        for (int y = 0; y < kBoardHeight; ++y)
        {
            int index = GetIndexFromPos(x, y);
            if (m_cells[index] == CellState::kEmpty)
            {
                outColumns[x] = true;
                break;
            }
        }
    }

    return outColumns;
}

void ConnectFourGameState::Draw() const
{
    for (int y = kBoardHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x < kBoardWidth; ++x)
        {
            int index = GetIndexFromPos(x, y);
            switch (m_cells[index])
            {
                case CellState::kEmpty:
                    std::cout << "_ ";
                    break;
                case CellState::kRed:
                    std::cout << "X ";
                    break;
                case CellState::kBlack:
                    std::cout << "O ";
                    break;
                default:
                    assert(0 && "Bad cell state");
                    break;
            }
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

CellState ConnectFourGameState::CheckForWinAt(int x, int y) const
{
    CellState result = CheckForConnection(x, y, 1, 0);
    if (result != CellState::kEmpty)
        return result;
    result = CheckForConnection(x, y, 0, 1);
    if (result != CellState::kEmpty)
        return result;
    result = CheckForConnection(x, y, 1, 1);
    if (result != CellState::kEmpty)
        return result;
    result = CheckForConnection(x, y, 1, -1);
    if (result != CellState::kEmpty)
        return result;

    return CellState::kEmpty;
}

CellState ConnectFourGameState::CheckForConnection(int x, int y, int dx, int dy) const
{
    int index = GetIndexFromPos(x, y);
    const CellState testState = m_cells[index];

    for (int i = 1; i < kWinCount; ++i)
    {
        // recalculate x & y for the new position
        int testX = x + i * dx;
        int testY = y + i * dy;

        // Make sure they're in bounds.  If not, this can't be a connection.
        if (testX < 0 || testX >= kBoardWidth)
            return CellState::kEmpty;
        if (testY < 0 || testY >= kBoardHeight)
            return CellState::kEmpty;

        // if we get here, check to see if this could possibly be another connection
        index = GetIndexFromPos(testX, testY);
        if (m_cells[index] != testState)
            return CellState::kEmpty;
    }

    // If we get here, we have a connection.  Return the cellstate.
    return testState;
}

void ConnectFourGameState::CopyState(const ConnectFourGameState& right)
{
    memcpy(m_cells, right.m_cells, sizeof(CellState) * kBoardArraySize);
}
