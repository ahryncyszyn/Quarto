#pragma once
#include "player.h"
#include "board.h"
#include <string>
class SmartBot : public Player {
public:
    // Konstruktor
    explicit SmartBot(const std::string& name);
    // Wybór pionka dla przeciwnika
    void getNextPiece(Board& board) const override;
    // Umieszczenie pionka na planszy
    void placePawn(Board& board) const override;
private:
    // Symulacja: Ocena, jak groźny jest pionek dla przeciwnika
    int simulateOpponentThreat(const Board& board, int pieceIndex) const;
    // Ocena ruchu: Jak dobry jest dany ruch
    int evaluateMove(const Board& board, int row, int col, int pieceIndex) const;
    // Liczba prawie wygranych linii
    int countNearlyWinningLines(const Board& board, int row, int col) const;
};