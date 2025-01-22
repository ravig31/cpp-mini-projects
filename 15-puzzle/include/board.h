#pragma once

#include <array>
#include "tile.h"
#include "direction.h"
#include "point.h"

class Board {
    using BoardArray = std::array<std::array<Tile, 4>, 4>;
public:
    Board();
    void randomize();
    void moveTile(Direction direction);
    Tile& getTileAtPoint(Point& point);
    Point getEmptyTileLocation();
    
    friend std::ostream& operator<<(std::ostream& out, const Board& board);
    
private:
    BoardArray m_tiles{};
};