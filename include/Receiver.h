#ifndef Receiver_h
#define Receiver_h

class Receiver
{
    
public:
    virtual ~Receiver(){}
    virtual void update() = 0;
};

#endif /* Receiver_h */
