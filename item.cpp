
#include "defs.hpp"
#include "item.hpp"

Item::Item()
{
}

Item::Item(float left, float top, float width, float height, string nome)
{
    picked = false;
    texture.loadFromFile(nome);
    // cout << "lalala " << nome << endl;
    sprite.setTexture(texture);
    sprite.move(left, top);
    this->left = sprite.getGlobalBounds().left;
    this->top = sprite.getGlobalBounds().top;
    this->width = sprite.getGlobalBounds().width;
    this->height = sprite.getGlobalBounds().height;
    pos.x = left;
    pos.y = top;
}

void Item::draw(sf::RenderWindow *window){
    sprite.setTexture(texture);
    window->draw(sprite);
}

void Item::updateMove(int mv_state){
    move_state = mv_state;
}

// void Item::move(int delta_t){
//     move(delta_t, move_state);
// }

void Item::move(int delta_t){
    // move_state = mv_state;
    if (move_state == 0) spd.x = 0;

    if((spd.x > 0.0 && stuck.x != 1) || (spd.x < 0.0 && stuck.x != -1)){
        sprite.move(spd.x * delta_t, 0);
        pos.x += spd.x * delta_t;
        left += spd.x * delta_t;

        stuck.x = 0;
    }

    if((spd.y > 0.0 && stuck.y != 1) || (spd.y < 0.0 && stuck.y != -1)){
        sprite.move(0, spd.y * delta_t);
        pos.y += spd.y * delta_t;
        top += spd.y * delta_t;
    }
}

void Item::move(float offsetX, float offsetY){
    sprite.move(offsetX, offsetY);
    pos.x += offsetX;
    pos.y += offsetY;
    left += offsetX;
    top += offsetY;
}

void Item::accel(int delta_t, float gravity){
    spd.x += move_state * delta_t * (MAX_SPD/(ACCEL_TIME * 1000.0));
    if(spd.x > MAX_SPD) spd.x = MAX_SPD;
    if(spd.x < -MAX_SPD) spd.x = -MAX_SPD;
    if(stuck.y != 1) spd.y += gravity * delta_t;
}