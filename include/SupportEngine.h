#ifndef SupportEngine_h
#define SupportEngine_h

#include "Game.h"
#include "GameStage.h"

enum {
    INIT_RESOURCE_NUMBER = 19,
    INIT_ROAD_NUMBER = 5,
    INIT_TOWN_NUMBER = 5,
    INIT_CITY_NUMBER = 4,
    
    MIN_PLAYERS = 3,
    MAX_PLAYERS = 4,
    
    BORDER = 2,
    
    ROB_DICE = 7,
    MIN_DICE = 2,
    MAX_DICE = 12,
    
    RESOURCE_KINDS = 5,
    
    EXCHANGE_WITH_FIELD_NUM = 4,
    
    WIN_POINTS = 4
};

/*@
 _current_player < _game.num_players()
@*/

class SupportEngine
{
protected:
    Game &_game;
    size_t &_current_player;
    
public:
    SupportEngine(Game &, size_t &);

protected:
    bool road_adjoins_locality(Coord, CrossCorner, Coord, RoadSide) const noexcept;
    bool locality_adjoins_locality(Coord, CrossCorner) const noexcept;
    bool robber_adjoins_locality() const;
    
    bool locality_in_field_range(Coord, CrossCorner) const noexcept;
    bool road_in_field_range(Coord, RoadSide) const noexcept;
    
    bool locality_is_hear(const Player &, Coord, CrossCorner) const noexcept;
    bool road_is_hear(const Player &, Coord, RoadSide) const noexcept;
    
    void issue_resource(Player &, Coord, Coord, CrossCorner);
    void gather_resource(Player &, Coord);
    Player &get_player(const std::string player_name) const;
    
    bool check_infrastructure_set() const noexcept;
};

#endif /* SupportEngine_h */
