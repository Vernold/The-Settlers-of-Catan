#include "FirstEngine.h"

FirstEngine::FirstEngine(Game &game, size_t &current): SupportEngine(game, current)
{}

GameStage
FirstEngine::make_dice(const std::string &player_name, size_t dice)
{
    if (_game.player(_current_player).name() != player_name) {
        throw std::invalid_argument("The player is not the current one");
    }
    if (dice < MIN_DICE || dice > MAX_DICE) {
        throw std::invalid_argument("The dice can be in range [2, 12]");
    }
    
    if (dice == ROB_DICE) {
        resources_to_drop.clear();
        for (uint i = 0; i < _game.num_players(); i++) {
            Player &player = _game.player(i);
            size_t resources = player.bank().resources();
            if (resources > ROB_DICE) {
                resources_to_drop[player.name()] = resources >> 1;
            }
        }
        if (!resources_to_drop.empty()){
            return GameStage::STAGE1_DROP_RESOURCES;
        }
        return GameStage::STAGE1_MOVE_ROBBER;
    }
    Field &field = _game.field();
    std::vector<Coord> coords;
    
    for(uint i = 0; i < field.num_hexes(); i++) {
        Hex &hex = field.hex(i);
        if (hex.has_number() &&
            hex.number() == dice &&
            field.robber() != field.coord(hex)) {
            coords.push_back(field.coord(hex));
        }
    }

    for (uint i = 0; i < _game.num_players(); i++) {
        Player &player = _game.player(i);
        for (Coord coord : coords){
            issue_resource(player, coord, Coord(0, 0), CrossCorner::TOP);
            issue_resource(player, coord, Coord(1, -1), CrossCorner::TOP);
            issue_resource(player, coord, Coord(0, -1), CrossCorner::TOP);
            
            issue_resource(player, coord, Coord(0, 0), CrossCorner::BOTTOM);
            issue_resource(player, coord, Coord(-1, 1), CrossCorner::BOTTOM);
            issue_resource(player, coord, Coord(0, 1), CrossCorner::BOTTOM);
        }
    }
    return GameStage::STAGE2;
}

GameStage
FirstEngine::drop_resource(const std::string &player_name, Resource resource)
{
    Player &player = get_player(player_name);
    
    if (resources_to_drop.count(player_name) == 0) {
        throw std::invalid_argument("The player should not drop");
    }
    if (player.bank().resources(resource) == 0) {
        throw std::invalid_argument("Not enough resources");
    }
    
    player.bank().remove(resource, 1);
    _game.field().bank().add(resource, 1);
    
    if (--resources_to_drop[player_name] == 0){
        resources_to_drop.erase(player_name);
    }
    if (!resources_to_drop.empty()){
        return GameStage::STAGE1_DROP_RESOURCES;
    }
    return GameStage::STAGE1_MOVE_ROBBER;
}

GameStage
FirstEngine::move_robber(const std::string &player_name, Coord coord)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    if (!_game.field().has_hex(coord)) {
        throw std::invalid_argument("The hex does not exist");
    }
    if (_game.field().robber() == coord) {
        throw std::invalid_argument("The robber is already here");
    }
    
    _game.field().set_robber(coord);
    
    if (robber_adjoins_locality()){
        return GameStage::STAGE1_ROBBING;
    }
    return GameStage::STAGE2;
}

GameStage
FirstEngine::rob(const std::string &player_name, const std::string &victim_name)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    
    Player &player = _game.player(_current_player);
    Player &victim = get_player(victim_name);
    Coord coord = _game.field().robber();
    
    if (!locality_is_hear(victim, coord, CrossCorner::TOP) &&
        !locality_is_hear(victim, coord, CrossCorner::BOTTOM) &&
        !locality_is_hear(victim, coord + Coord(-1, 1), CrossCorner::BOTTOM) &&
        !locality_is_hear(victim, coord + Coord(0, 1), CrossCorner::BOTTOM) &&
        !locality_is_hear(victim, coord + Coord(1, -1), CrossCorner::TOP) &&
        !locality_is_hear(victim, coord + Coord(0, -1), CrossCorner::TOP)) {
        throw std::invalid_argument("The robber cannot rob the victim");
    }
    
    for (uint i = 0; i < RESOURCE_KINDS; i++){
        if (victim.bank().resources(static_cast<Resource>(i))) {
            victim.bank().remove(static_cast<Resource>(i), 1);
            player.bank().add(static_cast<Resource>(i), 1);
            break;
        }
    }
    return GameStage::STAGE2;
}
