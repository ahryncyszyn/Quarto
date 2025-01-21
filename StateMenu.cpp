#include "StateMenu.h"
#include "DropdownButton.h"
#include "Global.h"
#include "StateManager.h"
#include "StatePlay.h"
//#include "smart_bot.h"

#include <iostream>
#include <vector>

constexpr float BUTTON_HEIGHT = 60.f;
constexpr float BUTTON_WIDTH = 320.f;

StateMenu::StateMenu(Global* context)
    : BaseState(context, StateType::Menu),
    
    modeButton({400, BUTTON_HEIGHT},
                {context->m_window->getSize().x / 2 - 400.f / 2, 220},
                "NORMAL SETTINGS", "ADVANCED SETTINGS", *context->m_font),
    multiplButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 295}, 
                "MULTIPLAYER MODE", *context->m_font),
    easyButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 370}, 
                "EASY MODE", *context->m_font),
    mediumButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 445}, 
                "MEDIUM MODE", *context->m_font),
    hardButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 520}, 
                "HARD MODE", *context->m_font),
    instructionsButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 595}, 
                "INSTRUCTIONS", *context->m_font),
    exitButton({BUTTON_WIDTH, BUTTON_HEIGHT}, 
                {context->m_window->getSize().x / 2 - BUTTON_WIDTH / 2, 695}, 
                "EXIT", *context->m_font)
{
    // wczytywanie tła
    if (!backgroundTexture.loadFromFile("images/menu_background.png")) {
        std::cerr << "Loading background graphics unsuccessful" << std::endl;
    }

    if (!instructionsFont.loadFromFile("CormorantGaramond.ttf")){
        std::cerr << "Loading instruction font unsuccessful" << std::endl;
    }

}

void StateMenu::processInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        
        // sprawdzenie pozycji klikniecia
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_globalContext->m_window);

        modeButton.handleClick(mousePos, event.mouseButton);

        // sprawdzenie, czy klikniecie nastapilo na guziku z instrukcjami
        if (instructionsButton.isClicked(mousePos, event.mouseButton)) {
            showInstructions();
        }

        // sprawdzenie, czy klikniecie nastapilo na guziku do rozpoczecia gry
        if (multiplButton.isClicked(mousePos, event.mouseButton)) {
            bool advancedMode = modeButton.getHardMode();
            m_globalContext->m_states->initNextState<StatePlay>(advancedMode);
            m_globalContext->m_states->changeState();
            return;
        }
        if (easyButton.isClicked(mousePos, event.mouseButton))
        {
            bool advancedMode = modeButton.getHardMode();
            m_globalContext->m_states->initNextState<StatePlay>(advancedMode);
            auto* nextState = dynamic_cast<StatePlay*>(m_globalContext->m_states->getNextState());
            nextState->setupPlayersForMode("easyBot");
            m_globalContext->m_states->changeState();
            return;
        }
        if (mediumButton.isClicked(mousePos, event.mouseButton))
        {
            // TODO: przekierowanie do gry z botem medium
        }
        if (hardButton.isClicked(mousePos, event.mouseButton))
        {
            bool advancedMode = modeButton.getHardMode();
            m_globalContext->m_states->initNextState<StatePlay>(advancedMode);
            auto* nextState = dynamic_cast<StatePlay*>(m_globalContext->m_states->getNextState());
            nextState->setupPlayersForMode("hardBot");
            m_globalContext->m_states->changeState();
            return;
        }

        // sprawdzenie, czy klikniecie nastapilo na guziku do wyjscia
        if (exitButton.isClicked(mousePos, event.mouseButton)) {
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
    // rysowanie tła
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setScale(1.75, 1.75);
    m_globalContext->m_window->draw(background);

    // rysowanie napisu Quarto! na gorze
    sf::Text title;
    title.setFont(*m_globalContext->m_font);
    title.setString("Quarto!");
    title.setCharacterSize(120);
    title.setFillColor(sf::Color::Black);
    float text_width = title.getLocalBounds().width;
    float window_width = m_globalContext->m_window->getSize().x;
    title.setPosition((window_width - text_width) / 2, PADDING_SIZE);
    m_globalContext->m_window->draw(title);

    // rysowanie wszystkich przyciskow
    modeButton.draw(*m_globalContext->m_window);
    multiplButton.draw(*m_globalContext->m_window);
    easyButton.draw(*m_globalContext->m_window);
    mediumButton.draw(*m_globalContext->m_window);
    hardButton.draw(*m_globalContext->m_window);
    instructionsButton.draw(*m_globalContext->m_window);
    exitButton.draw(*m_globalContext->m_window);
}

void StateMenu::showInstructions()
{
    // wyswietla nowe okno z instrucjami
    sf::RenderWindow instructionsWindow(sf::VideoMode(600, 350), "Instructions", sf::Style::Titlebar | sf::Style::Close);
    sf::Text instructionsText;
    instructionsText.setFont(instructionsFont);
    instructionsText.setString(
        "\n"
        "OBJECTIVE: be the first one to create a line (horizontal, vertical, \n"
        "or diagonal) of four pieces that share at least one common attribute: \n"
        "color, shape, height, or fill.\n\n"
        "GAMEPLAY: players take turns placing pieces, but they can only place\n"
        "the piece selected by their opponent in the previous turn.\n\n"
        "GAME MODES:\n"
        "- Multiplayer Mode: take turns playing with a friend.\n"
        "- Easy, Medium, and Hard Modes: challenge yourself against bots \n"
        " of varying difficulty levels.\n"
    );
    instructionsText.setCharacterSize(20);
    instructionsText.setFillColor(sf::Color::Black);
    instructionsText.setPosition(20, 20);

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(instructionsWindow.getSize().x, instructionsWindow.getSize().y));
    background.setFillColor(sf::Color(193, 154, 107));

    instructionsWindow.clear();
    instructionsWindow.draw(background);
    instructionsWindow.draw(instructionsText);
    instructionsWindow.display();

    while (instructionsWindow.isOpen()) {
        sf::Event event;

        // zamyka okno
        while (instructionsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                instructionsWindow.close();
            }
        }
    }
}
