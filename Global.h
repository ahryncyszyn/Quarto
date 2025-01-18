#pragma once

class StateManager;
namespace sf {
    class RenderWindow;
    class Font;
}

struct Global {
    StateManager* m_states;
    sf::RenderWindow* m_window;
};