#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "StateManager.h"
#include "Global.h"
#include "StatePlay.h"
#include "StateMenu.h"
#include "board.h"


int main() {
    constexpr int windowWidth = 650; // Szerokość obu planszy jest równa
    constexpr int windowHeight = 825; // Wysokość jest sumą wysokości obu planszy

    Global gameContext;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // poprawia jakosc drukowanych okregow na planszy
    gameContext.m_window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Quarto!", sf::Style::Titlebar | sf::Style::Close, settings);
    gameContext.m_states = new StateManager(&gameContext);
    gameContext.m_states->initNextState<StatePlay>();
    gameContext.m_states->changeState();

    // Główna pętla
    // Sama przetwarza tylko zamknięcie okna
    // A resztę zadań oddelegowuje do odpowiedniego stanu gry
    while (gameContext.m_window->isOpen()) {
        sf::Event event;
        while (gameContext.m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameContext.m_window->close();
            } else {
                gameContext.m_states->processInput(event);
            }
        }

        gameContext.m_states->update();

        gameContext.m_window->clear(sf::Color::White);
        gameContext.m_states->draw();        
        gameContext.m_window->display(); 
    }

    return 0;
}


/* 
=============== WYJAŚNIENIA ================
1. gameContext to struktura przechowująca kluczowe elementy gry: stateManager i window
    Różne stany gry potrzebują dostępu do tych dwóch rzeczy, żeby odpowiednio zmienić stan 
    przy spełnieniu jakichś warunków (np. kliknięcie przycisku w menu -> rozpoczęcie gry)
    i żeby rysować w swojej funkcji draw

2. stateManager zarządza aktualnym stanem gry i przez niego wywoływane są właściwe w danym momencie funkcje
    processInput, update, draw

3. dzięki rozróżnieniu stanów gry można spokojnie rozbudowywać funkcjonalność/dostosowywać implementację
     bez zaśmiecania maina

4. Podstawowe klasy bazowe:
    > BaseState
    > Player
    Chcąc stworzyć stan gry, robimy zwykły inherit od BaseState i implementujemy processInput, update, draw
    Chcąc stworzyć bota, robimy inherit od Player i implementujemy placePawn i getNextPiece.
    W kontekscie klasy Player, potencjalnie dobrym rozwiązaniem byłoby zwracanie pożądanych wartości
    i dopiero w ramach StatePlay weryfikacja ruchu i potencjalna
    modyfikacja Board, ale to już zobaczymy, czy nam się będzie chciało


Co bym zmienił, ale na razie mi się nie chciało:
    ** Prawdopodobnie lepiej będzie, jeśli ruch HumanPlayer zaimplementujemy w sumie
       bezpośrednio w StatePlay, wtedy unikniemy dość nienaturalnego przerzucania argumentów
       i dziwnego dziedziczenia i dodawania funkcji

    ** Tworzenie gracza w konstruktorze StatePlay na bazie zadanych argumentów 
       (będzie ważne w przypadku, kiedy będzie zaimplementowany więcej niż 1 rodzaj gracza/botów)
       Lub osobna funkcja tworząca gracza z szablonu
       Alternatywnie, szablon funkcji addPlayer(), właściwie analogiczny do changeState

    ** Stany gry powinny mieć dostęp do globalContext, a nie do samego okna (ze względu na konieczność przełączania)

    ** Zweryfikował, gdzie potrzebne jakie pointery, bo tak na szybko pisząc leciałem na czuja

    ** Być może "wciągnął" większość głównej pętli do StateManager

    ** Ujednolicił format nazewnictwa
*/