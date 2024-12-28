#pragma once

namespace sf {
    class RenderWindow;
    class Event;
}

enum class StateType {
    Menu,
    Play,
    GameEnd
};

// Abstrakcyjna klasa, z której będą dziedziczyć wszystkie możliwe stany gry (np. menu/granie/pauza/end-screen)

class BaseState {
    private:
        StateType m_type;               // rodzaj stanu gry
    
    protected:
        sf::RenderWindow* m_window;     // ptr do okna, żeby rysować w funkcji draw()

    public:
        BaseState(sf::RenderWindow* window, const StateType& type)
            : m_window(window), m_type(type) { };
        virtual ~BaseState() = default;

        // Czysto wirtualne funkcje, które stany gry będą musiały implementować
        virtual void processInput(const sf::Event&) = 0;
        virtual void update() = 0;
        virtual void draw() const = 0;
};