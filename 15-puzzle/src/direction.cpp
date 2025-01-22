#include "direction.h"
#include <random>

Direction::Direction(Type type)
{
    switch (type) {
        case Type::up:
            m_dx = 0;
            m_dy = -1;
            break;
        case Type::down:
            m_dx = 0;
            m_dy = 1;
            break;
        case Type::left:
            m_dx = -1;
            m_dy = 0;
            break;
        case Type::right:
            m_dx = 1;
            m_dy = 0;
            break;
    }
    m_type = type;
}

Direction generateRandomDirection()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 3);
    int rand = dist(rd);

    switch (rand) {
        case 0: return Direction(Direction::Type::up);
        case 1: return Direction(Direction::Type::down);
        case 2: return Direction(Direction::Type::left);
        case 3: return Direction(Direction::Type::right);
        default: return Direction(Direction::Type::up);
    }
}

Direction::Type getDirectionFromChar(char cmd)
{
    if (cmd == 'w') return Direction::Type::up;
    if (cmd == 's') return Direction::Type::down;
    if (cmd == 'a') return Direction::Type::left;
    if (cmd == 'd') return Direction::Type::right;
    return {};
}

std::string_view getDirectionName(const Direction::Type direction)
{
    switch (direction) {
        case Direction::Type::up: return "up";
        case Direction::Type::down: return "down";
        case Direction::Type::left: return "left";
        case Direction::Type::right: return "right";
    }
}

std::ostream& operator<<(std::ostream& out, Direction direction)
{
    out << getDirectionName(direction.m_type);
    return out;
}

