#include "board.h"

Board::Board() : grid(4, std::vector<Piece*>(4, nullptr)) {
    for (int i = 0; i < 16; i++) {
        pieces.emplace_back(i & 8, i & 4, i & 2, i & 1);
    }
}

bool Board::placePiece(int row, int column, int pIndex) {
    if (row < 0 || row >= 4|| column < 0 || column >= 4) {
        std::cout << "Wrong position" << std::endl;
        return false;
    }

    if (grid[row][column] != nullptr) {
        std::cout << "Position is already taken" << std::endl;
        return false;
    }

    if (pIndex < 0 || pIndex >= 16 || !pieces[pIndex].available) {
        std::cout << "Invalid piece" << std::endl;
        return false;
    }

    grid[row][column] = &pieces[pIndex];
    pieces[pIndex].available = false;
    return true;
}

bool Board::winCondition() const {
    for (int j = 0; j < 4; j++) {
        if (checkLine(grid[j][0], grid[j][1], grid[j][2], grid[j][3]))
        || checkLine(grid[0][j], grid[1][j], grid[2][j], grid[3][j])) {
            return true;
        }
    }
    return checkLine(grid[0][0], grid[1][1], grid[2][2], grid[3][3])
    || checkLine(grid[0][3], grid[1][2], grid[2][1], grid[3][0]);
}

bool Board::checkLine(Piece* p1, Piece* p2, Piece* p3, Piece* p4) const {
    if (!p1 || !p2 || !p3 || !p4) return false;

    std::bitset<4>  sum = p1->attributes & p2->attributes & p3->attributes
    & p4->attributes;
    if (sum.any()) return true;

    sum = -(p1->attributes | p2->attributes | p3->attributes | p4->attributes);
    return sum.any();
}