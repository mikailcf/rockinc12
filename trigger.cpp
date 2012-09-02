
#include "trigger.hpp"

Trigger::Trigger()
{
}

Trigger::Trigger(Box box)
{
    this->box = box;
}

void Trigger::check(Player *player)
{
    if (box.intersects(player)) {
        action(player);
    }
}

