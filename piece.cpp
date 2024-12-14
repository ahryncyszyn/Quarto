#include "piece.h"

Piece::Piece(bool dark, bool square, bool hollow, bool tall)
    : attributes((dark << 3) | (hollow << 2) | (square << 1)
    | tall), available(true) {}