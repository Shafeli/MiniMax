// Move.h
#pragma once

#include <vector>

struct Move
{
    int player;
    int boardIndex;

    Move(int _player, int _boardIndex) : player(_player), boardIndex(_boardIndex) { }
    bool operator==(const Move& move) const;
    bool operator!=(const Move& move) const;
};

inline bool Move::operator==(const Move& move) const
{
    return player == move.player && boardIndex == move.boardIndex;
}

inline bool Move::operator!=(const Move& move) const
{
    return !(*this == move);
}

using Moves = std::vector<Move>;
