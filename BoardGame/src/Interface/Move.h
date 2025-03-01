// Move.h
#pragma once

#include <vector>

struct Move
{
    int player;
    int boardIndex;

    Move(int _player, int _boardIndex) : player(_player), boardIndex(_boardIndex) { }
};

using Moves = std::vector<Move>;
