
#include "checkpoint.hpp"

Checkpoint::Checkpoint()
{
}

Checkpoint::Checkpoint(int id, Box box)
{
    this->id = id;
    this->box = box;
}

void Checkpoint::action(Player *player)
{
    player->setCheckpoint(this);
}

sf::Vector2f Checkpoint::getPosition()
{
    return sf::Vector2f(box.getPosition().x, box.getPosition().y);
}

