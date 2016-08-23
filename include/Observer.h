#ifndef Observer_h
#define Observer_h

#include <memory>
#include "Receiver.h"

/*@
 if (_receiver != nullptr) \valid(_receiver)
@*/

class Observer
{
    Receiver *_receiver = nullptr;

public:
    
    void register_receiver(Receiver &receiver)
    {
        _receiver = &receiver;
    }
    
    void notify()
    {
         _receiver->update();
    }
};

#endif /* Observer_h */
