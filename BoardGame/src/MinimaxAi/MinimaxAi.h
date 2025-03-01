#pragma once
#include <thread>

#include "AITasksQueue.h"
#include "../Interface/GameAi.h"
#include "../TicTacToe/TicTacToeBoard.h"

class MinimaxAi : public GameAi
{
    static constexpr int kAi = 2;
    static constexpr int kPlayer = 1;

    static constexpr int kScoreInf = 10000000;

    static constexpr int kWinMoveValue = 100;
    static constexpr int kForkValue = 15;
    static constexpr int kBlockValue = 8;
    static constexpr int kCenterControlValue = 5;
    static constexpr int kBlockFork = 10;
    static constexpr int kCornerValue = 3;
    static constexpr int kTieValue = 0;


    AITasksQueue m_tasksQueue;

public:
    explicit MinimaxAi(Board* pBoard)
        : GameAi(pBoard)
    {

    }

    int Minimax(const Board* pBoard, int depth, bool isMax, int alpha, int beta)
    {
        std::unique_ptr<Board> clonedBoard(pBoard->Clone());

        // Get legal moves
        std::vector<Move> legalMoves = pBoard->GetLegalMoves();

        int best = isMax ? -kScoreInf : kScoreInf;

        for (const Move& move : legalMoves)
        {
            clonedBoard->MakeMove(move);

            // Check for a winner immediately after the move
            int winner = clonedBoard->GetWinner();
            if (winner == kAi) {
                return kWinMoveValue;  // AI wins
            }
            else if (winner == kPlayer) {
                return -kWinMoveValue;  // Player wins
            }

            // If there’s no winner, continue the minimax search
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

            if (beta <= alpha) break;  // Alpha-beta pruning
        }

        return best;
    }

    int EvaluateBoard(const Board* pBoard)
    {
        
        auto board = pBoard->GetBoardHash();
        int score = 0;

        // Check rows, columns, and diagonals for potential wins, forks, blocks
        for (int row = 0; row < 3; row++)
        {
            int start = row * 3;
            score += EvaluateLine(board[start], board[start + 1], board[start + 2]);
        }

        for (int col = 0; col < 3; col++)
        {
            score += EvaluateLine(board[col], board[col + 3], board[col + 6]);
        }

        // Check diagonals
        score += EvaluateLine(board[0], board[4], board[8]);
        score += EvaluateLine(board[2], board[4], board[6]);

        // Center control
        if (board[4] == kAi) score += kCenterControlValue;
        else if (board[4] == kPlayer) score -= kCenterControlValue;

        // Corners
        for (int corner : {0, 2, 6, 8})
        {
            if (board[corner] == kAi) score += kCornerValue;
            else if (board[corner] == kPlayer) score -= kCornerValue;
        }

        return score;
    }

    int EvaluateLine(int a, int b, int c)
    {
        int score = 0;

        // win check
        if (a == kAi && b == kAi && c == kAi) score += kWinMoveValue;
        else if (a == kPlayer && b == kPlayer && c == kPlayer) score -= kWinMoveValue;

        // AI two in a row with empty space
        else if (a == kAi && b == kAi && c == 0 ||
            a == kAi && c == kAi && b == 0 ||
            b == kAi && c == kAi && a == 0)
            score += kForkValue;

        // Player two in a row with empty space (block)
        else if (a == kPlayer && b == kPlayer && c == 0 ||
            a == kPlayer && c == kPlayer && b == 0 ||
            b == kPlayer && c == kPlayer && a == 0)
            score -= kBlockValue;

        return score;
    }


    virtual ~MinimaxAi() override;

    virtual Move FindBestMove() override;
};

