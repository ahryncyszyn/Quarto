#pragma once

#include "player.h"

#include <SFML/Graphics.hpp>

class HumanPlayer : public Player {
    public:
        HumanPlayer(const std::string& name)
            : Player(PlayerType::Human, name) { }


        void placePawn(Board&) const final { };
        void getNextPiece(Board&) const final { };
        void placePawn(sf::CircleShape grid[][4], Board& board, sf::Vector2i mousePos) const;
        int actualizeLastPawn(sf::RectangleShape pawns[], Board& board, sf::Vector2i mousePos) const;
};