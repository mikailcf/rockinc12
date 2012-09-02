
#include "defs.hpp"
#include "trigger.hpp"
#include "player.hpp"

#ifndef TRAP_HPP
#define TRAP_HPP

class Trap : public Trigger
{
private:
public:
    Trap();
    Trap(Box);
    void action(Player*);
};

#endif

