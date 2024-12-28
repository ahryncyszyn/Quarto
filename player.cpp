#include "player.h"

void Player::setName(const std::string& name) {
    m_name = name;
}

std::string Player::getName() const {
    return m_name;
}

PlayerType Player::getType() const {
    return m_type;
}