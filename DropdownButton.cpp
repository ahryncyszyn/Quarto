#include "DropdownButton.h"

DropdownButton::DropdownButton(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& title, const sf::Font& font)
    : isDropdownOpen(false), selectedIndex(-1), font(font) {
    
    // glowny przycisk
    button.setSize(size);
    button.setPosition(position);
    button.setFillColor(sf::Color::White);
    buttonText.setFont(font);
    buttonText.setString(title);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);

    // centrowanie tekstu na przycisku
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2, 
                         textBounds.top + textBounds.height / 2);
    buttonText.setPosition(position + size / 2.0f);

    // ksztalt z opcjami do wyboru
    dropdownBox.setPosition(position);
    dropdownBox.setSize({ size.x, 0 });
    dropdownBox.setFillColor(sf::Color(200, 200, 200));
}

void DropdownButton::draw(sf::RenderWindow& window) const {
    window.draw(button);
    window.draw(buttonText);

    // rysowanie opcji jezeli sa rozwiniete
    if (isDropdownOpen) {
        window.draw(dropdownBox);
        for (const auto& option : optionTexts) {
            window.draw(option);
        }
    }
}

void DropdownButton::handleClick(const sf::Event& event, const sf::Vector2i& mousePos) {
    
    if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) 
    {
        toggleDropdown();
    } else if (isDropdownOpen) 
    {
        // sprawdzanie czy ktoras z opcji zostala kliknieta
        for (size_t i = 0; i < optionTexts.size(); ++i) 
        {
            if (optionTexts[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) 
            {
                selectedIndex = i;
                buttonText.setString(optionTexts[i].getString());
                closeDropdown();
                break;
            }
        }
    }
}

void DropdownButton::setOptions(const std::vector<std::string>& options) {
    optionTexts.clear();

    sf::Vector2f button_position = button.getPosition();
    sf::Vector2f button_size = button.getSize();
    float padding = 5.0f;

    // dostosowanie rozmiaru w zaleznosci od ilosci opcji
    dropdownBox.setSize({ button_size.x, button_size.y * static_cast<float>(options.size()) });
    dropdownBox.setFillColor(sf::Color::White);
    dropdownBox.setPosition(button_position.x, button_position.y + padding);

    for (size_t i = 0; i < options.size(); ++i) 
    {
        sf::Text option;
        option.setFont(font);
        option.setString(options[i]);
        option.setCharacterSize(20);
        option.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = option.getLocalBounds();
        option.setOrigin(textBounds.left, textBounds.top + textBounds.height / 2);
        option.setPosition(button_position.x, button_position.y + button_size.y * (i + 1) + padding * (i + 1));

        optionTexts.push_back(option);
    }
}

int DropdownButton::getSelectedIndex() const {
    return selectedIndex;
}

std::string DropdownButton::getSelectedOption() const {
    if (selectedIndex >= 0 && selectedIndex < static_cast<int>(optionTexts.size())) {
        return optionTexts[selectedIndex].getString();
    }
    return "";
}

void DropdownButton::toggleDropdown() {
    isDropdownOpen = !isDropdownOpen;
}

void DropdownButton::closeDropdown() {
    isDropdownOpen = false;
}
