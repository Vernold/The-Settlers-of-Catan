#ifndef IGameEngine_h
#define IGameEngine_h

#include <set>
#include "SupportEngine.h"

class IGameEngine
{
public:
    virtual ~IGameEngine(){}
    
    /*StartEngine*/
    virtual void join_player(const std::string &) = 0;
    virtual void start_game() = 0;
    
    virtual void register_road(const std::string &, const std::string &) = 0;
    virtual void register_town(const std::string &, const std::string &) = 0;
    virtual void register_city(const std::string &, const std::string &) = 0;
    
    virtual void put_initial_infrastructure(const std::string &, const std::string &, Coord,
                                            CrossCorner, const std::string &, Coord, RoadSide) = 0;
    /*FirstEngine*/
    
    virtual void make_dice(const std::string &, size_t) = 0;
    virtual void drop_resource(const std::string &, Resource) = 0;
    virtual void move_robber(const std::string &, Coord) = 0;
    virtual void rob(const std::string &, const std::string &) = 0;
    
    /*SecondEngine*/
    
    virtual void exchange_with_field(const std::string &, Resource, Resource) = 0;
    virtual int exchange_players_request(const std::string &, const std::string &,
                                         const std::multiset<Resource> &, const std::multiset<Resource> &) = 0;
    virtual void exchange_players_accept(const std::string &, int) = 0;
    virtual void end_exchanges(const std::string &) = 0;
    
    virtual std::set<int> requests() const = 0;
    virtual std::set<int> exchanges() const = 0;
    
    virtual const Player &initiator(int) const = 0;
    virtual const Player &other(int) const = 0;
    
    virtual const std::multiset<Resource> &src(int) const = 0;
    virtual const std::multiset<Resource> &target(int) const = 0;
    
    virtual bool requested(int) const = 0;
    virtual bool performed(int) const = 0;
    
    /*ThirdEngine*/
    
    virtual void build_road(const std::string &, const std::string &, Coord, RoadSide) = 0;
    virtual void build_town(const std::string &, const std::string &, Coord, CrossCorner) = 0;
    virtual void build_city(const std::string &, const std::string &, Coord, CrossCorner) = 0;
    virtual void next_player(const std::string &) = 0;
    virtual const Player &winner() const = 0;
    
    /*General*/
    virtual const Game &game() const noexcept = 0;
    virtual GameStage stage() const noexcept = 0;
    virtual int score(const std::string &) = 0;
    virtual const Player &current_player() const = 0;
};

#endif /* IGameEngine_h */
