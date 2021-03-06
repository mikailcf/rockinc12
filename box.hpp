
#include "defs.hpp"
#include "player.hpp"

#ifndef BOX_HPP
#define BOX_HPP

class Box{
    sf::ConvexShape box;
    sf::Vector2f center, initial_center;
    int relative_position;
    bool animate;

public:
    Box();
    Box(sf::Vector2f origin, sf::Vector2f size);

    int collide(Player *player);
    int collide(Item *item);
    int intersects(Player *player);
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow *window);
    sf::Vector2f getPosition();
};

#endif
