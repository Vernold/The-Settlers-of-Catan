#ifndef FirstEngine_h
#define FirstEngine_h

#include "SupportEngine.h"

class FirstEngine: public SupportEngine
{
    std::map<const std::string, size_t> resources_to_drop;
    
public:
    FirstEngine(Game &, size_t &);
    
    GameStage make_dice(const std::string &, size_t);
    GameStage drop_resource(const std::string &, Resource);
    GameStage move_robber(const std::string &, Coord);
    GameStage rob(const std::string &, const std::string &);
};

#endif /* FirstEngine_h */
