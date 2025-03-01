// Board.h
#pragma once

#include "Move.h"
#include "Types.h"

class Board
{
public:
    virtual ~Board() = default;

    // Resets the game to the starting position.
    virtual void StartGame() = 0;

    // Returns the current player index.  This value will be >= 1.
    virtual int GetCurrentPlayer() const = 0;

    // Gets the maximum number of choices the player has.
    virtual int GetMaxMoves() const = 0;

    // Makes a single move.
    virtual void MakeMove(const Move& move) = 0;

    // Returns all legal moves from the current position.
    virtual Moves GetLegalMoves() const = 0;

    // Returns the player index if there's a winner.  If not, it will return 0 if the game is still going on and -1 if 
    // there's a tie.
    virtual int GetWinner() const = 0;

    // Prints the winner message.
    virtual void PrintWinner() const = 0;

    // Renders the board.
    virtual void Draw() const = 0;

    // Clones the game board.
    virtual Board* Clone() const = 0;

    // Returns a unique hash for this board.
    virtual GameStateHashType GetBoardHash() const = 0;
};
