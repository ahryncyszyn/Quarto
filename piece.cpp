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