#include <SFML/Graphics.hpp>
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
    void move(float offsetX, float offsetY);
};

#endif
