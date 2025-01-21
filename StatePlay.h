#pragma once

#include "BaseState.h"
#include "board.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <memory>

class Player;

// Stan gry definiujący właściwą rozgrywkę
class StatePlay : public BaseState {
    static const int PADDING_SIZE = 25;
    static const int CELL_SIZE_LARGE = 100; // Rozmiar komórki dużej planszy
    static const int GRID_SIZE_LARGE = 4;   // Rozmiar dużej planszy (GRID_SIZE_LARGE x GRID_SIZE_LARGE)

    static const int CELL_SIZE_PAWNS = 75;  // Rozmiar komórki małej planszy (2 razy mniejszy)
    static const int GRID_SIZE_PAWNS_ROWS = 2; // Liczba wierszy małej planszy
    static const int GRID_SIZE_PAWNS_COLS = 8; // Liczba kolumn małej planszy

    public:
        StatePlay(Global* context);
        void processInput(const sf::Event&) final;
        void update() final;
        void draw() const final;

    private:
        void initializeGrids();
        template <typename T> void
        initPlayer(int index, const std::string& name);

        short m_currentPlayer = 0;
        bool m_stagePlace = 0;          // W przypadku ruchów gracza ludzkiego,
                                        // Musimy wiedzieć, czy aktualnie legalnym ruchem jest
                                        // Umieszczenie pionka, czy wybranie kolejnego pionka

        Board m_board;
        sf::Texture backgroundTexture;
        std::shared_ptr<Player> m_players[2];
        sf::CircleShape grid[GRID_SIZE_LARGE][GRID_SIZE_LARGE];
        sf::RectangleShape pawns[GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS]; 
        sf::RectangleShape chosen_pawn;
};

template <typename T>
inline void StatePlay::initPlayer(int index, const std::string& name)
{
    m_players[index].reset(std::make_shared<T>(name));
}
