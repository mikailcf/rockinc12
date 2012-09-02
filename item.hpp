
#include "defs.hpp"

#ifndef ITEM_HPP
#define ITEM_HPP

class Item
{
private:
    string nome;
    sf::Texture texture;
    sf::Sprite sprite;
    int move_state;
    int animation_t, jump_t;

public:
    bool picked;
    float left, top, width, height;
    sf::Vector2f spd;
    sf::Vector2i stuck;
    sf::Vector2f pos;

    Item();
    Item(float left, float top, float width, float height, string);
    void draw(sf::RenderWindow *window);
    void updateMove(int mv_state);
    void move(int delta_t);
    // void move(int delta_t, int mv_state);
    void move(float offsetX, float offsetY);
    void accel(int delta_t, float gravity);
};

#endif

