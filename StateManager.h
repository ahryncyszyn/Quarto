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
        template <typename T, typename... Args>
        void initNextState(Args&&... args);


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

template <typename T, typename... Args>
inline void StateManager::initNextState(Args&&... args) {
    if constexpr (std::is_constructible_v<T, Global*, Args...>) {
        m_nextState = std::make_unique<T>(m_globalContext, std::forward<Args>(args)...);
    } else {
        static_assert(std::is_constructible_v<T, Global*, Args...>, "StatePlay requires Global* and bool constructor.");
    }
}

inline BaseState* StateManager::getNextState() {
    return m_nextState.get();
}
