
#include "defs.hpp"
#include "player.hpp"
#include "animation.hpp"
#include "item.hpp"

#ifndef BLOCK_HPP
#define BLOCK_HPP

class Block{
    sf::ConvexShape block;
    sf::Vector2f center, initial_center;
    sf::Texture tex;
    sf::Sprite sprite;
    int relative_position;
    Player *attached_player;
    Item *attached_item;
    sf::View *view;
    Animation *animation;
    bool animate;
    sf::Clock clock;

public:
    Block();
    Block(sf::Vector2f origin, sf::Vector2f size, string, string);

    void init_animation();

    int collide(Player *player);
    int collide(Item *item);
    void move(float offsetX, float offsetY);
    void moveAnimate();
    void updateCenter();
    void draw(sf::RenderWindow *window);
};

#endif
