#pragma once
#include <iostream>
#include <ostream>
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
    static constexpr int kAiFavorableBoardValue = 75;
    static constexpr int kPlayerFavorableBoardValue = 160;

    static constexpr int kTieValue = 5;
    static constexpr int kMaxDepth = 16;  // Set a max depth/ goal 10 ->12 would be great

    // AITasksQueue m_tasksQueue;

    int controlDepth = kMaxDepth / 2; // half the max at the start
    int roundCount = 0;
    int expandCounterMax = 9; 
public:
    explicit MinimaxAi(Board* pBoard)
        : GameAi(pBoard)
    {
        //
    }

    bool IsTerminal(const Board* pBoard)
    {
        const int winner = pBoard->GetWinner();
        return (winner == kAi || winner == kPlayer || winner == -1);
    }


    int Minimax(const Board* pBoard, int depth, bool isMax, int alpha, int beta)
    {
        if (depth >= controlDepth || IsTerminal(pBoard))
        {
            return EvaluateBoard(pBoard);
        }

        // Get legal moves
        std::vector<Move> legalMoves = pBoard->GetLegalMoves();

        int best = isMax ? -kScoreInf : kScoreInf;

        for (const Move& move : legalMoves)
        {
            std::unique_ptr<Board> clonedBoard(pBoard->Clone());
            clonedBoard->MakeMove(move);

            // Check for a winner after the move
            int moveVal = EvaluateBoard(clonedBoard.get());

            if (moveVal == kWinMoveValue || moveVal == -kWinMoveValue || moveVal == kTieValue)
                return moveVal;

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
        const int winner = pBoard->GetWinner();
        if (winner == kAi) return kWinMoveValue; // AI wins
        if (winner == kPlayer) return -kWinMoveValue; // Player wins
        if (winner == -1) return kTieValue; // Draw

        int score = 0;

        // Check for favorable patterns
        std::vector<Move> aiThreats = MinimaxAi::GetThreat(pBoard, kAi);
        std::vector<Move> playerThreats = MinimaxAi::GetThreat(pBoard, kPlayer);

        // scores based on detected threats
        score += aiThreats.size() * kAiFavorableBoardValue;       // Reward AI for opportunities
        score -= playerThreats.size() * kPlayerFavorableBoardValue;   // Penalize if Player has threats


        return score; // No winner yet
    }

    std::vector<Move> GetThreat(const Board* pBoard, int player)
    {
        std::vector<Move> threats;
        const std::vector<Move> legalMoves = pBoard->GetLegalMoves();

        for (const Move& move : legalMoves)
        {
            std::unique_ptr<Board> tempBoard(pBoard->Clone());
            tempBoard->MakeMove(move);

            if (tempBoard->GetWinner() == player)
            {
                threats.push_back(move);
            }
        }

        return threats;
    }

    virtual ~MinimaxAi() override;

    virtual Move FindBestMove() override;
    Move DetectImmediateMove(int player);
};

