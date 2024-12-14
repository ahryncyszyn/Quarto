#include <bitset>
#include <iostream>

class Piece {
public:
    std::bitset<4> attributes;
    bool available;

    Piece(bool dark, bool square, bool hollow, bool tall);
};