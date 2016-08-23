#ifndef Road_h
#define Road_h

#include "Infrastructure.h"

class Road: public Infrastructure
{
    
public:
    Road(const std::string &, Player &);
    virtual ~Road();
    
    bool is_city() const noexcept;
    bool is_town() const noexcept;
    bool is_road() const noexcept;
};

#endif /* Road_h */
