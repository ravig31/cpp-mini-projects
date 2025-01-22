#pragma once
#include <cassert>
#include <iostream>

class Tile
{
  public:
	Tile(int value) : m_value{ value } { assert(value >= 0 && value < 16); }
	Tile() : m_value{ 0 } {}

	int getNum() const { return m_value; }
	bool isEmpty() const { return m_value == 0; }

	friend std::ostream &operator<<(std::ostream &out, const Tile &tile)
	{
		if (tile.isEmpty())
		{
			out << "    ";
			return out;
		}
		if (tile.m_value < 10)
		{
			out << "  " << tile.m_value << " ";
		}
		else
		{
			out << " " << tile.m_value << " ";
		}
		return out;
	}

  private:
	int m_value;
};