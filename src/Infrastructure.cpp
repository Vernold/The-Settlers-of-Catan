#include "Infrastructure.h"

Infrastructure::Infrastructure(const std::string &name, Player &player):
_name(name), _player(player)
{}

Infrastructure::~Infrastructure()
{}

const std::string &
Infrastructure::name() const noexcept
{
    return _name;
}

Player &
Infrastructure::player() const noexcept
{
    return _player;
}
