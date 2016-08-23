#ifndef Player_h
#define Player_h

#include <vector>
#include <string>
#include <memory>

#include "ResourcesHolder.h"
#include "Road.h"
#include "Town.h"
#include "City.h"

typedef unsigned int uint;

/*@
 _bank != nullptr
 &&
 \forall std::unique_ptr<Infrastructures> i; i \in infrastructures ==> i != null
 &&
 \forall Infrastructure i1, Infrastructure i2; i1 != i2 && i1 \in infrastructures && i2 \in infrastructures ==> i1 != i2
@*/

class Player
{
    const std::string _name;
    std::unique_ptr<ResourcesHolder> _bank;
    
    std::vector<std::unique_ptr<Infrastructure>> infrastructures;
    
public:
    Player(const std::string &name);
    
    const std::string &name() const noexcept;
    ResourcesHolder &bank() const noexcept;
    
    Road &add_road(const std::string &);
    void remove_road(Road &);
    
    City &add_city(const std::string &);
    void remove_city(City &);
    
    Town &add_town(const std::string &);
    void remove_town(Town &);
    
    size_t num_infrastructures() const noexcept;
    Infrastructure &infrastructure(size_t) const;
    
    size_t num_roads() const noexcept;
    Road &road(size_t) const;
    
    size_t num_towns() const noexcept;
    Town &town(size_t) const;
    
    size_t num_cities() const noexcept;
    City &city(size_t) const;
  
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;
};
#endif /* Player_h */
