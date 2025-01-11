#include "piece.h"

/*Definicja konstruktora.
 *Wartosci atrybutow sa zapisywane na bitach (wyjasnienie w pliku piece.h)
 *Operacje bitshift potrafia zaznaczyc konkretny bit ktory chcemy ustawic
 *Np dark << 3 ustawia najbardziej znaczacy bit: 1 dla ciemnego pionka i 0 dla jasnego
 *1000 pionek ciemny, okragly, zamkniety i niski, 
 *0101 pionek jasny, kwadratowy, otwarty i wysoki etc.
 *Available jest zawsze prawdziwe na poczatku, jako ze pionek nie zostal jeszcze uzyty
 */
Piece::Piece(bool dark, bool square, bool hollow, bool tall)
    : attributes((dark << 3) | (square << 2) | (hollow << 1)
    | tall), available(true) {}

void Piece::draw(sf::RenderWindow& window, sf::Vector2f position, float size) const {

    static sf::Texture pawn_texture;

    if (!pawn_texture.loadFromFile("images/testpawn.png"))
    {
        std::cerr << "Loading pawn graphics unseccessful" << std::endl;
        return;
    }
    pawn_texture.setSmooth(true);

    sf::Sprite pawn_sprite;
    pawn_sprite.setTexture(pawn_texture);

    float scale = size / pawn_texture.getSize().x;
    pawn_sprite.setScale(scale, scale);

    pawn_sprite.setPosition(position);
    window.draw(pawn_sprite);

}
