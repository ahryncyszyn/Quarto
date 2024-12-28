#pragma once

#include <string>

class Board;

enum class PlayerType {
    Human,
    Bot
};

// Bazowa klasa określające podstawowe właściwości jakiegokolwiek gracza
// Aby stworzyć bota, zainherituj od klasy Player i zaimplementuj placePawn() i getNextPiece()

class Player {
    private:
        const PlayerType m_type;
        std::string m_name;
    
    public:
        Player(const PlayerType& type, const std::string& name)
            : m_type(type), m_name(name) { }
        ~Player() = default;
            
        virtual void placePawn(Board&) const = 0;
        virtual void getNextPiece(Board&) const = 0;

        // Podstawowe gettery/settery, może się przydadzą, np. przy pisaniu, kto wygrał
        void setName(const std::string& name);
        std::string getName() const;

        PlayerType getType() const;
};