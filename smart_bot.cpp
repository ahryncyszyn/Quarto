#include "smart_bot.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

SmartBot::SmartBot(const std::string& name) : Player(PlayerType::Bot, name) {}

void SmartBot::getNextPiece(Board& board) const {
    int bestPiece = -1;
    int worstThreat = -1;

    for (int i = 0; i < board.pieces.size(); ++i) {
        if (board.pieces[i].available) {
            int threatLevel = simulateOpponentThreat(board, i);
            if (threatLevel > worstThreat) {
                worstThreat = threatLevel;
                bestPiece = i;
            }
        }
    }

    if (bestPiece != -1) {
        board.last_piece_indeks = bestPiece;
        std::cout << getName() << " Wybrany pionek dla przeciwnika: " << board.last_piece_indeks << std::endl;
    } else {
        std::cout << getName() << " Brak pionków do wyboru." << std::endl;
    }
}

void SmartBot::placePawn(Board& board) const {
    int bestRow = -1, bestCol = -1;
    int bestScore = -1;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board.getCell(row, col) == nullptr) {
                int score = evaluateMove(board, row, col, board.last_piece_indeks);
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = row;
                    bestCol = col;
                }
            }
        }
    }

    if (bestRow != -1 && bestCol != -1) {
        if (board.placePiece(bestRow, bestCol, board.last_piece_indeks)) {
            std::cout << getName() << " Ustawiono pionek na pozycji: (" << bestRow << ", " << bestCol << ")" << std::endl;
        } else {
            std::cout << getName() << " Nie udało się ustawić pionka." << std::endl;
        }
    } else {
        std::cout << getName() << " Nie znaleziono pustego miejsca." << std::endl;
    }
}

int SmartBot::simulateOpponentThreat(const Board& board, int pieceIndex) const {
    int threatLevel = 0;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board.getCell(row, col) == nullptr) {
                Board tempBoard = board;
                tempBoard.placePiece(row, col, pieceIndex);
                if (tempBoard.winCondition()) {
                    threatLevel++;
                }
            }
        }
    }
    return threatLevel;
}

int SmartBot::evaluateMove(const Board& board, int row, int col, int pieceIndex) const {
    Board tempBoard = board;
    tempBoard.placePiece(row, col, pieceIndex);

    if (tempBoard.winCondition()) {
        return 1000;
    }

    int score = 0;
    score += countNearlyWinningLines(tempBoard, row, col);
    return score;
}

int SmartBot::countNearlyWinningLines(const Board& board, int row, int col) const {
    int nearlyWinningLines = 0;

    for (auto& line : board.getLines(row, col)) {
        int emptyCells = 0;
        int sameFeatureCount = 0;

        for (auto& cell : line) {
            if (board.getCell(cell.first, cell.second) == nullptr) {
                emptyCells++;
            } else if (board.getCell(cell.first, cell.second)->hasCommonFeature(board.pieces[board.last_piece_indeks])) {
                sameFeatureCount++;
            }
        }

        if (emptyCells == 1 && sameFeatureCount == 3) {
            nearlyWinningLines++;
        }
    }

    return nearlyWinningLines;
}
