#ifndef Hex_h
#define Hex_h

#include <stdexcept>
#include <memory>

#include "Resource.h"

/*@
 true
@*/

class Hex
{
    size_t _number = 0;

    bool _has_resource = false;
    Resource _resource;

public:
    Hex();
    
    void set_number(size_t n);
    void unset_number();
    bool has_number() const noexcept;
    size_t number() const;
    
    void set_resource(Resource);
    void unset_resource();
    bool has_resource() const noexcept;
    Resource resource() const;
    
    Hex(const Hex &) = delete;
    Hex &operator=(const Hex &) = delete;
};

#endif /* Hex_h */
