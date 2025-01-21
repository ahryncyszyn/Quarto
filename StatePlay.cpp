#include "StatePlay.h"
#include "HumanPlayer.h"
#include "Global.h"
#include "StateManager.h"
#include "StateMenu.h"

#include <SFML/Graphics.hpp>
#include <iostream> // tylko do debug

sf::Color beige = sf::Color(225, 202, 168);
const int windowWidth = 650;
const int windowHeight = 825;


StatePlay::StatePlay(Global* context, bool isAdvancedMode)
    : BaseState(context, StateType::Play), m_board(isAdvancedMode)
{ 
    // wczytywanie tła
    if (!backgroundTexture.loadFromFile("images/menu_background.png")) {
        std::cerr << "Loading background graphics unsuccessful" << std::endl;
    }

    // wczytywanie fontu na ogloszenie zwyciezcy
    winnerFont = *context->m_font;

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
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_globalContext->m_window);

        // Jeśli oczekujemy od gracza, że postawi pionek...
        if (m_stagePlace) {
            std::cout<<"Daje pionka"<<std::endl;
            //player->placePawn(grid, m_board, mousePos);
                // Sprawdzenie kliknięcia na dużej planszy
            for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
                for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
                    if (grid[row][col].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (m_board.last_piece_indeks != -1){
                            if (m_board.placePiece(row, col, m_board.last_piece_indeks)){
                                printf("Ustawiono pionek %d na pozycji %d %d\n", m_board.last_piece_indeks, row, col); 
                                m_board.last_piece_indeks = -1;
                            }
                            else std::cout << "Wybrany pionek nie działa\n";
                        }
                        else std::cout << "Nie wybrano pionka\n";
                    }
                }
            }

            // Jeśli last_piece_indeks == -1, tzn., że gracz wykonał legalny ruch
            // Wtedy zmieniamy oczekiwany input na wybór pionka dla następnego gracza;
            // Wpp oczekujemy, że wybierze inną pozycję
            m_stagePlace = m_board.last_piece_indeks != -1; 
        }
        
        // W przeciwnym wypadku wybiera pionek dla następnego gracza
        else {
            int res = -1;    
            for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
                if (pawns[ind].getGlobalBounds().contains(mousePos.x, mousePos.y)
                    && m_board.pieces[ind].available) {
                    std::cout << "Wybrano pionek o indeksie " << ind << std::endl;
                    res = ind;
                }
            }
            std::cout<<res<<std::endl;

            // Gracz wybrał legalny pionek
            if (res != -1) {
                m_board.last_piece_indeks = res;
                m_currentPlayer = (m_currentPlayer + 1) % 2;
                m_stagePlace = true;
            }
        }

        // zmodyfikowanie pozycji podswietlenia na wybrany pionek
        if (m_board.last_piece_indeks != -1)
        {
            int ind = m_board.last_piece_indeks;
            int row = ind / GRID_SIZE_PAWNS_COLS;
            int col = ind % GRID_SIZE_PAWNS_COLS;
            chosen_pawn.setPosition((col * CELL_SIZE_PAWNS) + PADDING_SIZE, 
                                     600 + 2*PADDING_SIZE + row * CELL_SIZE_PAWNS);
        }   
    }
}

void StatePlay::update() {
    if (m_players[m_currentPlayer]->getType() != PlayerType::Human)
        m_players[m_currentPlayer]->placePawn(m_board);

    if (m_board.winCondition()) {
        std::cout<<m_players[m_currentPlayer]->getName()<< " zwycieza!"<<std::endl;
        displayWinner();

        m_globalContext->m_states->initNextState<StateMenu>();
        m_globalContext->m_states->changeState();
        return;
    }

    if (m_players[m_currentPlayer]->getType() != PlayerType::Human) {
        m_players[m_currentPlayer]->getNextPiece(m_board);
        m_currentPlayer = (m_currentPlayer + 1) % 2; 
    }
}

void StatePlay::displayWinner(){

    // ustawia okienko z wygrana na srodek ekranu
    sf::RenderWindow winnerWindow(sf::VideoMode(500, 200), "WIN!");
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int x = (desktop.width - winnerWindow.getSize().x) / 2;
    int y = (desktop.height - winnerWindow.getSize().y) / 2;
    winnerWindow.setPosition(sf::Vector2i(x, y));

    // rysowanie tła
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(1, 1.75);
    winnerWindow.draw(background);

    // komunikat wygranej
    sf::Text winnerText;
    winnerText.setFont(winnerFont);
    winnerText.setString(m_players[m_currentPlayer]->getName() + " wins!");
    winnerText.setCharacterSize(60);
    winnerText.setFillColor(sf::Color::Black);
    winnerText.setStyle(sf::Text::Bold);

    // wysrodkowanie tesktu w okienku
    sf::FloatRect textRect = winnerText.getLocalBounds();
    winnerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    winnerText.setPosition(winnerWindow.getSize().x / 2.0f, 
                           winnerWindow.getSize().y / 2.0f);

    while (winnerWindow.isOpen()) {
        sf::Event event;
        while (winnerWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                winnerWindow.close();
            }
        }

        winnerWindow.clear(sf::Color::Black);
        winnerWindow.draw(background);
        winnerWindow.draw(winnerText);
        winnerWindow.display();
    }
}

void StatePlay::draw() const {

    // rysowanie tła
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(1.75, 1.75);
    m_globalContext->m_window->draw(background);

    // czarne tlo glownej planszy
    sf::RectangleShape board_background(sf::Vector2f(windowWidth - PADDING_SIZE * 2, windowHeight * 600/825));
    board_background.setFillColor(sf::Color(0, 0, 0, 220));
    float border = (windowWidth - board_background.getSize().x) / 2.0f; 
    board_background.setPosition(border, border);
    m_globalContext->m_window -> draw(board_background);

    // bezowa obwodka dookola planszy
    sf::CircleShape board_circle;
    board_circle.setRadius((board_background.getSize().x - 2*PADDING_SIZE)/ 2);
    board_circle.setOutlineThickness(5);
    board_circle.setOutlineColor(beige);
    board_circle.setFillColor(sf::Color::Transparent);
    board_circle.setPosition(2*PADDING_SIZE, 2*PADDING_SIZE);
    m_globalContext->m_window -> draw(board_circle);

    // rysowanie duzej planszy
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            m_globalContext->m_window -> draw(grid[row][col]);
        }
    }

    // rysowanie małej planszy
    for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
        m_globalContext->m_window -> draw(pawns[ind]);
    }

    // podswietlenie wybranego pionka
    if (m_board.last_piece_indeks != -1) m_globalContext->m_window -> draw(chosen_pawn);

    // rysowanie wolnych do uzycia pionkow
    for (int i = 0; i < m_board.pieces.size(); ++i)
    {
        const Piece& piece = m_board.pieces[i];
        if (piece.available)
        {
            sf::Vector2f position = pawns[i].getPosition();
            piece.draw(*m_globalContext->m_window, sf::Vector2f(position.x, position.y + 2), CELL_SIZE_PAWNS);
        }
    }

    // rysowanie pionkow ulozonych na planszy
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            const Piece* piece = m_board.getCell(row, col);
            if (piece != nullptr) {
                sf::Vector2f position = grid[row][col].getPosition();
                piece->draw(*m_globalContext->m_window, 
                            sf::Vector2f(position.x - 5, position.y - 20), CELL_SIZE_LARGE);
            }
        }
    }
}


void StatePlay::initializeGrids() {

    // inicjalizowanie pol glownej planszy 4x4 jako bezowe kolka
    for (int row = 0; row < GRID_SIZE_LARGE; ++row) {
        for (int col = 0; col < GRID_SIZE_LARGE; ++col) {
            float radius = (windowWidth - 12*PADDING_SIZE) / 8;
            grid[row][col].setRadius(radius);
            grid[row][col].setOutlineThickness(5);
            grid[row][col].setOutlineColor(beige);
            grid[row][col].setFillColor(sf::Color(0, 0, 0, 90));

            float x = col * CELL_SIZE_LARGE + PADDING_SIZE;
            float y = row * CELL_SIZE_LARGE + PADDING_SIZE;
            float angle = -3.14 / 4.0f;
            float cos_angle = std::cos(angle);
            float sin_angle = std::sin(angle);

            grid[row][col].setPosition(x * cos_angle - y * sin_angle + 35, x * sin_angle + y * cos_angle + 280);
            grid[row][col].move(0, 0);
        }
    }

    // inicjalizowanie pol malej planszy 8x2 jako bezowe kwadraty
    for (int ind = 0; ind < GRID_SIZE_PAWNS_ROWS * GRID_SIZE_PAWNS_COLS; ++ind) {
        int row = ind / GRID_SIZE_PAWNS_COLS;
        int col = ind % GRID_SIZE_PAWNS_COLS;

        pawns[ind].setSize(sf::Vector2f(CELL_SIZE_PAWNS + 2, CELL_SIZE_PAWNS + 2));
        pawns[ind].setOutlineThickness(1);
        pawns[ind].setOutlineColor(sf::Color::Black);
        pawns[ind].setFillColor(sf::Color(0, 0, 0, 100));
        
        // ustawienie małej pod duza
        pawns[ind].setPosition((col * CELL_SIZE_PAWNS) + PADDING_SIZE, 
                                600 + 2*PADDING_SIZE + row * CELL_SIZE_PAWNS);

    }

    // inicjalizowanie pola podswietlajacego wybrany pionek
    chosen_pawn.setSize(sf::Vector2f(CELL_SIZE_PAWNS + 2, CELL_SIZE_PAWNS + 2));
    chosen_pawn.setFillColor(sf::Color(255, 255, 255, 100));
    chosen_pawn.setPosition(PADDING_SIZE, 600 + 2*PADDING_SIZE);
}