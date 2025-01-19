#pragma once

#include "Global.h"
#include "BaseState.h"
#include <memory>


class StateManager {
    private: 
        std::unique_ptr<BaseState> m_currentState = nullptr;
        std::unique_ptr<BaseState> m_nextState = nullptr;
        Global* m_globalContext = nullptr;

    public:
        StateManager(Global* context)
            : m_globalContext(context) { }
        void changeState();
        template <typename T> void initNextState();


        BaseState* getNextState();
        void processInput(const sf::Event& event);
        void update();
        void draw() const;
};

inline void StateManager::changeState()
{
    if(!m_nextState) return;
    m_currentState.reset(nullptr);
    m_currentState = std::move(m_nextState);
}

template <typename T>
inline void StateManager::initNextState()
{
    m_nextState = std::make_unique<T>(m_globalContext);
}

inline BaseState* StateManager::getNextState() {
    return m_nextState.get();
}
