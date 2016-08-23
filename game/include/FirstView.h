#ifndef FirstView_h
#define FirstView_h

#include "Receiver.h"
#include "SupportView.h"

/*@
 true
@*/
class FirstView: public SupportView, public Receiver
{

public:
    FirstView(IGameEngine &);
    
    void update();
    
    int make_dice_view();
    int drop_resources_view();
    int move_robber_view();
    int rob_view();
};

#endif /* FirstView_h */
