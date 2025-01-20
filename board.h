#pragma once

#include <vector>
#include <bits/stdc++.h>
#include "piece.h"

class Board {

private:
    //Deklaruje tablice 2D gdzie kazdy element jest wskaznikiem na pionek.
    //nullptr jesli nie ma zadnego pinka jeszcze
    std::vector<std::vector<Piece*>> grid;

// Tymczasowo public, żeby działał kod wybierania pionka (sprawdzenie dostępności) i zmiana available. 
// Jeśli zostaniemy przy tej koncepcji, lepiej będzie zrobić getter + setter
public:
    //Deklaruje tablice 1D, ktora przetrzymuje wszystkie pionki.
    std::vector<Piece> pieces;

    // getter dla konkretnej komorki na planszy
    Piece* getCell(int row, int column) const {
        if (row >= 0 && row < grid.size() && column >= 0 && column < grid[row].size()) {
            return grid[row][column];
        }
        return nullptr;
    }

private:
    
    // Decyduje o tym czy gra będzie rozgrywana tylko
    // sprawdzając linie, czy rowniez kwadraty
    bool advanced_mode;

    //Sprawdza czy pionki w jakiejs lini "wygrywaja" tzn. dziela podobna ceche. 
    bool checkLine(Piece* p1, Piece* p2, Piece* p3, Piece* p4) const;

public:
    int last_piece_indeks = -1;

    // Konstruktor
    // Argument 0 dla podstawowej wersji i 1 dla zaawansowanej
    // Default podstawowa
    Board(bool advanced_mode = false);

    //Kladzie pionek z indeksem pIndex w podanym wierszu i kolumnie. 
    //Zwraca true jesli udalo sie postawic pionek.
    bool placePiece(int row, int column, int pIndex);

    //Zwraca true gdy ktos wygral
    bool winCondition() const;
};
