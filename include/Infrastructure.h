#ifndef Infrastructure_h
#define Infrastructure_h

#include <string>

class Player;

/*@ 
 true
@*/
class Infrastructure
{
    const std::string _name;
    Player &_player;
    
public:
    Infrastructure(const std::string &, Player &);
    virtual ~Infrastructure();
    
    Player &player() const noexcept;
    const std::string &name() const noexcept;
    
    virtual bool is_town() const noexcept = 0;
    virtual bool is_city() const noexcept = 0;
    virtual bool is_road() const noexcept = 0;
};



#endif /* Infrastructure_h */
