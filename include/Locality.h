#ifndef Locality_h
#define Locality_h

#include "Infrastructure.h"

class Locality: public Infrastructure
{
    
public:
    Locality(const std::string &, Player &);
    virtual ~Locality();
    
    Locality(const Locality &) = delete;
    Locality &operator=(Locality &) = delete;
};

#endif /* Locality_h */
