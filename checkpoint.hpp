
#include "defs.hpp"
#include "trigger.hpp"
#include "player.hpp"

#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

class Checkpoint : public Trigger
{
private:
    int id;
    bool visited;
public:
    Checkpoint();
    Checkpoint(int, Box, bool);
    void action(Player*);
    sf::Vector2f getPosition();
    void visit();
    bool getVisited();
};

#endif

