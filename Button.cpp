
#include "Button.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::String& text, const sf::Font& font)
    : button(sf::Vector2f(50, 10)), normalTexture(nullptr), hoverTexture(nullptr), isHovered(false) {
        
    button.setPosition(position);
    button.setSize(size);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(3);
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::Black);

    // kolor wypelnienia
    if (text == "INSTRUCTIONS") button.setFillColor(sf::Color(0, 128, 0, 60));
    else if (text == "EXIT") button.setFillColor(sf::Color(128, 0, 0, 60));
    else button.setFillColor(sf::Color(255, 255, 255, 60));

    // centrowanie tekstu na przycisku
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2, 
                         textBounds.top + textBounds.height / 2);
    buttonText.setPosition(position + size / 2.0f);
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(button);
    window.draw(buttonText);
}

void Button::update(const sf::Vector2i& mousePos) {
    bool hover = button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    if (hover && !isHovered) {
        isHovered = true;
        if (hoverTexture) {
            button.setTexture(hoverTexture);
        } else {
            button.setFillColor(sf::Color::Green);
        }
    } else if (!hover && isHovered) {
        isHovered = false;
        if (normalTexture) {
            button.setTexture(normalTexture);
        } else {
            button.setFillColor(sf::Color::White);
        }
    }
}

void Button::setTexture(const sf::Texture& texture, const sf::Texture& hoverTexture) {
    this->normalTexture = &texture;
    this->hoverTexture = &hoverTexture;
    button.setTexture(normalTexture);
}

bool Button::isClicked(const sf::Vector2i& mousePos, const sf::Event::MouseButtonEvent& mouseEvent) const {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) &&
           mouseEvent.button == sf::Mouse::Left;
}

void Button::setText(const std::string& text) {
    buttonText.setString(text);
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2,
                         textBounds.top + textBounds.height / 2);
}

sf::FloatRect Button::getGlobalBounds() const
{
    return button.getGlobalBounds();
}
