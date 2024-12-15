#include "board.h"

//Definicja konstruktora. Inicjalizuje plansze jako tablice 4x4
//gdzie kazda komorka to nullptr (czyli nie ma na niej jeszcze pionka)
Board::Board() : grid(4, std::vector<Piece*>(4, nullptr)) {
    for (int i = 0; i < 16; i++) {
        //emplace_back() dodaje wszystkie 16 pionkow sprawdzajac wszystkie
        //kombinacje 4 bitow atrybutow. Np dla i = 2 powstaje pionek
        //bedzie 0010 czyli: jasny, okragly, pusty i niski.
        //I tak iteruje przez wszystkie kombinacje atrybutow poniewaz
        //kazdy pionek jest inny.
        pieces.emplace_back(i & 8, i & 4, i & 2, i & 1);
    }
}

bool Board::placePiece(int row, int column, int pIndex) {
    //Sprawdza czy podane wiersz i kolumna mieszcza sie w planszy. Jesli nie zwraca false
    if (row < 0 || row >= 4|| column < 0 || column >= 4) {
        std::cout << "Wrong position" << std::endl;
        return false;
    }

    //Sprawdza czy miejsce nie jest jeszcze zajete. Jesli jest to zwraca false
    if (grid[row][column] != nullptr) {
        std::cout << "Position is already taken" << std::endl;
        return false;
    }

    //Sprawdza czy podany indeks pionka jest poprawny i czy pionek jest jescze dostepny.
    //Inaczej zwraca false.
    if (pIndex < 0 || pIndex >= 16 || !pieces[pIndex].available) {
        std::cout << "Invalid piece" << std::endl;
        return false;
    }

    //Przypisuje wskaznik na wskazany pionek do wybranego miejsca na planszy
    grid[row][column] = &pieces[pIndex];
    //Zmienia available na false, bo pionek juz nie moze byc uzyty ponownie
    pieces[pIndex].available = false;
    return true;
}

bool Board::winCondition() const {
    for (int j = 0; j < 4; j++) {
        /*Dla kazdego j sprawdza czy, jakas kolumna lub wiersz wygrywa
         *tzn. dla j = 0 sprawdza czy pierwsza kolumna albo pierwszy wiersz
         *wygrywaja itd..
        */
        if (checkLine(grid[j][0], grid[j][1], grid[j][2], grid[j][3])
        || checkLine(grid[0][j], grid[1][j], grid[2][j], grid[3][j])) {
            return true;
        }
    }
    //Jesli zadna kolumna i wiersz nie wygrywaja to sprawdza przekątne.
    return checkLine(grid[0][0], grid[1][1], grid[2][2], grid[3][3])
    || checkLine(grid[0][3], grid[1][2], grid[2][1], grid[3][0]);
}

bool Board::checkLine(Piece* p1, Piece* p2, Piece* p3, Piece* p4) const {
    //Sprawdza czy w lini znajduja sie w ogole 4 pionki. Jesli
    //w lini jest mniej niz 4 pionki to zwraca od razu false
    if (!p1 || !p2 || !p3 || !p4) return false;

    /*Jesli jakikolwiek atrybut jest dzielony przez wszystkie pionki w lini
     *Zwraca true i gra sie konczy.
     *Operacja & zwraca 1 jesli wszystkie pornwane bity maja ten bit zapalony.
     *Czyli jesli wszystkie sa jasne to bit 0 bedzie sie rownal 1.
    */
    std::bitset<4>  sum = p1->attributes & p2->attributes & p3->attributes
    & p4->attributes;

    //any() sprawdza czy jakikolwiek bit sumy jest zapalony
    //Jesli tak to gra sie konczy
    return sum.any();
}