#include "StatePlay.h"
#include "HumanPlayer.h"

#include <SFML/Graphics.hpp>
#include <iostream> // tylko do debug


StatePlay::StatePlay(sf::RenderWindow* window)
    : BaseState(window, StateType::Play), m_board(false) 
{ 
    // Tutaj możemy chcieć zaimplementować ify, żeby tworzyć różne rodzaje graczy
    m_players[0] = std::make_shared<HumanPlayer>("Player 1");
    m_players[1] = std::make_shared<HumanPlayer>("Player 2");

    initializeGrids();
}

// Tutaj trzeba podrasować
void StatePlay::processInput(const sf::Event& event)
{
    // HandleInput w kontekscie StatePlay ma sens jedynie kiedy aktualny gracz jest człowiekiem
    // Jedynym interesującym inputem jest kliknięcie
    if (m_players[m_currentPlayer]->getType() == PlayerType::Human
        && event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
        const HumanPlayer* player = static_cast<HumanPlayer*>(m_players[m_currentPlayer].get());

        // Jeśli oczekujemy od gracza, że postawi pionek...
        if (m_stagePlace) {
            std::cout<<"Daje pionka"<<std::endl;
            player->placePawn(grid, m_board, mousePos);

            // Jeśli last_piece_indeks == -1, tzn., że gracz wykonał legalny ruch
            // Wtedy zmieniamy oczekiwany input na wybór pionka dla następnego gracza;
            // Wpp oczekujemy, że wybierze inną pozycję
            m_stagePlace = m_board.last_piece_indeks != -1; 
        }
        
        // W przeciwnym wypadku wybiera pionek dla następnego gracza
        else {
            int ret = player->actualizeLastPawn(pawns, m_board, mousePos);
            std::cout<<ret<<std::endl;
            if (ret != -1) {
                m_board.last_piece_indeks = ret;
                m_currentPlayer = (m_currentPlayer + 1) % 2;
                m_stagePlace = true;
            }
        }
            
    }
}

void StatePlay::update() {
    if (m_players[m_currentPlayer]->getType() != PlayerType::Human)
        m_players[m_currentPlayer]->placePawn(m_board);

    if (m_board.winCondition()) {
        std::cout<<m_players[m_currentPlayer]->getName()<< " zwycieza!"<<std::endl;
        return;
    }

    if (m_players[m_currentPlayer]->getType() != PlayerType::Human) {
        m_players[m_currentPlayer]->getNextPiece(m_board);
        m_currentPlayer = (m_currentPlayer + 1) % 2; 
    }
}

void StatePlay::draw() const {

    // Rysowanie dużej planszy
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            m_window->draw(grid[row][col]);
        }
    }

    // Rysowanie małej planszy
    for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
        m_window->draw(pawns[ind]);
    }

    // rysowanie wolnych do uzycia pionkow
    for (int i = 0; i < m_board.pieces.size(); ++i)
    {
        const Piece& piece = m_board.pieces[i];
        if (piece.available)
        {
            int row = i / GRID_SIZE_PAWNS_COLS;
            int col = i % GRID_SIZE_PAWNS_COLS;
            float x = col * CELL_SIZE_PAWNS + 10;
            float y = GRID_SIZE_LARGE * CELL_SIZE_LARGE + row * CELL_SIZE_PAWNS + 10;
            sf::Vector2f position(x, y);
            piece.draw(*m_window, position, CELL_SIZE_PAWNS - 20);
        }
    }

    // rysowanie pionkow ulozonych na planszy
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            const Piece* piece = m_board.getCell(row, col);
            if (piece != nullptr) {
                sf::Vector2f position(col * CELL_SIZE_LARGE + 10, row * CELL_SIZE_LARGE + 10);
                piece->draw(*m_window, position, CELL_SIZE_LARGE - 20);
            }
        }
    }
}


void StatePlay::initializeGrids() {
    // Tablica 4x4 (duża plansza)
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            grid[row][col].setSize(sf::Vector2f(CELL_SIZE_LARGE, CELL_SIZE_LARGE));
            grid[row][col].setOutlineThickness(2);
            grid[row][col].setOutlineColor(sf::Color::Black);
            grid[row][col].setFillColor(sf::Color(211, 211, 211));
            grid[row][col].setPosition(col * CELL_SIZE_LARGE, row * CELL_SIZE_LARGE);
        }
    }

    // Tablica 8x2 (mała plansza)
    for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
        int row = ind / GRID_SIZE_PAWNS_COLS; // Obliczamy wiersz
        int col = ind % GRID_SIZE_PAWNS_COLS; // Obliczamy kolumnę

        pawns[ind].setSize(sf::Vector2f(CELL_SIZE_PAWNS, CELL_SIZE_PAWNS));
        pawns[ind].setOutlineThickness(2);
        pawns[ind].setOutlineColor(sf::Color::Black);
        pawns[ind].setFillColor(sf::Color(211, 211, 211));
        // Pozycja małej planszy: zaczyna się poniżej dużej planszy
        pawns[ind].setPosition(col * CELL_SIZE_PAWNS, GRID_SIZE_LARGE * CELL_SIZE_LARGE + row * CELL_SIZE_PAWNS);
    }
}