#include "ObservableGameEngine.h"

ObservableGameEngine::ObservableGameEngine():
_game(new Game()),
_stage(GameStage::PLAYERS_REGISTRATION),
_observer(new Observer())
{
    switch_engine();
}

/*StartEngine*/

void
ObservableGameEngine::join_player(const std::string &player_name)
{
    if (_stage != GameStage::PLAYERS_REGISTRATION){
        throw std::invalid_argument("The game has already began");
    }
    start_engine->join_player(player_name);
    _observer->notify();
}

void
ObservableGameEngine::start_game()
{
    if (_stage != GameStage::PLAYERS_REGISTRATION){
        throw std::invalid_argument("The game has already began");
    }
    _stage = start_engine->start_game();
    _observer->notify();
}

void
ObservableGameEngine::register_road(const std::string &player_name, const std::string &road_name)
{
    if (_stage != GameStage::INFRASTRUCTURES_REGISTRATION){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = start_engine->register_road(player_name, road_name);
    _observer->notify();
}

void
ObservableGameEngine::register_town(const std::string &player_name, const std::string &town_name)
{
    if (_stage != GameStage::INFRASTRUCTURES_REGISTRATION){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = start_engine->register_town(player_name, town_name);
    _observer->notify();
}

void
ObservableGameEngine::register_city(const std::string &player_name, const std::string &city_name)
{
    if (_stage != GameStage::INFRASTRUCTURES_REGISTRATION){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = start_engine->register_city(player_name, city_name);
    _observer->notify();
}

void
ObservableGameEngine::put_initial_infrastructure(const std::string &player, const std::string &town, Coord town_coord, CrossCorner town_corner,
                                                 const std::string &road, Coord road_coord, RoadSide road_side)
{
    if (_stage != GameStage::PUT_INITIAL_INFRASTRUCTURES){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = start_engine->put_initial_infrastructure(player, town, town_coord, town_corner,
                                                      road, road_coord, road_side);
    switch_engine();
    _observer->notify();
}

/*FirstEngine*/

void
ObservableGameEngine::make_dice(const std::string &player_name, size_t dice)
{
    if (_stage != GameStage::STAGE1_DICE) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = first_engine->make_dice(player_name, dice);
    switch_engine();
    _observer->notify();
}

void
ObservableGameEngine::drop_resource(const std::string &player_name, Resource resource)
{
    if (_stage != GameStage::STAGE1_DROP_RESOURCES) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = first_engine->drop_resource(player_name, resource);
    _observer->notify();
}

void
ObservableGameEngine::move_robber(const std::string &player_name, Coord coord)
{
    if (_stage != GameStage::STAGE1_MOVE_ROBBER){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = first_engine->move_robber(player_name, coord);
    switch_engine();
    _observer->notify();
}

void
ObservableGameEngine::rob(const std::string &player_name, const std::string &victim_name)
{
    if (_stage != GameStage::STAGE1_ROBBING){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = first_engine->rob(player_name, victim_name);
    switch_engine();
    _observer->notify();
}

/*SecondEngine*/

void
ObservableGameEngine::exchange_with_field(const std::string &player_name, Resource src, Resource target)
{
    if (_stage != GameStage::STAGE2){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    second_engine->exchange_with_field(player_name, src, target);
    _observer->notify();
}

int
ObservableGameEngine::exchange_players_request(const std::string &player_name, const std::string &other_player_name,
                                               const std::multiset<Resource> &src, const std::multiset<Resource> &target)
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    int request = second_engine->exchange_players_request(player_name, other_player_name, src, target);
    return request;
}

void
ObservableGameEngine::exchange_players_accept(const std::string &player_name, int request)
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    second_engine->exchange_players_accept(player_name, request);
    _observer->notify();
}

void
ObservableGameEngine::end_exchanges(const std::string &player_name)
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = second_engine->end_exchanges(player_name);
    switch_engine();
    _observer->notify();
}

std::set<int>
ObservableGameEngine::requests() const
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return second_engine->requests();
}

std::set<int>
ObservableGameEngine::exchanges() const
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return second_engine->exchanges();
}

const Player &
ObservableGameEngine::initiator(int request) const
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return second_engine->initiator(request);
}
const Player &
ObservableGameEngine::other(int request) const
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return second_engine->other(request);
}

const std::multiset<Resource> &
ObservableGameEngine::src(int request) const
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return second_engine->src(request);
}

const std::multiset<Resource> &
ObservableGameEngine::target(int request) const
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return second_engine->target(request);
}

bool
ObservableGameEngine::requested(int number) const
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return second_engine->requested(number);
}

bool
ObservableGameEngine::performed(int request) const
{
    if (_stage != GameStage::STAGE2) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return second_engine->performed(request);
}


/*ThirdEngine*/

void
ObservableGameEngine::build_road(const std::string &player_name, const std::string &road_name,
                                 Coord coord, RoadSide road_side)
{
    if (_stage != GameStage::STAGE3){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    third_engine->build_road(player_name, road_name, coord, road_side);
    _observer->notify();
}

void
ObservableGameEngine::build_town(const std::string &player_name, const std::string &town_name,
                                 Coord coord, CrossCorner corner)
{
    if (_stage != GameStage::STAGE3){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    third_engine->build_town(player_name, town_name, coord, corner);
    
    if (score(player_name) >= WIN_POINTS) {
        _stage = GameStage::FINAL_STAGE;
    }
    _observer->notify();
}

void
ObservableGameEngine::build_city(const std::string &player_name, const std::string &city_name,
                                 Coord coord, CrossCorner corner)
{
    if (_stage != GameStage::STAGE3){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    third_engine->build_city(player_name, city_name, coord, corner);
    
    if (score(player_name) >= WIN_POINTS) {
        _stage = GameStage::FINAL_STAGE;
    }
    _observer->notify();
}

void
ObservableGameEngine::next_player(const std::string &player_name)
{
    if (_stage != GameStage::STAGE3){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    _stage = third_engine->next_player(player_name);
    switch_engine();
    _observer->notify();
}

int
ObservableGameEngine::score(const std::string &player_name)
{
    if (_stage == GameStage::PLAYERS_REGISTRATION) {
        throw std::invalid_argument("The game is on the wrong stage");
    }
    int player_num = -1;
    
    for (uint i = 0; i < _game->num_players(); i++){
        if (_game->player(i).name() == player_name){
            player_num = i;
        }
    }
    if (player_num < 0){
        throw std::invalid_argument("The player has not been registered");
    }
    Player &player = _game->player(player_num);
    
    int result = 0;
    
    for (uint i = 0; i < player.num_towns(); i++) {
        result += _game->field().linked(player.town(i));
    }
    for (uint i = 0; i < player.num_cities(); i++) {
        result += 2 * _game->field().linked(player.city(i));
    }
    return result;
}

const Player &
ObservableGameEngine::winner() const
{
    if (_stage != GameStage::FINAL_STAGE){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return third_engine->winner();
}

/*General*/

const Game &
ObservableGameEngine::game() const noexcept
{
    return *_game;
}

const Player &
ObservableGameEngine::current_player() const
{
    if (_stage == GameStage::PLAYERS_REGISTRATION ||
        _stage == GameStage::FINAL_STAGE){
        throw std::invalid_argument("The game is on the wrong stage");
    }
    return _game->player(_current_player);
}

GameStage
ObservableGameEngine::stage() const noexcept
{
    return _stage;
}

void
ObservableGameEngine::switch_engine()
{
    if (!start_engine && _stage == GameStage::PLAYERS_REGISTRATION){
        start_engine.reset(new StartEngine(*_game, _current_player));
        
    } else if (start_engine && _stage == GameStage::STAGE1_DICE) {
        first_engine.reset(new FirstEngine(*_game, _current_player));
        delete start_engine.release();
        
    } else if (first_engine && _stage == GameStage::STAGE2){
        second_engine.reset(new SecondEngine(*_game, _current_player));
        delete first_engine.release();
        
    } else if (second_engine && _stage == GameStage::STAGE3){
        third_engine.reset(new ThirdEngine(*_game, _current_player));
        delete second_engine.release();
        
    } else if (third_engine && _stage == GameStage::STAGE1_DICE) {
        first_engine.reset(new FirstEngine(*_game, _current_player));
        delete third_engine.release();
    }
}

Observer &
ObservableGameEngine::observer() const 
{
    return *_observer;
}