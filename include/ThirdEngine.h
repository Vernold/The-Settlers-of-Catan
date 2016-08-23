#ifndef ThirdEngine_h
#define ThirdEngine_h

#include "SupportEngine.h"

/*@
 true
@*/

class ThirdEngine: public SupportEngine
{    
public:
    ThirdEngine(Game &, size_t &);
    
    void build_road(const std::string &, const std::string &, Coord, RoadSide);
    void build_town(const std::string &, const std::string &, Coord, CrossCorner);
    void build_city(const std::string &, const std::string &, Coord, CrossCorner);
    GameStage next_player(const std::string &);
    
    const Player &winner() const noexcept;
};

#endif /* ThirdEngine_h */
