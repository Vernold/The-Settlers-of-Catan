#include "Hex.h"

Hex::Hex()
{}

void
Hex::set_number(size_t n)
{
    if (_number){
        throw std::logic_error("The number is already set");
    }
    _number = n;
}

void
Hex::unset_number()
{
    if (!_number){
        throw std::logic_error("The number has not been set");
    }
    _number = 0;
}

bool
Hex::has_number() const noexcept
{
    return _number != 0;
}

size_t
Hex::number() const
{
    if (!_number){
        throw std::logic_error("The number has not been set");
    }
    return _number;
}

void
Hex::set_resource(Resource r)
{
    if (_has_resource){
        throw std::logic_error("The resource is already set");
    }
    _resource = r;
    _has_resource = true;
}

void
Hex::unset_resource()
{
    if (!_has_resource){
        throw std::logic_error("The resource has not been set");
    }
    _has_resource = false;
}

bool
Hex::has_resource() const noexcept
{
    return _has_resource;
}

Resource
Hex::resource() const
{
    if (!_has_resource){
        throw std::logic_error("The resource has not been set");
    }
    return _resource;
}

