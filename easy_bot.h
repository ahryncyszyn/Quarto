#pragma once

#include "player.h"
#include "board.h"
#include <string>

// Klasa reprezentująca bota grającego losowo
class RandomBot : public Player {
public:
    // Konstruktor klasy RandomBot, przyjmujący nazwę gracza
    RandomBot(const std::string& name);

    // Metoda losująca pionek spośród dostępnych
    void getNextPiece(Board& board) const override;

    // Metoda losowo wybierająca pozycję i umieszczająca pionek na planszy
    void placePawn(Board& board) const override;
};
