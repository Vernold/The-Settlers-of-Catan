#ifndef Field_h
#define Field_h

#include <memory>

#include "Road.h"
#include "Locality.h"
#include "ResourcesHolder.h"
#include "Hex.h"
#include "Coord.h"
#include "RoadSide.h"
#include "CrossCorner.h"

typedef std::pair<Coord, RoadSide> RoadCoord;
typedef std::pair<Coord, CrossCorner> LocalityCoord;
typedef std::pair<bool, Coord> Robber;
/*@
 _bank != nullptr
 &&
 \forall RoadCoord roadcoord; roadcoord \in roads ==> \valid(roads[roadcoord])
 &&
 \forall RoadCoord c1, RoadCoord c2; c1 != c2 && c1 \in roads && c2 \in roads ==> roads[c1] != roads[c2]
 &&
 \forall LocalityCoord loccoord; loccoord \in localities ==> \valid(localities[loccoord])
 &&
 \forall LocalityCoord c1, LocalityCoord c2; c1 != c2 && c1 \in localities && c2 \in localities ==> localities[c1] != localities[c2]
 @*/

class Field
{
    std::unique_ptr<ResourcesHolder> _bank;
    
    std::map<Coord, std::unique_ptr<Hex>> hexes;
    std::map<RoadCoord, Road *> roads;
    std::map<LocalityCoord, Locality *> localities;
    
    Robber _robber = {false, Coord()};
    
public:
    Field();
    
    ResourcesHolder &bank() const noexcept;
    
    Hex &put_hex(Coord);
    void remove_hex(Coord);
    Hex &hex(Coord) const;
    
    Coord coord(Hex &) const;
    bool has_hex(Coord) const noexcept;
    size_t num_hexes() const noexcept;
    Hex &hex(size_t i) const;
    
    void link_road(Road &, Coord, RoadSide);
    void unlink_road(Coord, RoadSide);
    void unlink_road(Road &);
    
    bool has_road(Coord, RoadSide) const noexcept;
    Road &road(Coord, RoadSide) const;
    
    RoadCoord coord(Road &) const;
    
    void link_locality(Locality &, Coord, CrossCorner);
    void unlink_locality(Coord, CrossCorner);
    void unlink_locality(Locality &);
    
    bool has_locality(Coord, CrossCorner) const noexcept;
    Locality &locality(Coord, CrossCorner) const;
    
    LocalityCoord coord(Locality &) const;
    bool linked(const Infrastructure &) const noexcept;
    
    void set_robber(Coord) noexcept;
    void unset_robber();
    bool has_robber() const noexcept;
    Coord robber() const;
    
    Field(const Field &) = delete;
    Field &operator=(const Field &) = delete;
};

#endif /* Field_h */
