#include <math.h>
#include "player.hpp"

Player::Player(){item = NULL;};

Player::Player(std::string filename){
    tex.loadFromFile(filename);
    sprite.setTexture(tex);

    animation_t = jump_t = 0;
    state = STAND;

    sprite.move(500.0, 0);
}

Player::Player(float x, float y){
    item = NULL;

    pos.x = 0;
    pos.y = 15;

    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(pos.x, -(45 - pos.y)));
    triangle.setPoint(1, sf::Vector2f(pos.x - 25, pos.y));
    triangle.setPoint(2, sf::Vector2f(pos.x + 25, pos.y));
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(2.0);
    triangle.setFillColor(sf::Color(255, 255, 255, 50));

    triangle.move(x, y);
    pos.x = x;
    pos.y = y;

    animation_t = jump_t = 0;
    angle = target_angle = 0.0;
    turn_spd = 0.0;
    spd.x = spd.y = 0.0;
    stuck.x = stuck.y = 0;
    can_jump = 0;
    jumping = 0;
    left = triangle.getGlobalBounds().left + 3.0;
    top = triangle.getGlobalBounds().top;
    width = triangle.getGlobalBounds().width - 5.0;
    height = triangle.getGlobalBounds().height;
}

void Player::draw(sf::RenderWindow *window){
    window->draw(sprite);
}

void Player::move(int delta_t){
    if((spd.x > 0.0 && stuck.x != 1) || (spd.x < 0.0 && stuck.x != -1)){
        triangle.move(spd.x * delta_t, 0);
        pos.x += spd.x * delta_t;
        left += spd.x * delta_t;

        stuck.x = 0;
    }

    if((spd.y > 0.0 && stuck.y != 1) || (spd.y < 0.0 && stuck.y != -1)){
        triangle.move(0, spd.y * delta_t);
        pos.y += spd.y * delta_t;
        top += spd.y * delta_t;
    }
}

void Player::move(float offsetX, float offsetY){
    triangle.move(offsetX, offsetY);
    pos.x += offsetX;
    pos.y += offsetY;
    left += offsetX;
    top += offsetY;
}

void Player::setPosition(float x, float y){
    left += x - pos.x;
    top += y - pos.y;
    triangle.move(x - pos.x, y - pos.y);
    pos.x = x;
    pos.y = y;
}

void Player::setScale(float scale){
    triangle.setScale(scale, scale);
}

void Player::animate(int elapsed_t){
    int i;
    animation_t += elapsed_t;
    animation_t %= 1000;

    i = (int) animation_t/125;
    i %= 8;

    sprite.setTextureRect(sf::IntRect(i*50, 0, 50, 50));
}

void Player::turn(int move){
    if(move == 1){
        turn_spd = (MAX_ANGLE - angle)/TURN_TIME;
        target_angle = MAX_ANGLE;
    }
    else if(move == -1){
        turn_spd = (-MAX_ANGLE - angle)/TURN_TIME;
        target_angle = -MAX_ANGLE;
    }
    else if(move == 0){
        turn_spd = (-angle)/TURN_TIME;
        target_angle = 0;
    }
}

void Player::accel(int move, int delta_t, float gravity){
    spd.x += move * delta_t * (MAX_SPD/(ACCEL_TIME * 1000.0));
    if(spd.x > MAX_SPD) spd.x = MAX_SPD;
    if(spd.x < -MAX_SPD) spd.x = -MAX_SPD;
    if(stuck.y != 1) spd.y += gravity * delta_t;
}

void Player::jump(int delta_t){
    if(delta_t == -1){
        jump_t = 0;
        spd.y += -JUMP_SPD/2.0;

        can_jump = 0;
        jumping = 1;
    }
    else jump_t += delta_t;

    stuck.y = 0;

    if(jump_t > JUMP_TIME*333){
        spd.y += -JUMP_SPD/1.9;
        jumping = 0;
        return;
    }
}
