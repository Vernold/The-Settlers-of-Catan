#include "Coord.h"

Coord::Coord()
{}

Coord::Coord(int x, int y): _x(x), _y(y)
{}

Coord::Coord(const Coord &c)
{
    _x = c.x();
    _y = c.y();
}

bool
Coord::operator==(const Coord c) const noexcept
{
    return _x == c.x() && _y == c.y();
}

bool
Coord::operator!=(const Coord c) const noexcept
{
    return _x != c.x() || _y != c.y();
}

bool
Coord::operator<(const Coord c) const noexcept
{
    return _x < c.x() || (_x == c.x() && _y < c.y());
}

Coord
Coord::operator+(const Coord c) const noexcept
{
    return Coord(_x + c.x(), _y + c.y());
}

int
Coord::x() const noexcept
{
    return _x;
}

int
Coord::y() const noexcept
{
    return _y;
}
