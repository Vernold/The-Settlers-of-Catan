#include "Town.h"

Town::Town(const std::string &name, Player &player):
Locality(name, player)
{}

Town::~Town()
{}

bool Town::is_city() const noexcept
{
    return false;
}

bool Town::is_town() const noexcept
{
    return true;
}

bool Town::is_road() const noexcept
{
    return false;
}
