#include "StateMenu.h"
#include "Global.h"
#include <iostream>

StateMenu::StateMenu(Global* context)
    : BaseState(context, StateType::Menu)
{
    if (!m_font.loadFromFile("HawthorneVintage.otf")) {
        std::cerr << "Failed to load font\n";
    }

    if (!m_backgroundTexture.loadFromFile("images/menu_background.png")) {
        std::cerr << "Loading background graphics unsuccessful" << std::endl;
    }
}

void StateMenu::processInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        
        // sprawdzenie pozycji klikniecia
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_globalContext->m_window);

        // sprawdzenie, czy klikniecie nastapilo na guziku z instrukcjami

        // sprawdzenie, czy klikniecie nastapilo na guziku do rozpoczecia gry

        // sprawdzenie, czy klikniecie nastapilo na guziku do wyjscia
    }
}

void StateMenu::update()
{
    // aktualizacja stanu menu
}

void StateMenu::draw() const
{
    sf::Sprite background;
    background.setTexture(m_backgroundTexture);
    background.setScale(1.75, 1.75);
    m_globalContext->m_window->draw(background);

    // rysowanie napisu Quarto! na gorze
    sf::Text title;
    title.setFont(m_font);
    title.setString("Quarto!");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Black);

    float text_width = title.getLocalBounds().width;
    float window_width = m_globalContext->m_window->getSize().x;
    title.setPosition((window_width - text_width) / 2, PADDING_SIZE);
    m_globalContext->m_window->draw(title);

    // rysowanie opcji gry
    //instructionsButton.draw(*m_window);
    //startButton.draw(*m_window);
    //exitButton.draw(*m_window);
}