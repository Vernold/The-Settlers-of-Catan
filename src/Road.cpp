#include "Road.h"

Road::Road(const std::string &name, Player &player):
Infrastructure(name, player)
{}

Road::~Road()
{}

bool Road::is_city() const noexcept
{
    return false;
}

bool Road::is_town() const noexcept
{
    return false;
}

bool Road::is_road() const noexcept
{
    return true;
}
