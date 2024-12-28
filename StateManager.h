#pragma once

#include "Global.h"
#include "BaseState.h"
#include <memory>


class StateManager {
    private: 
        std::unique_ptr<BaseState> m_currentState = nullptr;
        Global* m_globalContext = nullptr;

    public:
        StateManager(Global* context)
            : m_globalContext(context) { }
        template <typename T> void changeState();

        void processInput(const sf::Event& event);
        void update();
        void draw() const;
};

template <typename T>
inline void StateManager::changeState()
{
    m_currentState = std::make_unique<T>(m_globalContext->m_window);
}
