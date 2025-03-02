#pragma once
#include <iostream>
#include <ostream>
#include <thread>

#include "AITasksQueue.h"
#include "../Interface/GameAi.h"
#include "../TicTacToe/TicTacToeBoard.h"

class TicTacToeMinimaxAi : public GameAi
{
    static constexpr int kAi = 2;
    static constexpr int kPlayer = 1;

    static constexpr int kScoreInf = 10000000;

    static constexpr int kWinMoveValue = 100;
    static constexpr int kTieValue = 150;
    static constexpr int kMaxDepth = 14;  // Set a reasonable max depth

    AITasksQueue m_tasksQueue;

public:
    explicit TicTacToeMinimaxAi(Board* pBoard)
        : GameAi(pBoard)
    {
        //
    }

    bool IsTerminalState(const Board* pBoard)
    {
        int winner = pBoard->GetWinner();
        return (winner == kAi || winner == kPlayer || winner == -1);
    }


    int TicTacToeMinimaxAi::Minimax(const Board* pBoard, int depth, bool isMax, int alpha, int beta)
    {
        if (depth >= kMaxDepth || IsTerminalState(pBoard))
        {
            return EvaluateBoard(pBoard);
        }

        std::unique_ptr<Board> clonedBoard(pBoard->Clone());

        // Get legal moves
        std::vector<Move> legalMoves = pBoard->GetLegalMoves();

        int best = isMax ? -kScoreInf : kScoreInf;

        for (const Move& move : legalMoves)
        {
            clonedBoard->MakeMove(move);

            // Check for a winner after the move
            int moveVal = EvaluateBoard(clonedBoard.get());

            if (moveVal == kWinMoveValue || moveVal == -kWinMoveValue || moveVal == kTieValue)
                return moveVal;
            //if (winner == kWinMoveValue)
            //{
            //    //std::cout << "AI wins with move: " << move.boardIndex << std::endl;
            //    return kWinMoveValue;  // AI wins
            //}
            //if (winner == -kWinMoveValue)
            //{
            //    //std::cout << "Player wins with move: " << move.boardIndex << std::endl;
            //    return -kWinMoveValue; // Player wins
            //}

            // Continue if no winner
            int moveScore = Minimax(clonedBoard.get(), depth + 1, !isMax, alpha, beta);

            if (isMax)
            {
                best = std::max(best, moveScore);
                alpha = std::max(alpha, best);
            }
            else
            {
                best = std::min(best, moveScore);
                beta = std::min(beta, best);
            }

            if (beta <= alpha) break;  // pruning
        }

        return best;
    }


    int EvaluateBoard(const Board* pBoard)
    {
        int winner = pBoard->GetWinner();
        if (winner == kAi) return kWinMoveValue; // AI wins
        if (winner == kPlayer) return -kWinMoveValue; // Player wins
        if (winner == -1) return kTieValue; // Draw
        return 0; // No winner yet
    }

    virtual ~TicTacToeMinimaxAi() override;

    virtual Move FindBestMove() override;
    Move DetectImmediateMove(int player);
};

