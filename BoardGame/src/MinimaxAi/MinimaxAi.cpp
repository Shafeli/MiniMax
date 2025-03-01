#include "MinimaxAi.h"

MinimaxAi::~MinimaxAi()
{
    //
}

Move MinimaxAi::FindBestMove()
{
    //
    std::vector<Move> legalMoves = m_pBoard->GetLegalMoves();

    Move bestMove{kAi, 0}; // default
    int bestScore = -kScoreInf;

    for (const Move& move : legalMoves)
    {
        // Clone board and apply move
        std::unique_ptr<Board> clonedBoard(m_pBoard->Clone());
        clonedBoard->MakeMove(move);

        // Evaluate move using Minimax
        int moveScore = Minimax(clonedBoard.get(), 0, false, -kScoreInf, kScoreInf);

        // If this move is better, store it
        if (moveScore > bestScore)
        {
            bestScore = moveScore;
            bestMove.boardIndex = move.boardIndex;
        }
    }

    return bestMove;
}
