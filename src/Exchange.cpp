#include "Exchange.h"

Exchange::Exchange(Player &initiator, Player &other,
                   const std::multiset<Resource> &src, const std::multiset<Resource> &target):
_initiator(initiator), _other(other), _src(src), _target(target)
{}

const Player &
Exchange::initiator() const noexcept
{
    return _initiator;
}

const Player &
Exchange::other() const noexcept
{
    return _other;
}

const std::multiset<Resource> &
Exchange::src() const noexcept
{
    return _src;
}

const std::multiset<Resource> &
Exchange::target() const noexcept
{
    return _target;
}

void
Exchange::set_performed() noexcept
{
    _performed = true;
}

bool
Exchange::performed() const noexcept
{
    return _performed;
}