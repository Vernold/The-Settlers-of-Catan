#include "ResourcesHolder.h"


ResourcesHolder::ResourcesHolder()
{}

void
ResourcesHolder::add(Resource r, size_t n) noexcept
{
    if (!_resources.count(r)){
        _resources[r] = 0;
    }
    _resources[r] += n;
}

void
ResourcesHolder::remove(Resource r, size_t n)
{
    if (n == 0){
        return;
    }
    if (!_resources.count(r) || _resources[r] < n){
        throw std::logic_error("More resources are needed");
    }
    _resources[r] -= n;
}

size_t
ResourcesHolder::resources(Resource r) const noexcept
{
    return _resources.count(r) != 0 ? _resources.at(r) : 0;
}

size_t
ResourcesHolder::resources() const noexcept
{
    size_t result = 0;
    
    for (auto r : _resources){
        result += r.second;
    }
    return result;
}


