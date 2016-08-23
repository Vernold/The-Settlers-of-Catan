#ifndef ResourcesHolder_h
#define ResourcesHolder_h

#include "Resource.h"
#include <map>
#include <stdexcept>

/*@
  true
@*/
class ResourcesHolder
{
    std::map<Resource, size_t> _resources;
    
public:
    ResourcesHolder();
    void add(Resource, size_t) noexcept;
    void remove(Resource, size_t);
    size_t resources(Resource) const noexcept;
    size_t resources() const noexcept;
    
    ResourcesHolder(const ResourcesHolder &) = delete;
    ResourcesHolder &operator=(const ResourcesHolder &) = delete;
};

#endif /* ResourcesHolder_h */
