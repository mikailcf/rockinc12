
#include "defs.hpp"
#include "player.hpp"
#include "animation.hpp"

#ifndef BLOCK_HPP
#define BLOCK_HPP

class Block{
    sf::ConvexShape block;
    sf::Vector2f center, initial_center;
    int relative_position;
    Player *attached;
    sf::View *view;
    Animation *animation;
    bool animate;

public:
    Block(sf::Vector2f origin, sf::Vector2f size, sf::View *v, sf::Vector2f *l, bool anim);

    void init_animation(float time);

    int collide(Player *tri);
    void move(float offsetX, float offsetY);
    void moveAnimate(float time);
    void updateCenter();
    void draw(sf::RenderWindow *window);
};

#endif
