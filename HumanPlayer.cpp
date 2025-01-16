#include "HumanPlayer.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const int CELL_SIZE_LARGE = 100; // Rozmiar komórki dużej planszy
const int GRID_SIZE_LARGE = 4;   // Rozmiar dużej planszy (GRID_SIZE_LARGE x GRID_SIZE_LARGE)

const int CELL_SIZE_PAWNS = 50;  // Rozmiar komórki małej planszy (2 razy mniejszy)
const int GRID_SIZE_PAWNS_ROWS = 2; // Liczba wierszy małej planszy
const int GRID_SIZE_PAWNS_COLS = 8; // Liczba kolumn małej planszy

// int mousePosition(sf::RectangleShape grid[][4], sf::RectangleShape pawns[], sf::Vector2i mousePos)
// {
//     // Sprawdzenie kliknięcia na dużej planszy
//     for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
//         for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
//             if (grid[row][col].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                 std::cout << "Kliknięto dużą komórkę: (" << row << ", " << col << ")" << std::endl;
//                 return 1;
//             }
//         }
//     }
    
//     // Sprawdzenie kliknięcia na małej planszy
//     for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
//         if (pawns[ind].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//             std::cout << "Kliknięto małą komórkę: (" << ind << ")" << std::endl;
//             return 2;
//         }
//     }
//     return 0; //brak wykoknania akcji
// }

void HumanPlayer::placePawn(sf::CircleShape grid[][4], Board& board, sf::Vector2i mousePos) const
{
    // Sprawdzenie kliknięcia na dużej planszy
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            if (grid[row][col].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (board.last_piece_indeks != -1){
                    if (board.placePiece(row, col, board.last_piece_indeks)){
                        printf("Ustawiono pionek %d na pozycji %d %d\n", board.last_piece_indeks, row, col); 
                        board.last_piece_indeks = -1;
                    }
                    else std::cout << "Wybrany pionek nie działa\n";
                }
                else std::cout << "Nie wybrano pionka\n";
            }
        }
    }
}


// Ze względu na przełączanie graczy, to na tym etapie musi być weryfikowany wybór
int HumanPlayer::actualizeLastPawn(sf::RectangleShape pawns[], Board& board, sf::Vector2i mousePos) const
{
    for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
        if (pawns[ind].getGlobalBounds().contains(mousePos.x, mousePos.y)
            && board.pieces[ind].available) {
            std::cout << "Wybrano pionek o indeksie " << ind << std::endl;
            return ind;
        }
    }

    return -1;
}