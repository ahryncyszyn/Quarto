#pragma once

#include "BaseState.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <memory>

class StateMenu : public BaseState {

    static const int PADDING_SIZE = 50;
    static const int WINDOW_WIDTH = 650;
    static const int WINDOW_HEIGHT = 825;

    public:
        StateMenu(Global* context);
        void processInput(const sf::Event&) final;
        void update() final;
        void draw() const final;

    private:

        sf::Font m_font;                      // czcionka do wyświetlania tekstu
        sf::Texture m_backgroundTexture;      // tło menu
        std::vector<sf::Text> m_optionTexts;  // tekst opcji wyświetlany na ekranie

        // todo: jak inicjalizować guziki?
        //Button instructionsButton;
        //Button startButton;
        //Button exitButton;

};