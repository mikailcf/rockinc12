
#include "trap.hpp"

Trap::Trap() : Trigger()
{
}

Trap::Trap(Box box, string filename, int frames) : Trigger(box, filename, frames)
{
}

void Trap::action(Player *player)
{
    player->restoreCheckpoint();
}

