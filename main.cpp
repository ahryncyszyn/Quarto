#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <bits/stdc++.h>
#include <iostream>
#include "board.h"

Board board(false); // Nasza plansza. Zmien na true jesli chcesz zmienic na zaawansowana wersje zasad

const int CELL_SIZE_LARGE = 100; // Rozmiar komórki dużej planszy
const int GRID_SIZE_LARGE = 4;   // Rozmiar dużej planszy (GRID_SIZE_LARGE x GRID_SIZE_LARGE)

const int CELL_SIZE_PAWNS = 50;  // Rozmiar komórki małej planszy (2 razy mniejszy)
const int GRID_SIZE_PAWNS_ROWS = 2; // Liczba wierszy małej planszy
const int GRID_SIZE_PAWNS_COLS = 8; // Liczba kolumn małej planszy

void initializeGrids(sf::RectangleShape grid[][4], sf::RectangleShape pawns[]) {
    // Tablica 4x4 (duża plansza)
    
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            grid[row][col].setSize(sf::Vector2f(CELL_SIZE_LARGE, CELL_SIZE_LARGE));
            grid[row][col].setOutlineThickness(2);
            grid[row][col].setOutlineColor(sf::Color::Black);
            grid[row][col].setFillColor(sf::Color(211, 211, 211));
            grid[row][col].setPosition(col * CELL_SIZE_LARGE, row * CELL_SIZE_LARGE);
        }
    }

    // Tablica 8x2 (mała plansza)
    for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
        int row = ind / GRID_SIZE_PAWNS_COLS; // Obliczamy wiersz
        int col = ind % GRID_SIZE_PAWNS_COLS; // Obliczamy kolumnę

        pawns[ind].setSize(sf::Vector2f(CELL_SIZE_PAWNS, CELL_SIZE_PAWNS));
        pawns[ind].setOutlineThickness(2);
        pawns[ind].setOutlineColor(sf::Color::Black);
        pawns[ind].setFillColor(sf::Color(211, 211, 211));
        // Pozycja małej planszy: zaczyna się poniżej dużej planszy
        pawns[ind].setPosition(col * CELL_SIZE_PAWNS, GRID_SIZE_LARGE * CELL_SIZE_LARGE + row * CELL_SIZE_PAWNS);
    
    }
}

int mousePosition(sf::RectangleShape grid[][4], sf::RectangleShape pawns[], sf::Vector2i mousePos)
{
    // Sprawdzenie kliknięcia na dużej planszy
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            if (grid[row][col].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Kliknięto dużą komórkę: (" << row << ", " << col << ")" << std::endl;
                return 1;
            }
        }
    }
    
    // Sprawdzenie kliknięcia na małej planszy
    for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
        if (pawns[ind].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Kliknięto małą komórkę: (" << ind << ")" << std::endl;
            return 2;
        }
    }
    return 0; //brak wykoknania akcji
}

void place_pawn(sf::RectangleShape grid[][4], sf::Vector2i mousePos)
{
    if (board.last_piece_indeks == -1)
    {

    }
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

void actualize_last_pawn(sf::RectangleShape pawns[], sf::Vector2i mousePos)
{
    for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
        if (pawns[ind].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if (board.last_piece_indeks == -1){
                std::cout << "Zmiana wybranej figury na " << ind << std::endl;
                board.last_piece_indeks = ind;
            }
            else {
                std::cout << "Ustawinie wybranej figury na " << ind << std::endl;
                board.last_piece_indeks = ind;
            }
        }
    }
}

int main() {

    int windowWidth = 400; // Szerokość obu planszy jest równa
    int windowHeight = 500; // Wysokość jest sumą wysokości obu planszy

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tablica 4x4 i 8x2");

    
    sf::RectangleShape grid[GRID_SIZE_LARGE][GRID_SIZE_LARGE];
    sf::RectangleShape pawns[GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS];

    initializeGrids(grid, pawns);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Sprawdzanie kliknięcia myszy
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { 
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                int action = mousePosition(grid, pawns, mousePos);

                if (action == 1) place_pawn(grid, mousePos);
                if (action == 2) actualize_last_pawn(pawns, mousePos);
                if (board.winCondition()) {
                    std::cout << "Wygrana";
                    return 0;
                }
            }
        }
    
        //Logika gry. Interfejs ktory obsluguje input
        //i na podstawie game_logic.cpp aktualizuje stan gry
        // Wyczyść okno
        window.clear(sf::Color::White);

        // Rysowanie dużej planszy
        for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
            for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
                window.draw(grid[row][col]);
            }
        }

        // Rysowanie małej planszy
        for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
            window.draw(pawns[ind]);
        }

        
        window.display(); 

        
    }

    return 0;
}
