#include <SFML/Graphics.hpp>
#include "defs.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player{
    sf::ConvexShape triangle;
    int animation_t, jump_t;
    float angle, target_angle;
    float turn_spd;
    sf::Texture tex;
    sf::Sprite sprite;

public:
    sf::Vector2f pos;
    sf::Vector2f spd;
    sf::Vector2i stuck;
    int can_jump;
    int jumping;
    float left, top, width, height;
    PLAYER_STATE state;

    Player();
    Player(std::string filename);
    Player(float x, float y);

    void draw(sf::RenderWindow *window);
    void draw2(sf::RenderWindow *window);
    void move(int delta_t);
    void move(float offsetX, float offsetY);
    void setPosition(float x, float y);

    void setScale(float scale);
    void pulse(int elapsed_t);
    void turn(int move);
    void accel(int move, int delta_t, float gravity);
    void jump(int delta_t);
    void jumpStop();
};

#endif
