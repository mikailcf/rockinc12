
#include "trap.hpp"

Trap::Trap()
{
}

Trap::Trap(Box box)
{
    this->box = box;
}

void Trap::action(Player *player)
{
    player->restoreCheckpoint();
}

