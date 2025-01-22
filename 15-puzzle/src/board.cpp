#include "board.h"
#include "constants.h"

// clang-format off
Board::Board()
    : m_tiles{{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    }}
{}
// clang-format on

void Board::randomize()
{
	for (int i{ 0 }; i < Constants::g_randomisationDepth; i++)
	{
		Direction dir{ generateRandomDirection() };
		this->moveTile(dir);
	}
}

void Board::moveTile(Direction direction)
{
	Point empty_tile{ Board::getEmptyTileLocation() };
	Point adjacent{ empty_tile.getAdjacentPoint(-direction) };

	if (adjacent.getX() < 0 || adjacent.getX() > 3 || adjacent.getY() < 0 || adjacent.getY() > 3)
	{
		return;
	}

	std::swap(getTileAtPoint(empty_tile), getTileAtPoint(adjacent));
}

Tile &Board::getTileAtPoint(Point &point)
{
	assert(point.getX() >= 0 && point.getX() < 4 && point.getY() >= 0 && point.getY() < 4);
	return m_tiles[point.getY()][point.getX()];
}

Point Board::getEmptyTileLocation()
{
	for (size_t y{ 0 }; y < 4; y++)
	{
		for (size_t x{ 0 }; x < 4; x++)
		{
			if (m_tiles[y][x].isEmpty())
				return Point(x, y);
		}
	}
	assert(false && "No empty tile found - board is in invalid state");
	return Point{ 0, 0 };
}

std::ostream &operator<<(std::ostream &out, const Board &board)
{
	for (int i{ 0 }; i < Constants::g_consoleLines; i++)
		out << '\n';

	for (size_t y{ 0 }; y < 4; y++)
	{
		for (size_t x{ 0 }; x < 4; x++)
		{
			out << board.m_tiles[y][x];
		}
		out << '\n';
	}
	return out;
}