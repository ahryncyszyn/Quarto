#pragma once

#include "BaseState.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <memory>

class StateMenu : public BaseState {

    static const int PADDING_SIZE = 50;
    static const int WINDOW_WIDTH = 650;
    static const int WINDOW_HEIGHT = 825;

    public:
        StateMenu(sf::RenderWindow* window = nullptr);
        void processInput(const sf::Event&) final;
        void update() final;
        void draw() const final;

    private:
        void initializeOptions();
        
        std::vector<std::string> m_options;   // lista opcji w menu
        int m_selectedOption;                 // aktualnie wybrana opcja
        sf::Font m_font;                      // czcionka do wyświetlania tekstu
        std::vector<sf::Text> m_optionTexts;  // tekst opcji wyświetlany na ekranie

};