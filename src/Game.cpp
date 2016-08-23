
#include "Game.h"

Game::Game(): _field(new Field())
{}

Field &
Game::field() const noexcept
{
    return *_field;
}

Player &
Game::add_player(const std::string &name)
{
    players.emplace_back(new Player(name));
    return *players.back();
}

size_t
Game::num_players() const noexcept
{
    return players.size();
}

Player &
Game::player(size_t i) const
{
    if (i >= players.size()){
        throw std::out_of_range("There is no such player");
    }
    return *players[i];
}