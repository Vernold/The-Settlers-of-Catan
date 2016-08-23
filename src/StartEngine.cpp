#include "StartEngine.h"
#include <queue>

StartEngine::StartEngine(Game &game, size_t &current): SupportEngine(game, current)
{}

void
StartEngine::join_player(const std::string &player_name)
{
    for (uint i = 0; i < _game.num_players(); i++){
        if (_game.player(i).name() == player_name){
            throw std::invalid_argument("The player has already been registered");
        }
    }
    _game.add_player(player_name);
}

GameStage
StartEngine::start_game()
{
    if (_game.num_players() < MIN_PLAYERS || _game.num_players() > MAX_PLAYERS){
        throw std::invalid_argument("Wrong number of players");
    }
    
    Field &field = _game.field();
    
    field.bank().add(Resource::GRAIN, INIT_RESOURCE_NUMBER);
    field.bank().add(Resource::CLAY, INIT_RESOURCE_NUMBER);
    field.bank().add(Resource::ORE, INIT_RESOURCE_NUMBER);
    field.bank().add(Resource::WOOL, INIT_RESOURCE_NUMBER);
    field.bank().add(Resource::WOOD, INIT_RESOURCE_NUMBER);

    std::vector<std::pair<Resource, size_t>> hex_info = {
        {Resource::CLAY, 4}, {Resource::GRAIN, 2}, {Resource::WOOL, 9},
        {Resource::WOOL, 8}, {Resource::GRAIN, 3}, {Resource::ORE, 5},
        {Resource::WOOD, 10}, {Resource::WOOD, 11}, {Resource::ORE, 6},
        {Resource::ORE, 6}, {Resource::WOOD, 11}, {Resource::WOOD, 10},
        {Resource::ORE, 5}, {Resource::GRAIN, 3}, {Resource::WOOL, 8},
        {Resource::WOOL, 9}, {Resource::CLAY, 12}, {Resource::CLAY, 4}
    };
    
    for (int y = -BORDER; y <= BORDER; y++){
        for (int x = -BORDER; x <= BORDER; x++){
            Coord c = Coord(x, y);
            if (x == 0 && y == 0){
                field.put_hex(c);
                field.set_robber(c);
            } else if (x * y < BORDER) {
                auto info = hex_info.back();
                field.put_hex(c);
                field.hex(c).set_resource(info.first);
                field.hex(c).set_number(info.second);
                hex_info.pop_back();
            }
        }
    }
    return GameStage::INFRASTRUCTURES_REGISTRATION;
}

GameStage
StartEngine::register_road(const std::string &player_name, const std::string &road_name)
{
    Player &player = get_player(player_name);
    
    if (player.num_roads() == INIT_ROAD_NUMBER){
        throw std::invalid_argument("The player cannot have more than 15 roads");
    }
    for (uint i = 0; i < player.num_roads(); i++){
        if (player.road(i).name() == road_name){
            throw std::invalid_argument("The road has already been registered");
        }
    }
    player.add_road(road_name);
    if (check_infrastructure_set()){
        return GameStage::PUT_INITIAL_INFRASTRUCTURES;
    }
    return GameStage::INFRASTRUCTURES_REGISTRATION;
}

GameStage
StartEngine::register_town(const std::string &player_name, const std::string &town_name)
{
    Player &player = get_player(player_name);
    
    if (player.num_towns() == INIT_TOWN_NUMBER){
        throw std::invalid_argument("The player cannot have more than 5 towns");
    }
    for (uint i = 0; i < player.num_towns(); i++){
        if (player.town(i).name() == town_name){
            throw std::invalid_argument("The town has already been registered");
        }
    }
    player.add_town(town_name);
    if (check_infrastructure_set()){
        return GameStage::PUT_INITIAL_INFRASTRUCTURES;
    }
    return GameStage::INFRASTRUCTURES_REGISTRATION;
}

GameStage
StartEngine::register_city(const std::string &player_name, const std::string &city_name)
{
    Player &player = get_player(player_name);
    
    if (player.num_cities() == INIT_CITY_NUMBER){
        throw std::invalid_argument("The player cannot have more than 5 towns");
    }
    for (uint i = 0; i < player.num_cities(); i++){
        if (player.city(i).name() == city_name){
            throw std::invalid_argument("The city has already been registered");
        }
    }
    player.add_city(city_name);
    if (check_infrastructure_set()){
        return GameStage::PUT_INITIAL_INFRASTRUCTURES;
    }
    return GameStage::INFRASTRUCTURES_REGISTRATION;
}

GameStage
StartEngine::put_initial_infrastructure(const std::string &player_name,
                                        const std::string &town_name, Coord town_coord, CrossCorner town_corner,
                                        const std::string &road_name, Coord road_coord, RoadSide road_side)
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
    
    if (!locality_in_field_range(town_coord, town_corner) ||
        !road_in_field_range(road_coord, road_side)){
        throw std::invalid_argument("Attempt to build out of the field");
    }
    if (locality_adjoins_locality(town_coord, town_corner)){
        throw std::invalid_argument("The town adjoins the locality");
    }
    if (!road_adjoins_locality(town_coord, town_corner, road_coord, road_side)){
        throw std::invalid_argument("The road does not adjoins the town");
    }
    Field &field = _game.field();
    
    if (field.linked(town) || field.linked(road)){
        throw std::invalid_argument("The road or the town has been linked");
    }
    
    try {
        field.link_locality(town, town_coord, town_corner);
        field.link_road(road, road_coord, road_side);
    }
    catch (std::logic_error &e) {
        throw std::invalid_argument(e.what());
    }
    
    if (!order){
        gather_resource(player, town_coord);
        if (town_corner == CrossCorner::TOP) {
            gather_resource(player, town_coord + Coord(0, 1));
            gather_resource(player, town_coord + Coord(-1, 1));
        } else {
            gather_resource(player, town_coord + Coord(0, -1));
            gather_resource(player, town_coord + Coord(1, -1));
        }
        if (_current_player == 0){
            return GameStage::STAGE1_DICE;
        } else {
            _current_player--;
        }
    } else {
        if (_current_player == _game.num_players() - 1){
            order = false;
        } else {
            _current_player++;
        }
    }
    return GameStage::PUT_INITIAL_INFRASTRUCTURES;
}

