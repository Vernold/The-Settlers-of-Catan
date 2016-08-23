#ifndef SecondView_h
#define SecondView_h

#include "SupportView.h"
#include "Receiver.h"

/*@
 true
 @*/
class SecondView: public SupportView, public Receiver
{
    
public:
    SecondView(IGameEngine &);
    
    int menu();
    void update();
    
    int exchange_with_field_view();
    int exchange_request_view();
    int accept_request_view(const std::string &, int);
};

#endif /* SecondView_h */
