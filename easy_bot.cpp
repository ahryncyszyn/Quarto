#pragma once

#include "easy_bot.h"
#include <cstdlib>
#include <ctime>

class RandomBot : public Player {
public:
    RandomBot(const std::string& name) : Player(PlayerType::Bot, name) {
        // Inicjalizacja generatora liczb losowych
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    // Implementacja metody wybierającej losowy pionek
    void getNextPiece(Board& board) const override {
        std::vector<int> availablePieces;

        // Znajdź wszystkie dostępne pionki
        for (int i = 0; i < board.pieces.size(); ++i) {
            if (board.pieces[i].available) {
                availablePieces.push_back(i);
            }
        }

        if (!availablePieces.empty()) {
            // Wybierz losowy pionek
            int randomIndex = std::rand() % availablePieces.size();
            board.last_piece_indeks = availablePieces[randomIndex];
            std::cout << getName() << " selected piece: " << board.last_piece_indeks << std::endl;
        } else {
            std::cout << getName() << " could not find any available pieces!" << std::endl;
        }
    }

    // Implementacja metody umieszczającej pionek na planszy
    void placePawn(Board& board) const override {
        std::vector<std::pair<int, int>> emptyCells;

        // Znajdź wszystkie wolne komórki na planszy
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                if (board.getCell(row, col) == nullptr) {
                    emptyCells.emplace_back(row, col);
                }
            }
        }

        if (!emptyCells.empty()) {
            // Wybierz losową komórkę
            int randomIndex = std::rand() % emptyCells.size();
            int row = emptyCells[randomIndex].first;
            int col = emptyCells[randomIndex].second;

            // Umieść pionek w losowej komórce
            if (board.placePiece(row, col, board.last_piece_indeks)) {
                std::cout << getName() << " placed piece at position: (" << row << ", " << col << ")" << std::endl;
            } else {
                std::cout << getName() << " failed to place piece!" << std::endl;
            }
        } else {
            std::cout << getName() << " could not find an empty cell!" << std::endl;
        }
    }
};
