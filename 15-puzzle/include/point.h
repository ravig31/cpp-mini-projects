#include "direction.h"

class Point
{
  public:
	Point(int x, int y) : m_x{ x }, m_y{ y } {}

	Point getAdjacentPoint(Direction direction)
	{
		return Point(m_x + direction.getDx(), m_y + direction.getDy());
	}

	friend std::ostream &operator<<(std::ostream &out, const Point &point);
	friend bool operator==(const Point &p1, const Point &p2)
	{
		return p1.m_x == p2.m_x && p1.m_y == p2.m_y;
	}
	friend bool operator!=(const Point &p1, const Point &p2) { return !(operator==(p1, p2)); }

	int getX() const { return m_x; }
	int getY() const { return m_y; }

  private:
	int m_x{};
	int m_y{};
};