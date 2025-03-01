// ConnectFourGameState.h
#pragma once

#include "../Interface/GameState.h"
#include "../Interface/Move.h"
#include "ConnectFourTypes.h"

class ConnectFourGameState : public GameState
{
    static constexpr int kBoardWidth = 7;
    static constexpr int kBoardHeight = 6;
    static constexpr size_t kBoardArraySize = kBoardWidth * kBoardHeight;
    static constexpr int kWinCount = 4;  // how many we need in a row

public:
    static constexpr int kMaxMoves = kBoardWidth;

private:
    CellState m_cells[kBoardArraySize];

public:
    ConnectFourGameState();
    ConnectFourGameState(const ConnectFourGameState& right);
    ConnectFourGameState(ConnectFourGameState&& right) = delete;
    ConnectFourGameState& operator=(const ConnectFourGameState& right);
    ConnectFourGameState& operator=(ConnectFourGameState&& right) = delete;

    void Clear();

    int CheckForWinner() const;
    void MakeMove(const Move& move);
    std::vector<bool> GetValidColumns() const;
    void Draw() const;

    virtual GameStateHashType GetHash() const override;

private:
    CellState CheckForWinAt(int x, int y) const;
    CellState CheckForConnection(int x, int y, int dx, int dy) const;
    int GetIndexFromPos(int x, int y) const { return (y * kBoardWidth) + x; }
    void CopyState(const ConnectFourGameState& right);
};
