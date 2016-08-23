#ifndef StartView_h
#define StartView_h

#include "SupportView.h"
#include "Receiver.h"

/*@
 true
@*/
class StartView: public SupportView, public Receiver
{
    
public:
    StartView(IGameEngine &);
    
    void update();
    
    int infrastructures_registration_view();
    int initial_infrastructures_view();
    int players_registration_view();
    int join_player_view();
};



#endif /* StartView_h */
