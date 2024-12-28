#pragma once

class StateManager;
namespace sf {
    class RenderWindow;
}

struct Global {
    StateManager* m_states;
    sf::RenderWindow* m_window;
};