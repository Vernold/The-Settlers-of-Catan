#ifndef ThirdView_h
#define ThirdView_h

#include "SupportView.h"
#include "Receiver.h"

/*@
 true
@*/

class ThirdView: public SupportView, public Receiver
{
public:
    ThirdView(IGameEngine &);
    
    void update();
    int menu();
    
    int build_view(const std::string &) const;
    void winner_view() const;
};
#endif /* ThirdView_h */
