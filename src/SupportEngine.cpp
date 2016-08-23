#include "SupportEngine.h"

SupportEngine::SupportEngine(Game &game, size_t &current): _game(game), _current_player(current)
{}

Player &
SupportEngine::get_player(const std::string player_name) const
{
    int player_num = -1;
    
    for (uint i = 0; i < _game.num_players(); i++){
        if (_game.player(i).name() == player_name){
            player_num = i;
        }
    }
    if (player_num < 0){
        throw std::invalid_argument("The player has not been registered");
    }
    return _game.player(player_num);
}

bool
SupportEngine::road_adjoins_locality(Coord locality_coord, CrossCorner locality_corner,
                                     Coord road_coord, RoadSide road_side) const noexcept
{
    if (locality_corner == CrossCorner::TOP){
        if ((locality_coord == road_coord) &&
            (road_side == RoadSide::UP)){
            return true;
        }
        if ((locality_coord == road_coord + Coord (1, -1)) &&
            (road_side != RoadSide::UP)){
            return true;
        }
    } else {
        if ((locality_coord == road_coord) &&
            (road_side == RoadSide::DOWN)){
            return true;
        }
        if ((locality_coord == road_coord + Coord (0, 1)) &&
            (road_side != RoadSide::DOWN)){
            return true;
        }
    }
    return false;
}

bool
SupportEngine::locality_adjoins_locality(Coord coord, CrossCorner corner) const noexcept
{
    Field &field = _game.field();
    
    if (field.has_locality(coord, corner)){
        return true;
    }
    if (corner == CrossCorner::BOTTOM) {
        if (field.has_locality(coord + Coord(1, -2), CrossCorner::TOP) ||
            field.has_locality(coord + Coord(0, -1), CrossCorner::TOP) ||
            field.has_locality(coord + Coord(1, -1), CrossCorner::TOP)){
            return true;
        }
    } else {
        if (field.has_locality(coord + Coord(-1, 2), CrossCorner::BOTTOM) ||
            field.has_locality(coord + Coord(0, 1), CrossCorner::BOTTOM) ||
            field.has_locality(coord + Coord(-1, 1), CrossCorner::BOTTOM)){
            return true;
        }
    }
    return false;
}

void
SupportEngine::gather_resource(Player &player, Coord coord)
{
    Field &field = _game.field();
    
    if (!field.has_hex(coord)){
        return;
    }
    
    Hex &hex = field.hex(coord);
    
    if (hex.has_resource() &&
        field.robber() != coord &&
        field.bank().resources(hex.resource())){
        field.bank().remove(hex.resource(), 1);
        player.bank().add(hex.resource(), 1);
    }
}

bool
SupportEngine::locality_in_field_range(Coord coord, CrossCorner corner) const noexcept
{
    Field &field = _game.field();
    
    if (corner == CrossCorner::TOP){
        if (field.has_hex(coord) ||
            field.has_hex(coord + Coord(0, 1)) ||
            field.has_hex(coord + Coord(-1, 1))){
            return true;
        }
    } else {
        if (field.has_hex(coord) ||
            field.has_hex(coord + Coord(0, -1)) ||
            field.has_hex(coord + Coord(1,- 1))){
            return true;
        }
    }
    return false;
}

bool
SupportEngine::road_in_field_range(Coord coord, RoadSide side) const noexcept
{
    Field &field = _game.field();
    
    if (side == RoadSide::UP){
        if (field.has_hex(coord) ||
            field.has_hex(coord + Coord(0, 1))){
            return true;
        }
    } else if (side == RoadSide::RIGHT){
        if (field.has_hex(coord) ||
            field.has_hex(coord + Coord(1, 0))){
            return true;
        }
    } else {
        if (field.has_hex(coord) ||
            field.has_hex(coord + Coord(1, -1))){
            return true;
        }
    }
    return false;
}

bool
SupportEngine::locality_is_hear(const Player &player, Coord coord, CrossCorner corner) const noexcept
{
    return  _game.field().has_locality(coord, corner) &&
            _game.field().locality(coord, corner).player().name() == player.name();
}

bool
SupportEngine::road_is_hear(const Player &player, Coord coord, RoadSide side) const noexcept
{
    return  _game.field().has_road(coord, side) &&
            _game.field().road(coord, side).player().name() == player.name();
}

bool
SupportEngine::check_infrastructure_set() const noexcept
{
    for (uint i = 0; i < _game.num_players(); i++) {
        if ((_game.player(i).num_cities() != INIT_CITY_NUMBER) ||
            (_game.player(i).num_roads() != INIT_ROAD_NUMBER) ||
            (_game.player(i).num_towns() != INIT_TOWN_NUMBER)) {
            return false;
        }
    }
    return true;
}

void
SupportEngine::issue_resource(Player &player, Coord coord, Coord shift, CrossCorner corner)
{
    if (locality_is_hear(player, coord + shift, corner)) {
        Locality &locality = _game.field().locality(coord + shift, corner);
        gather_resource(player, coord);
        if (locality.is_city()) {
            gather_resource(player, coord);
        }
    }
}

bool
SupportEngine::robber_adjoins_locality() const
{
    Field &field = _game.field();
    Coord coord = field.robber();
    
    return  field.has_locality(coord, CrossCorner::TOP) ||
    field.has_locality(coord, CrossCorner::BOTTOM) ||
    field.has_locality(coord + Coord(-1, 1), CrossCorner::BOTTOM) ||
    field.has_locality(coord + Coord(0, 1), CrossCorner::BOTTOM) ||
    field.has_locality(coord + Coord(1, -1), CrossCorner::TOP) ||
    field.has_locality(coord + Coord(0, -1), CrossCorner::TOP);
}