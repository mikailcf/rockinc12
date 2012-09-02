
#include "defs.hpp"
#include "box.hpp"
#include "player.hpp"

#ifndef TRIGGER_HPP
#define TRIGGER_HPP

class Trigger
{
private:
    int animation_t;
    sf::Texture texture;
    sf::Sprite sprite;
    int frames;
protected:
    Box box;
public:
    Trigger();
    Trigger(Box);
    Trigger(Box, string);
    Trigger(Box, string, int);
    void check(Player*);
    virtual void action(Player*) = 0;
    virtual void actionAlternate(Player*);
    void animate(int);
    void draw(sf::RenderWindow *);
};

#endif

