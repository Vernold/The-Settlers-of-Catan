#include "Player.h"

Player::Player(const std::string &name): _name(name), _bank(new ResourcesHolder())
{}

const std::string &
Player::name() const noexcept
{
    return _name;
}

ResourcesHolder &
Player::bank() const noexcept
{
    return *_bank;
}

/*Roads*/

Road &
Player::add_road(const std::string &name)
{
    infrastructures.emplace_back(new Road(name, *this));
    return dynamic_cast<Road &>(*infrastructures.back());
}

void
Player::remove_road(Road &road)
{
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_road() &&
            infrastructures[i]->name() == road.name()){
            delete infrastructures[i].release();
            infrastructures.erase(infrastructures.begin() + i);
            return;
        }
    }
    throw std::logic_error("The player does not have the road");
}

/*Cities*/

City &
Player::add_city(const std::string &name)
{
    infrastructures.emplace_back(new City(name, *this));
    return dynamic_cast<City &>(*infrastructures.back());
}

void
Player::remove_city(City &city)
{
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_city() &&
            infrastructures[i]->name() == city.name()){
            delete infrastructures[i].release();
            infrastructures.erase(infrastructures.begin() + i);
            return;
        }
    }
    throw std::logic_error("The player does not have the city");
}

/*Towns*/

Town &
Player::add_town(const std::string &name)
{
    infrastructures.emplace_back(new Town(name, *this));
    return dynamic_cast<Town &>(*infrastructures.back());
}

void
Player::remove_town(Town & town)
{
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_town() &&
            infrastructures[i]->name() == town.name()){
            delete infrastructures[i].release();
            infrastructures.erase(infrastructures.begin() + i);
            return;
        }
    }
    throw std::logic_error("The player does not have the town");
}

size_t
Player::num_infrastructures() const noexcept
{
    return infrastructures.size();
}

Infrastructure &
Player::infrastructure(size_t i) const
{
    if (i >= infrastructures.size()){
        throw std::out_of_range("The player does not have such the infrastructure");
    }
    return *infrastructures[i];
}

size_t
Player::num_roads() const noexcept
{
    size_t counter = 0;
    
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_road()){
            counter++;
        }
    }
    return counter;
}

Road &
Player::road(size_t j) const
{
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_road()){
            if (j-- == 0){
                return dynamic_cast<Road &>(*infrastructures[i]);
            }
        }
    }
    throw std::out_of_range("The player does not have such the road");
}

size_t
Player::num_towns() const noexcept
{
    size_t counter = 0;
    
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_town()){
            counter++;
        }
    }
    return counter;
}

Town &
Player::town(size_t j) const
{
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_town()){
            if (j-- == 0){
                return dynamic_cast<Town &>(*infrastructures[i]);
            }
        }
    }
    throw std::out_of_range("The player does not have such the town");
}

size_t
Player::num_cities() const noexcept
{
    size_t counter = 0;
    
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_city()){
            counter++;
        }
    }
    return counter;
}

City &
Player::city(size_t j) const
{
    for (uint i = 0; i < infrastructures.size(); i++){
        if (infrastructures[i]->is_city()){
            if (j-- == 0){
                return dynamic_cast<City &>(*infrastructures[i]);
            }
        }
    }
    throw std::out_of_range("The player does not have such the city");
}
