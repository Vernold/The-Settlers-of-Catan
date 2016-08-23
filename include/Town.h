#ifndef Town_h
#define Town_h

#include "Locality.h"

class Town: public Locality
{
    
public:
    Town(const std::string &, Player &);
    virtual ~Town();
    
    bool is_city() const noexcept;
    bool is_town() const noexcept;
    bool is_road() const noexcept;
};

#endif /* Town_h */
