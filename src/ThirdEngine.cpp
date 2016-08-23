#include "ThirdEngine.h"

ThirdEngine::ThirdEngine(Game &game, size_t &current): SupportEngine(game, current)
{}

void
ThirdEngine::build_road(const std::string &player_name, const std::string &road_name, Coord road_coord, RoadSide road_side)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    
    Player &player = _game.player(_current_player);
    int road_num = -1;
    
    for (uint i = 0; i < player.num_roads(); i++){
        if (player.road(i).name() == road_name){
            road_num = i;
        }
    }
    if (road_num < 0){
        throw std::invalid_argument("The player does not have such road");
    }
    
    Road &road = player.road(road_num);
    
    if (!player.bank().resources(Resource::CLAY) || !player.bank().resources(Resource::WOOD)){
        throw std::invalid_argument("The player does not have enough resources");
    }
    
    Field &field = _game.field();
    
    if (field.linked(road)){
        throw std::invalid_argument("The road has already been linked");
    }
    if (!road_in_field_range(road_coord, road_side)){
        throw std::invalid_argument("Attempt to build out of the field");
    }
    if (road_side == RoadSide::UP){
        if (!road_is_hear(player, road_coord, RoadSide::RIGHT) &&
            !road_is_hear(player, road_coord + Coord(0, 1), RoadSide::DOWN) &&
            !road_is_hear(player, road_coord + Coord(-1, 1), RoadSide::RIGHT) &&
            !road_is_hear(player, road_coord + Coord(-1, 1), RoadSide::DOWN) &&
            !locality_is_hear(player, road_coord, CrossCorner::TOP) &&
            !locality_is_hear(player, road_coord + Coord(0, 1), CrossCorner::BOTTOM)){
            throw std::invalid_argument("The player cannot build here");
        }
    } else if (road_side == RoadSide::RIGHT){
        if (!road_is_hear(player, road_coord, RoadSide::UP) &&
            !road_is_hear(player, road_coord, RoadSide::DOWN) &&
            !road_is_hear(player, road_coord + Coord(0, 1), RoadSide::DOWN) &&
            !road_is_hear(player, road_coord + Coord(1, -1), RoadSide::UP) &&
            !locality_is_hear(player, road_coord + Coord(1, -1), CrossCorner::TOP) &&
            !locality_is_hear(player, road_coord + Coord(0, 1), CrossCorner::BOTTOM)){
            throw std::invalid_argument("The player cannot build here");
        }
    } else {
        if (!road_is_hear(player, road_coord, RoadSide::RIGHT) &&
            !road_is_hear(player, road_coord + Coord(0, -1), RoadSide::UP) &&
            !road_is_hear(player, road_coord + Coord(0, -1), RoadSide::RIGHT) &&
            !road_is_hear(player, road_coord + Coord(1, -1), RoadSide::UP) &&
            !locality_is_hear(player, road_coord + Coord(1, -1), CrossCorner::TOP) &&
            !locality_is_hear(player, road_coord, CrossCorner::BOTTOM)){
            throw std::invalid_argument("The player cannot build here");
        }
    }

    field.link_road(road, road_coord, road_side);
    
    player.bank().remove(Resource::WOOD, 1);
    player.bank().remove(Resource::CLAY, 1);
    
    field.bank().add(Resource::WOOD, 1);
    field.bank().add(Resource::CLAY, 1);
}

void
ThirdEngine::build_town(const std::string &player_name, const std::string &town_name, Coord town_coord, CrossCorner town_corner)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    
    Player &player = _game.player(_current_player);
    Field &field = _game.field();

    int town_num = -1;
    
    for (uint i = 0; i < player.num_towns(); i++){
        if (player.town(i).name() == town_name){
            town_num = i;
        }
    }
    if (town_num < 0){
        throw std::invalid_argument("The player does not have such town");
    }
    
    Town &town = player.town(town_num);
    
    if (!locality_in_field_range(town_coord, town_corner)){
        throw std::invalid_argument("Attempt to build out of the field");
    }
    if (locality_adjoins_locality(town_coord, town_corner)){
        throw std::invalid_argument("You cannot build here");
    }
    if (field.linked(town)){
        throw std::invalid_argument("The town has been linked");
    }
    if (town_corner == CrossCorner::TOP) {
        if (!road_is_hear(player, town_coord, RoadSide::UP) &&
            !road_is_hear(player, town_coord + Coord(-1, 1), RoadSide::DOWN) &&
            !road_is_hear(player, town_coord + Coord(-1, 1), RoadSide::RIGHT)){
            throw std::invalid_argument("You cannot build here");
        }
    } else {
        if (!road_is_hear(player, town_coord, RoadSide::DOWN) &&
            !road_is_hear(player, town_coord + Coord(0, -1), RoadSide::UP) &&
            !road_is_hear(player, town_coord + Coord(0, -1), RoadSide::RIGHT)){
            throw std::invalid_argument("You cannot build here");
        }
    }
    if (!player.bank().resources(Resource::WOOD) ||
        !player.bank().resources(Resource::WOOL) ||
        !player.bank().resources(Resource::CLAY) ||
        !player.bank().resources(Resource::GRAIN)) {
        throw std::invalid_argument("The player does not have enough resources");
    }
    
    field.link_locality(town, town_coord, town_corner);
    
    player.bank().remove(Resource::CLAY, 1);
    player.bank().remove(Resource::WOOD, 1);
    player.bank().remove(Resource::GRAIN, 1);
    player.bank().remove(Resource::WOOL, 1);
    
    field.bank().add(Resource::WOOD, 1);
    field.bank().add(Resource::CLAY, 1);
    field.bank().add(Resource::GRAIN, 1);
    field.bank().add(Resource::WOOL, 1);
}

        
void
ThirdEngine::build_city(const std::string &player_name, const std::string &city_name, Coord city_coord, CrossCorner city_corner)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    
    Player &player = _game.player(_current_player);
    int city_num = -1;
    
    for (uint i = 0; i < player.num_cities(); i++){
        if (player.city(i).name() == city_name){
            city_num = i;
        }
    }
    if (city_num < 0){
        throw std::invalid_argument("The player does not have such city");
    }
    
    City &city = player.city(city_num);
    Field &field = _game.field();
    
    if (!locality_is_hear(player, city_coord, city_corner) ||
        !field.locality(city_coord, city_corner).is_town()) {
        throw std::invalid_argument("You cannot build here");
    }
    if (player.bank().resources(Resource::ORE) < 3 ||
        player.bank().resources(Resource::GRAIN) < 2){
        throw std::invalid_argument("The player does not have enough resources");
    }

    field.unlink_locality(city_coord, city_corner);
    field.link_locality(city, city_coord, city_corner);
    
    player.bank().remove(Resource::ORE, 3);
    player.bank().remove(Resource::GRAIN, 2);
    
    field.bank().add(Resource::ORE, 3);
    field.bank().add(Resource::GRAIN, 2);
}

GameStage
ThirdEngine::next_player(const std::string &player_name)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    _current_player++;
    _current_player %= _game.num_players();
    return GameStage::STAGE1_DICE;
}

const Player &
ThirdEngine::winner() const noexcept
{
    return _game.player(_current_player);
}