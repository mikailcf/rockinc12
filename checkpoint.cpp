
#include "checkpoint.hpp"

Checkpoint::Checkpoint()
{
}

Checkpoint::Checkpoint(int id, Box box, bool visited)
{
    this->id = id;
    this->box = box;
    this->visited = visited;
}

void Checkpoint::action(Player *player)
{
    this->visit();
    player->setCheckpoint(this);
}

sf::Vector2f Checkpoint::getPosition()
{
    return sf::Vector2f(box.getPosition().x, box.getPosition().y);
}

bool Checkpoint::getVisited()
{
    return visited;
}

void Checkpoint::visit()
{
    visited = true;
}

