
#include "defs.hpp"
#include "trigger.hpp"
#include "player.hpp"

#ifndef TELEPORT_HPP
#define TELEPORT_HPP

class Teleport : public Trigger
{
private:
public:
    Teleport();
    Teleport(Box);
    void action(Player*);
};

#endif

