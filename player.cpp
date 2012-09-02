#include <math.h>
#include "player.hpp"

#include "checkpoint.hpp"

Player::Player(){
    item = NULL;
    move_state = 0;
}

Player::Player(float x, float y, std::string filename, World* world){
    tex.loadFromFile(filename);
    animation_t = jump_t = 0;
    state = STAND;
    last_move_state = move_state = 0;
    sprite.move(x, y);

    pos.x = x;
    pos.y = y;
    checkpoint = NULL;

    item = NULL;
    move_state = 0;

    this->world = world;
    // pos.x = 0;
    // pos.y = 15;

    // triangle.setPointCount(3);
    // triangle.setPoint(0, sf::Vector2f(pos.x, -(45 - pos.y)));
    // triangle.setPoint(1, sf::Vector2f(pos.x - 25, pos.y));
    // triangle.setPoint(2, sf::Vector2f(pos.x + 25, pos.y));
    // triangle.setOutlineColor(sf::Color::White);
    // triangle.setOutlineThickness(2.0);
    // triangle.setFillColor(sf::Color(255, 255, 255, 50));

    // triangle.move(x, y);
    pos.x = x;
    pos.y = y;

    animation_t = jump_t = 0;
    angle = target_angle = 0.0;
    turn_spd = 0.0;
    spd.x = spd.y = 0.0;
    stuck.x = stuck.y = 0;
    can_jump = 0;
    jumping = 0;

    left = sprite.getGlobalBounds().left;
    top = sprite.getGlobalBounds().top;
    width = 50;
    height = 50;
}


void Player::draw(sf::RenderWindow *window){
    sprite.setTexture(tex);
    window->draw(sprite);
}

void Player::move(int delta_t){
    if(move_state == 0) spd.x = 0;
    // if(item != NULL) item->move(delta_t, move_state);

    if((spd.x > 0.0 && stuck.x != 1) || (spd.x < 0.0 && stuck.x != -1)){
        move(spd.x * delta_t, 0);
        // if(item != NULL) item->move(spd.x * delta_t, 0);
        // pos.x += spd.x * delta_t;
        // left += spd.x * delta_t;

        stuck.x = 0;
    }

    if((spd.y > 0.0 && stuck.y != 1) || (spd.y < 0.0 && stuck.y != -1)){
        move(0, spd.y * delta_t);
        // if(item != NULL) item->move(0, spd.y * delta_t);
        // pos.y += spd.y * delta_t;
        // top += spd.y * delta_t;
    }
    
}

void Player::move(float offsetX, float offsetY){
    sprite.move(offsetX, offsetY);
    pos.x += offsetX;
    pos.y += offsetY;
    left += offsetX;
    top += offsetY;

    if(item != NULL) item->move(offsetX, offsetY);
}

void Player::setPosition(float x, float y){
    left += x - pos.x;
    top += y - pos.y;
    sprite.move(x - pos.x, y - pos.y);
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
    // sprite.setTextureRect(sf::IntRect(50, 0, 50, 50));
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

void Player::accel(int delta_t, float gravity){
    spd.x += move_state * delta_t * (MAX_SPD/(ACCEL_TIME * 1000.0));
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

int Player::collide_item(Item *item){
    float bottom = top + height;
    float right  = left + width;
    float top_item    = item->top;
    float bottom_item = item->top + item->height;
    float left_item   = item->left;
    float right_item  = item->left + item->width;

    if(top > bottom_item)return 0;
    if(bottom < top_item)return 0;

    if(right < left_item)return 0;
    if(left > right_item)return 0;

    return 1;
}

void Player::processInput(const string key, bool keyPressed) {
    if (!move_state) last_move_state = move_state;
    if (key == "up") {
        teleporting += keyPressed ? 1 : -1;
        if (teleporting < 0)
            teleporting = 0;
    }
    else if (key == "down") {
    }
    else if (key == "left") {
        move_state += (keyPressed == true)? -1 : 1;
    }
    else if (key == "right") {
        move_state += (keyPressed == true)? 1 : -1;
    }
    else if (key == "jump") {
        //começo do pulo
        if (keyPressed && can_jump) jump(-1);
        //para de subir, smooth
        else if (!keyPressed && spd.y < -0.15) spd.y = -0.15;
    }
    else if (key == "item")
    {
    }
}

void Player::stop()
{
    if (!move_state) last_move_state = move_state;
    move_state = 0;
}

int Player::getMovestate()
{
    return move_state;
}

void Player::setCheckpoint(Checkpoint* check)
{
    checkpoint = check;
}

void Player::restoreCheckpoint()
{
    setPosition(checkpoint->getPosition().x, checkpoint->getPosition().y);
    unstuck();
}

void Player::unstuck()
{
    stuck.x = stuck.y = 0;
}

