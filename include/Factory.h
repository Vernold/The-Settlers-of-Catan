#ifndef Factory_h
#define Factory_h

#include "GameEngine.h"
#include "ObservableGameEngine.h"

class Factory
{

public:
    IGameEngine *make_game_engine()
    {
        return new ObservableGameEngine();
    }
};

#endif /* Factory_h */
