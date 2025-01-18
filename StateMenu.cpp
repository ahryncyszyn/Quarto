#include "StateMenu.h"

#include <iostream>

StateMenu::StateMenu(sf::RenderWindow* window)
    : BaseState(window, StateType::Menu)
{
    if (!m_font.loadFromFile("HawthorneVintage.otf")) {
        std::cerr << "Nie udało się załadować czcionki\n";
    }

    initializeOptions();
}

void StateMenu::processInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        
        // sprawdzenie pozycji klikniecia
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

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
    // rysowanie tła
    sf::Texture background_texture;
    if (!background_texture.loadFromFile("images/menu_background.png"))
    {
        std::cerr << "Loading background graphics unseccessful" << std::endl;
        return;
    }
    sf::Sprite background;
    background.setTexture(background_texture);
    background.setScale(1.75, 1.75);
    m_window->draw(background);

    // rysowanie napisu Quarto! na gorze
    sf::Text title;
    title.setFont(m_font);
    title.setString("Quarto!");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Black);

    float text_width = title.getLocalBounds().width;
    float window_width = m_window->getSize().x;
    title.setPosition((window_width - text_width) / 2, PADDING_SIZE);
    m_window->draw(title);

    // rysowanie opcji gry


    // rysowanie guzika z instrukcjami 


    // rysowanie guzika do rozpoczęcia gry
    
}

void StateMenu::initializeOptions()
{
    
}