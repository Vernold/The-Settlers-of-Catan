#include "City.h"

City::City(const std::string &name, Player &player):
Locality(name, player)
{}

City::~City()
{}

bool City::is_city() const noexcept
{
    return true;
}

bool City::is_town() const noexcept
{
    return false;
}

bool City::is_road() const noexcept
{
    return false;
}
