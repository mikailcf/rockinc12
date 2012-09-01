#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "animation.hpp"

#ifndef BLOCK_HPP
#define BLOCK_HPP

class Block{
    sf::ConvexShape block;
    sf::ConvexShape shadow;
    sf::Vector2f center, initial_center;
    int relative_position;
    Player *attached;
    sf::View *view;
    sf::Vector2f *light;
    Animation *animation;
    bool animate;

public:
    Block(sf::Vector2f origin, sf::Vector2f size, sf::Color color, sf::View *v, sf::Vector2f *l, bool anim);

    void init_animation(float time);

    int collide(Player *tri);
    void move(float offsetX, float offsetY);
    void moveAnimate(float time);
    void updateCenter();
    void draw(sf::RenderWindow *window);
    void draw(sf::RenderWindow *window, sf::RenderStates render_states);
    void castShadow(sf::RenderWindow *window);
    void makeShadow();
};

#endif