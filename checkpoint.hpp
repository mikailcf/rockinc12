
#include "defs.hpp"
#include "trigger.hpp"
#include "player.hpp"

#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

class Checkpoint : public Trigger
{
private:
    int id;
public:
    Checkpoint();
    Checkpoint(int, Box);
    void action(Player*);
    sf::Vector2f getPosition();
};

#endif

