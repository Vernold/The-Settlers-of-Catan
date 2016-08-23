#ifndef City_h
#define City_h

#include "Locality.h"

class City: public Locality
{

public:
    City(const std::string &, Player &);
    virtual ~City();
    
    bool is_city() const noexcept;
    bool is_town() const noexcept;
    bool is_road() const noexcept;
};

#endif /* City_h */
