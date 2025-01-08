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
    sf::Shape* shape;

    // rysuje pionek okragly lub kwadratowy
    if (attributes[1]) {
        shape = new sf::RectangleShape(sf::Vector2f(size, size));
    } else {
        shape = new sf::CircleShape(size / 2.0f);
    }

    // rysuje pionek jasny lub ciemny
    shape -> setFillColor(attributes[0] ? sf::Color(110, 38, 14) : sf::Color(193, 154, 107));
    shape -> setOutlineThickness(4);
    shape -> setOutlineColor(sf::Color::Black);
    shape -> setPosition(position);

    // rysuje pionek wysoki lub niski (na razie zwizualizowane jako brak obwodki)
    if (attributes[3]) {
        shape -> setOutlineColor(sf::Color::Transparent);
    }

    window.draw(*shape);

    // rysuje pionek otwarty lub zamkniety
    if (attributes[2]) {
        sf::CircleShape hole(size / 4.0f);
        hole.setFillColor(sf::Color::Transparent);
        hole.setOutlineThickness(4);
        hole.setOutlineColor(sf::Color::Black);
        hole.setPosition(position + sf::Vector2f(size / 4.0f, size / 4.0f));
        window.draw(hole);
    }

    delete shape;
}
