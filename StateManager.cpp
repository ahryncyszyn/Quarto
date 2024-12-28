#include "StateManager.h"

void StateManager::processInput(const sf::Event& event)
{
    if (m_currentState != nullptr)
        m_currentState->processInput(event);
}

void StateManager::update()
{
    if (m_currentState != nullptr)
        m_currentState->update();
}

void StateManager::draw() const
{
    if (m_currentState != nullptr)
        m_currentState->draw();
}
