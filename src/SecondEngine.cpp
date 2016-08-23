#include "SecondEngine.h"

SecondEngine::SecondEngine(Game &game, size_t &current): SupportEngine(game, current)
{}

void
SecondEngine::exchange_with_field(const std::string &player_name, Resource src, Resource target)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    
    Player &player = _game.player(_current_player);
    Field &field = _game.field();
    
    if (player.bank().resources(src) < EXCHANGE_WITH_FIELD_NUM) {
        throw std::invalid_argument("The player has no enough resources");
    }
    if (field.bank().resources(target) < 1) {
        throw std::invalid_argument("The bank has no such resource");
    }
    
    player.bank().add(target, 1);
    player.bank().remove(src, EXCHANGE_WITH_FIELD_NUM);
    
    field.bank().add(src, EXCHANGE_WITH_FIELD_NUM);
    field.bank().remove(target, 1);
}

int
SecondEngine::exchange_players_request(const std::string &player_name, const std::string &other_name,
                                       const std::multiset<Resource> &src, const std::multiset<Resource> &target)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    if (other_name == player_name){
        throw std::invalid_argument("The player cannot exchange with himself");
    }
    
    if (src.empty() || target.empty()) {
        throw std::invalid_argument("The player tries to cheat");
    }
    Player &player = _game.player(_current_player);
    Player &other_player = get_player(other_name);
    
    for (Resource resource : target){
        if (target.count(resource) > INIT_RESOURCE_NUMBER){
            throw std::invalid_argument("The player wants too much resources");
        }
    }
    for (Resource resource : src) {
        if (player.bank().resources(resource) < src.count(resource)) {
            throw std::invalid_argument("The player does not have this amount of resources");
        }
    }
    
    exchange_pool.emplace_back(player, other_player, std::multiset<Resource>(src), std::multiset<Resource>(target));
    
    return exchange_pool.size() - 1;
}

void
SecondEngine::exchange_players_accept(const std::string &player_name, int request)
{
    if (_game.player(_current_player).name() == player_name){
        throw std::invalid_argument("The player is current");
    }
    
    Player &player = get_player(player_name);
    
    if (!requested(request)) {
        throw std::invalid_argument("There is no such request");
    }
    
    Exchange &exchange = exchange_pool[request];
    
    if (exchange.performed()) {
        throw std::invalid_argument("The request has already been performed");
    }
    if (exchange.other().name() != player_name) {
        throw std::invalid_argument("The player cannot accept this request");
    }
    
    std::multiset<Resource> target = exchange.target();
    std::multiset<Resource> src = exchange.src();
    
    for (Resource resource : exchange.target()) {
        if (player.bank().resources(resource) < target.count(resource)) {
            throw std::invalid_argument("the other player does not have resources");
        }
        player.bank().remove(resource, target.count(resource));
        exchange.initiator().bank().add(resource, target.count(resource));
        target.erase(resource);
    }
    for (Resource resource : exchange.src()) {
        if (exchange.initiator().bank().resources(resource) < src.count(resource)) {
            throw std::invalid_argument("The initiator does not have resources");
        }
        player.bank().add(resource, src.count(resource));
        exchange.initiator().bank().remove(resource, src.count(resource));
        src.erase(resource);
    }
    exchange.set_performed();
}

GameStage
SecondEngine::end_exchanges(const std::string &player_name)
{
    if (_game.player(_current_player).name() != player_name){
        throw std::invalid_argument("The player is not current");
    }
    exchange_pool.clear();
    return GameStage::STAGE3;
}

bool
SecondEngine::requested(int number) const noexcept
{
    return number >= 0 && static_cast<size_t>(number) < exchange_pool.size();
}

bool
SecondEngine::performed(int request) const
{
    if (!requested(request)) {
        throw std::invalid_argument("There is no such request");
    }
    return exchange_pool[request].performed();
}

std::set<int>
SecondEngine::requests() const noexcept
{
    std::set<int> _requests;
    
    for (uint i = 0; i < exchange_pool.size(); i++)
    {
        if (!exchange_pool[i].performed()){
            _requests.insert(i);
        }
    }
    return _requests;
}

std::set<int>
SecondEngine::exchanges() const noexcept
{
    std::set<int> _exchanges;
    
    for (uint i = 0; i < exchange_pool.size(); i++)
    {
        if (exchange_pool[i].performed()){
            _exchanges.insert(i);
        }
    }
    return _exchanges;
}

const Player &
SecondEngine::initiator(int request) const
{
    if (!requested(request)) {
        throw std::invalid_argument("There is no such request");
    }
    return exchange_pool[request].initiator();
}

const Player &
SecondEngine::other(int request) const
{
    if (!requested(request)) {
        throw std::invalid_argument("There is no such request");
    }
    return exchange_pool[request].other();
}

const std::multiset<Resource> &
SecondEngine::src(int request) const
{
    if (!requested(request)) {
        throw std::invalid_argument("There is no such request");
    }
    return exchange_pool[request].src();
}

const std::multiset<Resource> &
SecondEngine::target(int request) const
{
    if (!requested(request)) {
        throw std::invalid_argument("There is no such request");
    }
    return exchange_pool[request].target();
}