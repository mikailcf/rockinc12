
#include "defs.hpp"
#include "trigger.hpp"
#include "player.hpp"

#ifndef TELEPORT_HPP
#define TELEPORT_HPP

class Teleport : public Trigger
{
private:
    bool occupied;
public:
    Teleport();
    Teleport(Box, string);
    void action(Player*);
    void actionAlternate(Player*);
    void leave();
};

#endif

