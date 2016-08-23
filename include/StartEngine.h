#ifndef StartEngine_h
#define StartEngine_h

#include "SupportEngine.h"

/*@
 true
@*/

class StartEngine: public SupportEngine
{
    bool order = true;

public:
    StartEngine(Game &, size_t &);
    
    void join_player(const std::string &);
    GameStage start_game();
    
    GameStage register_road(const std::string &, const std::string &);
    GameStage register_town(const std::string &, const std::string &);
    GameStage register_city(const std::string &, const std::string &);
    
    GameStage put_initial_infrastructure(const std::string &, const std::string &, Coord, CrossCorner,
                                         const std::string &, Coord, RoadSide);
};

#endif /* StartEngine_h */


