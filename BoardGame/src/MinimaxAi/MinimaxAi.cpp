#include "MinimaxAi.h"

#include <future>

MinimaxAi::~MinimaxAi()
{
    //
}

Move MinimaxAi::FindBestMove()
{
    ++roundCount;
    if (roundCount >= expandCounterMax)
    {
        std::cout << "AI Expanding Depth!\n";
        ++controlDepth;

        if (controlDepth >= kMaxDepth)
        {
            std::cout << "AI at mox Depth!\n";
            controlDepth = kMaxDepth;
        }
    }

    auto startTime = std::chrono::steady_clock::now();
    constexpr auto timeLimit = std::chrono::milliseconds(1000);

    Move bestMove = { -1, -1 }; // Invalid move

    // Take the easy win
    // Check for immediate winning move
    Move winningMove = DetectImmediateMove(kAi);
    if (winningMove.boardIndex != -1) return winningMove; // Check explicitly

    // Take an easy block
    // Check for immediate blocking move
    Move blockingMove = DetectImmediateMove(kPlayer);
    if (blockingMove.boardIndex != -1) return blockingMove; // Check explicitly

    
    int bestScore = -kScoreInf;

    for (int depth = 1; depth <= kMaxDepth; ++depth)
    {
        std::vector<Move> legalMoves = m_pBoard->GetLegalMoves();

        int alpha = -kScoreInf, beta = kScoreInf;

        for (const Move& move : legalMoves)
        {
            if (move.boardIndex == 4) // center
            {
                bestMove.boardIndex = 4;
                bestMove.player = kAi;
                return bestMove;
            }

            std::unique_ptr<Board> clonedBoard(m_pBoard->Clone());
            clonedBoard->MakeMove(move);
            int moveScore = Minimax(clonedBoard.get(), depth, false, alpha, beta);

            if (moveScore > bestScore)
            {
                bestScore = moveScore;
                bestMove = move;
            }

            auto now = std::chrono::steady_clock::now();
            if (now - startTime > timeLimit)
            {
                std::cout << "Time Limit Reached\n";
                return bestMove;  // Stop searching if time runs out
            }
        }
    }

    std::cout << "Max Depth Reached\n";

    return bestMove;
}

Move MinimaxAi::DetectImmediateMove(int player)
{
    std::vector<Move> legalMoves = m_pBoard->GetLegalMoves();

    for (Move& move : legalMoves)
    {
        std::unique_ptr<Board> clonedBoard(m_pBoard->Clone());
        Move nextMove = move;
        nextMove.player = player;

        clonedBoard->MakeMove(nextMove);

        if (clonedBoard->GetWinner() == player)
        {
            return move;
        }
    }

    return Move(-1, -1); // return an invalid move
}
