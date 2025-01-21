
#include "ToggleButton.h"

ToggleButton::ToggleButton(const sf::Vector2f& size, const sf::Vector2f& position,
                           const sf::String& newTextOFF, const sf::String& newTextON, 
                           const sf::Font& font)
    : button(sf::Vector2f(50, 10)), isHardMode(false) 
{
    
    // inicjalizowanie ksztaltu
    button.setPosition(position);
    button.setSize(size);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(3);
    button.setFillColor(normalColor);

    circle.setPosition(position);
    circle.move(4, 4);
    float radius = button.getSize().y / 2.0 - 4;
    circle.setRadius(radius);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::Black);
    circle.setFillColor(sf::Color(128, 128, 128, 128));

    textON.setString(newTextON);
    textOFF.setString(newTextOFF);
    textON.setFont(font);
    textOFF.setFont(font);
    textON.setCharacterSize(25);
    textOFF.setCharacterSize(25);
    textON.setFillColor(sf::Color::Black);
    textOFF.setFillColor(sf::Color::Black);

    // wysrodkowanie napisu on
    sf::FloatRect textBoundsON = textON.getLocalBounds();
    textON.setOrigin(textBoundsON.left + textBoundsON.width / 2.0f,
                    textBoundsON.top + textBoundsON.height / 2.0f);
    textON.setPosition(position + size / 2.0f);

    // wysrodkowanie napisu off
    sf::FloatRect textBoundsOFF = textOFF.getLocalBounds();
    textOFF.setOrigin(textBoundsOFF.left + textBoundsOFF.width / 2.0f,
                    textBoundsOFF.top + textBoundsOFF.height / 2.0f);
    textOFF.setPosition(position + size / 2.0f);
}

void ToggleButton::draw(sf::RenderWindow& window) const
{
    window.draw(button);
    window.draw(circle);
    window.draw(isHardMode ? textON : textOFF);
}

void ToggleButton::handleClick(const sf::Vector2i& mousePos, const sf::Event::MouseButtonEvent& mouseEvent) 
{
    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        toggleMode();
    }
}

void ToggleButton::toggleMode() 
{
    isHardMode = !isHardMode;
    button.setFillColor(isHardMode ? activeColor : normalColor);
    circle.move(isHardMode ? 340.f : -340.f, 0.f);
}