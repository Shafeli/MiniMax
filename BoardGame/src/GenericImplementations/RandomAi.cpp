// RandomAi.cpp
#include "RandomAi.h"
#include "../Interface/Board.h"

Move RandomAi::FindBestMove()
{
    Moves moves(m_pBoard->GetLegalMoves());

    int choice = rand() % moves.size();
    return moves[choice];
}
