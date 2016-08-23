#ifndef Exchange_h
#define Exchange_h

#include <set>
#include "Game.h"

/*@
 true
 @*/
class Exchange {
    bool _performed = false;
    
    Player &_initiator, &_other;
    
    const std::multiset<Resource> _src, _target;
    
public:
    Exchange(Player &, Player &, const std::multiset<Resource> &, const std::multiset<Resource> &);
    
    const Player &initiator() const noexcept;
    const Player &other() const noexcept;
    
    const std::multiset<Resource> &src() const noexcept;
    const std::multiset<Resource> &target() const noexcept;
    
    void set_performed() noexcept;
    bool performed() const noexcept;
};

#endif /* Exchange_h */
