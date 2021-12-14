#ifndef _OBSERVER_H_
#define _OBSERVER_H_ 
#include <string>
 
class Tile;

class Observer {
    public:
    virtual void wasNotified( Tile& whoNotified ) = 0;  // s is the Subject that called the notify method
    virtual ~Observer() = default;
};

#endif