
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
    circle.move(3, 3);
    float radius = button.getSize().y / 2.0 - 3;
    circle.setRadius(radius);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::Black);
    circle.setFillColor(sf::Color(255, 255, 255, 60));

    textON.setString(newTextON);
    textOFF.setString(newTextOFF);
    textON.setFont(font);
    textOFF.setFont(font);
    textON.setCharacterSize(24);
    textOFF.setCharacterSize(24);
    textON.setFillColor(sf::Color::Black);
    textOFF.setFillColor(sf::Color::Black);

    // centrowanie tekstu
    sf::FloatRect textBoundsON = textON.getLocalBounds();
    textON.setOrigin(textBoundsON.left + textBoundsON.width / 2, 
                   textBoundsON.top + textBoundsON.height / 2);
    textON.setPosition(position + size / 2.0f);

    sf::FloatRect textBoundsOFF = textOFF.getLocalBounds();
    textOFF.setOrigin(radius + textBoundsOFF.left + textBoundsOFF.width / 2, 
                   textBoundsOFF.top + textBoundsOFF.height / 2);
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