#include <vector>
#include "piece.h"

class Board {
private:
    std::vector<std::vector<Piece*>> grid;
    std::vector<Piece> pieces;

public:
    Board();
    bool placePiece(int row, int column, int pIndex);
    bool winCondition() const;

private:
    bool checkLine(Piece* p1, Piece* p2, Piece* p3, Piece* p4) const;
};