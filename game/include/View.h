#ifndef View_h
#define View_h

#include "StartView.h"
#include "FirstView.h"
#include "SecondView.h"
#include "ThirdView.h"

/*
 (\valid(start_view) && first_view == nullptr && second_view == nullptr && third_view == nullptr)
 &&
 (\valid(first_view) && start_view == nullptr && second_view == nullptr && third_view == nullptr)
 &&
 (\valid(second_view) && first_view == nullptr && start_view == nullptr && third_view == nullptr)
 &&
 (\valid(thrid_view) && first_view == nullptr && second_view == nullptr && start_view == nullptr)
*/
class View: public Receiver, public SupportView
{
    std::unique_ptr<StartView> start_view;
    std::unique_ptr<FirstView> first_view;
    std::unique_ptr<SecondView> second_view;
    std::unique_ptr<ThirdView> third_view;
    
public:
    View(IGameEngine &);
    
    void update();
};

#endif /* View_h */
