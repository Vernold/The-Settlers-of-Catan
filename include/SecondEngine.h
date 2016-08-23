#ifndef SecondEngine_h
#define SecondEngine_h

#include <set>

#include "SupportEngine.h"
#include "Exchange.h"

/*@
 \forall Exchange ex; ex \in exchange_pool ==> !ex.src().empty() && !ex.target().empty()
@*/

class SecondEngine: public SupportEngine
{
    std::vector<Exchange> exchange_pool;
    
public:
    SecondEngine(Game &, size_t &);
    
    void exchange_with_field(const std::string &, Resource, Resource);
    int exchange_players_request(const std::string &, const std::string &,
                                 const std::multiset<Resource> &, const std::multiset<Resource> &);
    void exchange_players_accept(const std::string &, int);
    GameStage end_exchanges(const std::string &);
    
    std::set<int> requests() const noexcept;
    std::set<int> exchanges() const noexcept;
    
    const Player &initiator(int) const;
    const Player &other(int) const;
    
    const std::multiset<Resource> &src(int) const;
    const std::multiset<Resource> &target(int) const;
    
    bool requested(int) const noexcept;
    bool performed(int) const;
};

#endif /* SecondEngine_h */
