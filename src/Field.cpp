#include "Field.h"

Field::Field(): _bank(new ResourcesHolder())
{}

ResourcesHolder &
Field::bank() const noexcept
{
    return *_bank;
}

Hex &
Field::put_hex(Coord c)
{
    if (hexes.count(c)){
        throw std::logic_error("The hex already exists here");
    }
    hexes[c] = std::unique_ptr<Hex>(new Hex());
    
    return *hexes.at(c);
}

void
Field::remove_hex(Coord c)
{
    if (!hexes.count(c)){
        throw std::logic_error("The hex does not exist here");
    }
    delete hexes[c].release();
    hexes.erase(c);
}

Hex &
Field::hex(Coord c) const
{
    if (!hexes.count(c)){
        throw std::logic_error("The hex does not exist here");
    }
    return *hexes.at(c);
}

Coord
Field::coord(Hex &hex) const
{
    for (auto elem = hexes.begin(); elem != hexes.end(); elem++){
        if (&hex == elem->second.get()){
            return elem->first;
        }
    }
    throw std::logic_error("The hex does not exist");
}

bool
Field::has_hex(Coord c) const noexcept
{
    return hexes.count(c) != 0;
}

size_t
Field::num_hexes() const noexcept
{
    return hexes.size();
}

Hex &
Field::hex(size_t i) const
{
    if (i >= hexes.size()){
        throw std::out_of_range("There is no such hex in the field");
    }
    
    return *std::next(hexes.begin(), i)->second;
}

void
Field::link_road(Road &r, Coord c, RoadSide rs)
{
    RoadCoord rc = std::make_pair(c, rs);
    
    if (!roads.count(rc) && !linked(r)){
        roads[rc] = &r;
    } else {
        throw std::logic_error("Cannot link the road with the field");
    }
}

void
Field::unlink_road(Coord c, RoadSide rs)
{
    RoadCoord rc = std::make_pair(c, rs);
    
    if (!roads.count(rc)){
        throw std::logic_error("The road is not linked");
    }
    roads.erase(rc);
}

void
Field::unlink_road(Road &r)
{
    for (auto road : roads){
        if (&r == road.second){
            roads.erase(road.first);
            return;
        }
    }
    throw std::logic_error("The road is not linked");
}

bool
Field::has_road(Coord c, RoadSide rs) const noexcept
{
    RoadCoord rc = std::make_pair(c, rs);
    
    return roads.count(rc) != 0;
}

Road &
Field::road(Coord c, RoadSide rs) const
{
    RoadCoord rc = std::make_pair(c, rs);
    
    if (!roads.count(rc)){
        throw std::logic_error("The road is not linked");
    }
    return *roads.at(rc);
}

RoadCoord
Field::coord(Road &r) const
{
    for (auto road : roads){
        if (&r == road.second){
            return road.first;
        }
    }
    throw std::logic_error("The road is not linked");
}

void Field::
link_locality(Locality &l, Coord c, CrossCorner cc)
{
    LocalityCoord lc = std::make_pair(c, cc);
    
    if (!localities.count(lc) && !linked(l)){
        localities[lc] = &l;
    } else {
        throw std::logic_error("Cannot link the locality with the field");
    }
}

void
Field::unlink_locality(Coord c, CrossCorner cc)
{
    LocalityCoord lc = std::make_pair(c, cc);
    
    if (!localities.count(lc)){
        throw std::logic_error("The locality is not linked");
    }
    localities.erase(lc);
}

void
Field::unlink_locality(Locality &l)
{
    for (auto locality : localities){
        if (&l == locality.second){
            localities.erase(locality.first);
            return;
        }
    }
    throw std::logic_error("The locality is not linked");
}

bool
Field::has_locality(Coord c, CrossCorner cc) const noexcept
{
    LocalityCoord lc = std::make_pair(c, cc);
    
    return localities.count(lc) != 0;
}

Locality &
Field::locality(Coord c, CrossCorner cc) const
{
    LocalityCoord lc = std::make_pair(c, cc);
    
    if (!localities.count(lc)){
        throw std::logic_error("The locality is not linked");
    }
    return *localities.at(lc);
}

LocalityCoord
Field::coord(Locality &l) const
{
    for (auto locality : localities){
        if (&l == locality.second){
            return locality.first;
        }
    }
    throw std::logic_error("The locality is not linked");
}

bool
Field::linked(const Infrastructure &i) const noexcept
{
    if (i.is_road()){
        for (auto road : roads){
            if (&i == road.second){
                return true;
            }
        }
    } else {
        for (auto locality : localities){
            if (&i == locality.second){
                return true;
            }
        }
    }
    return false;
}

void
Field::set_robber(Coord c) noexcept
{
    _robber.first = true;
    _robber.second = c;
}

void
Field::unset_robber()
{
    if (!_robber.first) {
        throw std::logic_error("The robber is not set");
    }
    _robber.first = false;
    _robber.second = Coord(0, 0);
}

bool
Field::has_robber() const noexcept
{
    return _robber.first;
}

Coord
Field::robber() const{
    if (!_robber.first) {
        throw std::logic_error("The robber is not set");
    }
    return _robber.second;
}