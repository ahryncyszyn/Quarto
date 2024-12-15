#include <bitset>
#include <iostream>

class Piece {
public:
    /*Attributes trzyma informacje o typie pionka które są zapisywane na bitach.
     *Największy bit oznacza kolor pionka. {1 - ciemny, 0 - jasny}
     *Nastepny bit oznacza ksztalt pionka. {1 - kwadratowy, 0 - okragly}
     *Nastepny jeszcze bit oznacza "sufit" pionkka. {1 - pusty/otwarty, 0 - zamkniety/plaski}
     *Ostatni bit oznacza jak wysoki jest pionek. {1 - wysoki, 0 - niski}
    */
    std::bitset<4> attributes;

    //Available mówi czy pionek jest jeszcze dostępny do użycia czy już został użyty.
    //Każdy pionek zaczyna z wartościa 1 - czyli jeszcze jest dostepny
    bool available;

    //Konstruktor
    Piece(bool dark, bool square, bool hollow, bool tall);
};