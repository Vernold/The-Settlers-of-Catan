#ifndef Game_h
#define Game_h

#include <vector>
#include <string>
#include <stdexcept>

#include "Field.h"
#include "Player.h"

/*@ 
 _field != nullptr
 &&
 \forall std::unique_ptr<Player> p; p \in players ==> p != null
 &&
 \forall Player p1, p2; p1 \in players && p2 \in players ==> p1.name() != p2.name()
 &&
 \forall Infrastructure *inf; inf \in _field.roads() || inf \in _field.localities() ==> \exists Player p; p \in players && inf \in p.infrastructures()
@*/
class Game
{
    std::unique_ptr<Field> _field;
    std::vector<std::unique_ptr<Player>> players;
    
public:
    Game();
    
    Field &field() const noexcept;
    
    Player &add_player(const std::string &);
    size_t num_players() const noexcept;
    Player &player(size_t i) const;

    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
};

#endif /* Game_h */
