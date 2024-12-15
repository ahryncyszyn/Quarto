#include "board.h"

//Definicja konstruktora. Inicjalizuje plansze jako tablice 4x4
//gdzie kazda komorka to nullptr (czyli nie ma na niej jeszcze pionka)
Board::Board(bool advanced_mode) : grid(4, std::vector<Piece*>(4, nullptr)), advanced_mode(advanced_mode) {
    for (int i = 0; i < 16; i++) {
        /*emplace_back() dodaje wszystkie 16 pionkow sprawdzajac wszystkie
         *kombinacje 4 bitow atrybutow. Np dla i = 2 powstaje pionek
         *bedzie 0010 czyli: jasny, okragly, pusty i niski.
         *I tak iteruje przez wszystkie kombinacje atrybutow poniewaz
         *kazdy pionek jest inny.
         *pieces.emplace_back(i & 8, i & 4, i & 2, i & 1);
         */
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

    // Jesli zostanie wybrana bardziej zaawansowana wersja gry
    if (advanced_mode) {
        for (int row = 0; row < 3; row++) {
            for (int column = 0; column < 3; column++) {
                // Sprawdzamy czy na jakimkolwiek kwadracie na planszy 
                // Wszystkie pionki maja te same atrybuty
                if (checkLine(grid[row][column], grid[row][column + 1], grid[row +1 ][column], grid[row + 1][column + 1])) {
                    return true;
                }
            }
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

    /*Jesli atrybut wynosi 1 i jest dzielony przez wszystkie pionki w lini
     *Zwraca true i gra sie konczy.
     *Operacja & zwraca 1 jesli wszystkie porownane bity maja ten sam bit zapalony.
     *Dziala tylko dla 1. Operacja dla dzielonych 0 ponizej.
     */
    std::bitset<4>  sum = p1->attributes & p2->attributes & p3->attributes
    & p4->attributes;

    //any() sprawdza czy jakikolwiek bit sumy jest zapalony
    //Jesli tak to gra sie konczy
    if (sum.any()) return true;

    /*Teraz sprawdza czy bity maja 0 w tych samych miejscach. Wtedy gra tez sie skonczy.
     *Operacja OR sprawdza czy przynajmniej jeden bit jest zapalony, wtedy zwraca 1.
     *Negacja zamienia wszystkie 0 na 1 wiec zwrocony jest bit ktory nie jest zapalony dla wszystkich liczb
     *Czyli dzielony atrybut.
     */
    std::bitset<4> inverse = ~(p1->attributes | p2->attributes | p3->attributes | p4->attributes);

    return inverse.any();
}