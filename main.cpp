#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Quarto!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Logika gry. Interfejs ktory obsluguje input
        //i na podstawie game_logic.cpp aktualizuje stan gry
        window.clear();
        //Wysietlanie gry. Rysowanie obiektow itd.
        window.display(); 
    }

    return 0;
}
