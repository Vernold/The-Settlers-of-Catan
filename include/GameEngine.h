#ifndef GameEngine_h
#define GameEngine_h

#include "IGameEngine.h"
#include "StartEngine.h"
#include "FirstEngine.h"
#include "SecondEngine.h"
#include "ThirdEngine.h"

/*@
 _game != nullptr
 &&
 _current_player < _game.num_players()
 &&
 if (is_start_stage(_stage)) then \valid(start_engine) && first_engine == nullptr && second_engine == nullptr && third_engine == nullptr
 &&
 if (is_first_stage(_stage)) then \valid(first_engine) && start_engine == nullptr && second_engine == nullptr && third_engine == nullptr
 &&
 if (is_second_stage(_stage)) then \valid(second_engine) && first_engine == nullptr && start_engine == nullptr && third_engine == nullptr
 &&
 if (is_third_stage(_stage)) then \valid(third_engine) && first_engine == nullptr && second_engine == nullptr && start_engine == nullptr
 &&
 _game.num_players() <= MAX_PLAYERS
 &&
 if (_stage != PLAYERS_REGISTRATION) then MIN_PLAYERS <= _game.num_players()
 &&
 \forall Player p; p \in Game p.num_roads() <= INIT_ROAD_NUMBER && p.num_towns() <= INIT_TOWN_NUMBER && p.num_cities() <= INIT_CITY_NUMBER
 &&
 if (_stage == PLAYERS_REGISTRATION) then _game.field().num_hexes() == 0 else _game.field().num_hexes() == 19
 &&
 \forall Hex hex; hex \in Field ==> if(field.coord(hex) != Desert) then hex.has_number() && hex.has_resource() else !hex.has_number() && !hex.has_resource()
 &&
 \forall Hex hex; hex \in Field ==> MIN_DICE <= hex.number() <= MAX_DICE
 &&
 \forall Hex hex; hex \in Field && hex.has_number() && (hex.number() == MIN_DICE || hex.number() == MAX_DICE) ==> \count(hex) == 1
 &&
 \forall Hex hex; hex \in Field && hex.has_number() && (hex.number() != MIN_DICE && hex.number() != MAX_DICE) ==> \count(hex) == 2
 &&
 \forall Resource R; R \in _game.field().bank() ==> _game.field().bank().resources(R) <= INIT_RESOURCE_NUMBER
 &&
 if (_stage != PLAYERS_REGISTRATION) then _game.field().has_robber() == true
 &&
 \forall Hex hex; hex \in Field ==>  |field.coord(hex).x()| < 3 && |field.coord(hex).y()| < 3 && (field.coord(hex).x() * field.coord(hex).y()) < 2
@*/

class GameEngine: public IGameEngine
{
    std::unique_ptr<Game> _game;
    GameStage _stage;
    
    std::unique_ptr<StartEngine> start_engine;
    std::unique_ptr<FirstEngine> first_engine;
    std::unique_ptr<SecondEngine> second_engine;
    std::unique_ptr<ThirdEngine> third_engine;
    
    size_t _current_player = 0;
    
public:
    GameEngine();
    
    /*StartEngine*/
    void join_player(const std::string &);
    void start_game();
    
    void register_road(const std::string &, const std::string &);
    void register_town(const std::string &, const std::string &);
    void register_city(const std::string &, const std::string &);
    
    void put_initial_infrastructure(const std::string &, const std::string &, Coord, CrossCorner,
                                    const std::string &, Coord, RoadSide);
    /*FirstEngine*/
    
    void make_dice(const std::string &, size_t);
    void drop_resource(const std::string &, Resource);
    void move_robber(const std::string &, Coord);
    void rob(const std::string &, const std::string &);
    
    /*SecondEngine*/
    
    void exchange_with_field(const std::string &, Resource, Resource);
    int exchange_players_request(const std::string &, const std::string &,
                                 const std::multiset<Resource> &, const std::multiset<Resource> &);
    void exchange_players_accept(const std::string &, int);
    void end_exchanges(const std::string &);
    
    std::set<int> requests() const;
    std::set<int> exchanges() const;
    
    const Player &initiator(int) const;
    const Player &other(int) const;
    
    const std::multiset<Resource> &src(int) const;
    const std::multiset<Resource> &target(int) const;
    
    bool requested(int) const;
    bool performed(int) const;
    
    /*ThirdEngine*/
    
    void build_road(const std::string &, const std::string &, Coord, RoadSide);
    void build_town(const std::string &, const std::string &, Coord, CrossCorner);
    void build_city(const std::string &, const std::string &, Coord, CrossCorner);
    void next_player(const std::string &);
    const Player &winner() const;
    
    /*General*/
    const Game &game() const noexcept;
    GameStage stage() const noexcept;
    int score(const std::string &);
    const Player &current_player() const;
    
    GameEngine(const GameEngine &) = delete;
    GameEngine &operator=(const GameEngine &) = delete;

private:
    void switch_engine();
};

#endif /* GameEngine_h */
