#pragma once

#include <iostream>
#include <random>
#include <string_view>

class Direction {
public:
    enum Type {
        up,
        down,
        left,
        right
    };

    explicit Direction(Type type);
    Direction(int x, int y) : m_dx{ x }, m_dy{ y } {}
    
    Direction operator-() const { return Direction(-m_dx, -m_dy); }
    
    int getDx() const { return m_dx; }
    int getDy() const { return m_dy; }
    
    friend std::ostream& operator<<(std::ostream& out, Direction direction);
    
private:
    int m_dx{};
    int m_dy{};
    Type m_type;
};

Direction generateRandomDirection();
Direction::Type getDirectionFromChar(char cmd);
std::string_view getDirectionName(Direction::Type direction);