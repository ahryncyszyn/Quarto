#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class DropdownButton {
public:
    DropdownButton(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& title, const sf::Font& font);

    void draw(sf::RenderWindow& window) const;
    void handleClick(const sf::Event& event, const sf::Vector2i& mousePos);
    void setOptions(const std::vector<std::string>& options);
    int getSelectedIndex() const;
    std::string getSelectedOption() const;

private:
    sf::RectangleShape button;           // przycisk
    sf::Text buttonText;                 // tekst przycisku
    sf::Font font;             
    std::vector<sf::Text> optionTexts;   // obiekty z opcjami do wyboru
    sf::RectangleShape dropdownBox;      // ksztalt opcji wyboru

    bool isDropdownOpen;                 // przechowuje informacje czy opcje sa rozwiniete
    int selectedIndex;                   // indeks wybranej opcji

    void toggleDropdown();               // zwija/rozwija opcje
    void closeDropdown();
};