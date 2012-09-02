
#include "teleport.hpp"
#include "world.hpp"

Teleport::Teleport()
{
    occupied = false;
}

Teleport::Teleport(Box box, string filename) : Trigger(box, filename)
{
    occupied = false;
}

void Teleport::action(Player *player)
{
    if (!occupied) {
        player->teleporting++;
        occupied = true;
    }
    player->world->switch_players();
}

void Teleport::actionAlternate(Player *player)
{
    if (occupied) {
        player->teleporting--;
        occupied = false;        
    }
}

void Teleport::leave()
{
    occupied = false;
}

