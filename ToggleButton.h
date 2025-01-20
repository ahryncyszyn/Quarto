#pragma only

#include <SFML/Graphics.hpp>

class ToggleButton {
public:
    ToggleButton(const sf::Vector2f& size, const sf::Vector2f& position,
                 const sf::String& textOFF, const sf::String& textON,
                 const sf::Font& font);
    void draw(sf::RenderWindow& window) const;
    void handleClick(const sf::Vector2i& mousePos, const sf::Event::MouseButtonEvent& mouseEvent);

private:
    sf::RectangleShape button;
    sf::CircleShape circle;
    sf::Text textON;
    sf::Text textOFF;
    bool isHardMode;

    const sf::Color normalColor = sf::Color(128, 128, 128, 60);
    const sf::Color activeColor = sf::Color(128, 0, 0, 60);

    void toggleMode();
};