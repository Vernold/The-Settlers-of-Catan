#ifndef Coord_h
#define Coord_h

/*@
 true
@*/

class Coord
{
    int _x = 0;
    int _y = 0;

public:
    Coord();
    Coord(int, int);
    Coord(const Coord &);
    
    bool operator==(const Coord) const noexcept;
    bool operator!=(const Coord) const noexcept;
    bool operator<(const Coord) const noexcept;
    Coord operator+(const Coord) const noexcept;
    
    int x() const noexcept;
    int y() const noexcept;
};

#endif /* Coord_h */
