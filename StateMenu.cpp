#include "StateMenu.h"
#include "Global.h"
#include "StateManager.h"
#include "StatePlay.h"

#include <iostream>

constexpr float BUTTON_HEIGHT = 40.f;
constexpr float BUTTON_WIDTH = 200.f;

StateMenu::StateMenu(Global* context)
    : BaseState(context, StateType::Menu),
    startButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 300 }, 
                "Start", *context->m_font),
    instructionsButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 375 }, 
                "Instructions", *context->m_font),
    exitButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 450}, 
                "Exit", *context->m_font)
{
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
        if (instructionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return;
        }

        // sprawdzenie, czy klikniecie nastapilo na guziku do rozpoczecia gry
        if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            m_globalContext->m_states->initNextState<StatePlay>();
            m_globalContext->m_states->changeState();
            return;
        }

        // sprawdzenie, czy klikniecie nastapilo na guziku do wyjscia
        if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            m_globalContext->m_window->close();
            return;
        }
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
    title.setFont(*m_globalContext->m_font);
    title.setString("Quarto!");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Black);

    float text_width = title.getLocalBounds().width;
    float window_width = m_globalContext->m_window->getSize().x;
    title.setPosition((window_width - text_width) / 2, PADDING_SIZE);
    m_globalContext->m_window->draw(title);

    // rysowanie opcji gry
    instructionsButton.draw(*m_globalContext->m_window);
    startButton.draw(*m_globalContext->m_window);
    exitButton.draw(*m_globalContext->m_window);
}