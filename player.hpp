#include <SFML/Graphics.hpp>
#include "defs.hpp"
#include "item.hpp"

class Checkpoint;
class World;

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player{
    sf::ConvexShape triangle;
    int animation_t, jump_t;
    int move_state;
    int last_move_state;
    float angle, target_angle;
    float turn_spd;
    sf::Texture tex;
    sf::Sprite sprite;
    Checkpoint* checkpoint;

public:
    World *world;
    sf::Vector2f pos;
    sf::Vector2f spd;
    sf::Vector2i stuck;
    int can_jump;
    int jumping;
    int teleporting;
    float left, top, width, height;
    PLAYER_STATE state;

    Item * item;

    Player();
    Player(float, float, std::string filename, World*);
    Player(float x, float y);

    void draw(sf::RenderWindow *window);
    void move(int delta_t);
    void move(float offsetX, float offsetY);
    void setPosition(float x, float y);

    void setScale(float scale);
    void pulse(int elapsed_t);
    void animate(int elapsed_t);
    void turn(int move);
    void accel(int delta_t, float gravity);
    void jump(int delta_t);
    
    void processInput(const string key, bool keyPressed);
    void stop();
    int getMovestate();

    void setCheckpoint(Checkpoint*);
    void restoreCheckpoint();
    void unstuck();
};
#endif
