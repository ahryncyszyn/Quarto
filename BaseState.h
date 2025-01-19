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

struct Global;

// Abstrakcyjna klasa, z której będą dziedziczyć wszystkie możliwe stany gry (np. menu/granie/pauza/end-screen)

class BaseState {
    private:
        StateType m_type;               // rodzaj stanu gry
    
    protected:
        Global* m_globalContext;     // ptr do okna, żeby rysować w funkcji draw()

    public:
        BaseState(Global* context, const StateType& type)
            : m_globalContext(context), m_type(type) { };
        virtual ~BaseState() = default;

        // Czysto wirtualne funkcje, które stany gry będą musiały implementować
        virtual void processInput(const sf::Event&) = 0;
        virtual void update() = 0;
        virtual void draw() const = 0;
};