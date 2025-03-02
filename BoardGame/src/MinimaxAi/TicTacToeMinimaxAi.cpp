#include "TicTacToeMinimaxAi.h"

TicTacToeMinimaxAi::~TicTacToeMinimaxAi()
{
    //
}
Move TicTacToeMinimaxAi::FindBestMove()
{
    auto startTime = std::chrono::steady_clock::now();
    constexpr auto timeLimit = std::chrono::milliseconds(2000);  // 2 seconds time limit

    Move bestMove = { -1, -1 }; // Invalid move

    // Take the easy win
    // Check for immediate winning move
    Move winningMove = DetectImmediateMove(kAi);
    if (winningMove.boardIndex != -1) return winningMove; // Check explicitly

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
                return bestMove;  // Stop searching if time runs out
            }
        }
    }

    return bestMove;
}


//Move MinimaxAi::FindBestMove()
//{
//    std::vector<Move> legalMoves = m_pBoard->GetLegalMoves();
//    int bestScore = -kScoreInf;
//    Move bestMove = { -1, -1 }; // Invalid move
//
//    // Check for immediate winning move
//    Move winningMove = DetectImmediateMove(kAi);
//    if (winningMove.boardIndex != -1) return winningMove; // Check explicitly
//
//    // Check for immediate blocking move
//    Move blockingMove = DetectImmediateMove(kPlayer);
//    if (blockingMove.boardIndex != -1) return blockingMove; // Check explicitly
//
//
//    for (const Move& move : legalMoves)
//    {
//
//        std::unique_ptr<Board> clonedBoard(m_pBoard->Clone());
//        clonedBoard->MakeMove(move);
//
//        int moveScore = Minimax(clonedBoard.get(), 0, false, -kScoreInf, kScoreInf);
//
//        if (moveScore > bestScore)
//        {
//            bestScore = moveScore;
//            bestMove = move;
//        }
//    }
//
//    return bestMove;
//}

Move TicTacToeMinimaxAi::DetectImmediateMove(int player)
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

    return Move(-1, -1); // Ensure it explicitly returns an invalid move
}
