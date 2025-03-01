// TicTacToeTypes.h
#pragma once

enum class TicTacToeCellState : unsigned char
{
    kEmpty = 0,
    kX = 1,  // must be 1, since it corresponds to player 1
    kO = 2,  // must be 2, since it corresponds to player 2
};
