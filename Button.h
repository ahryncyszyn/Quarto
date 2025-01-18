#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button 
{
    public:
        Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::String& text, const sf::Font& font);

        void draw(sf::RenderWindow& window) const;
        void update(const sf::Vector2i& mousePos);
        void setTexture(const sf::Texture& texture, const sf::Texture& hoverTexture);
        bool isClicked(const sf::Vector2i& mousePos, const sf::Event::MouseButtonEvent& mouseEvent) const;
        void setText(const std::string& text);

    private:
        sf::RectangleShape button; 
        sf::Text buttonText;
        const sf::Texture* normalTexture;
        const sf::Texture* hoverTexture;
        bool isHovered;
};