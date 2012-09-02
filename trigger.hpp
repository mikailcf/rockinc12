
#include "defs.hpp"
#include "box.hpp"
#include "player.hpp"

#ifndef TRIGGER_HPP
#define TRIGGER_HPP

class Trigger
{
protected:
    Box box;
public:
    Trigger(Box);
    Trigger();
    void check(Player*);
    virtual void action(Player*) = 0;
};

#endif

