#include "easy_bot.h"
#include <cstdlib>
#include <ctime>

    RandomBot::RandomBot(const std::string& name) : Player(PlayerType::Bot, name) {
        // Inicjalizacja generatora liczb losowych
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    // Implementacja metody wybierającej losowy pionek
    void RandomBot::getNextPiece(Board& board) const{
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
            std::cout << getName() << "Wybrany pionek: " << board.last_piece_indeks << std::endl;
        } else {
            std::cout << getName() << "Brak pionkow do wyboru." << std::endl;
        }
    }

    // Implementacja metody umieszczającej pionek na planszy
    void RandomBot::placePawn(Board& board) const{
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
                std::cout << getName() << "Ustawiono pionek na pozycji: (" << row << ", " << col << ")" << std::endl;
            } else {
                std::cout << getName() << "Nie udalo sie ustawic pionka." << std::endl;
            }
        } else {
            std::cout << getName() << "Nie znaleziono pustego miejsca." << std::endl;
        }
    }
