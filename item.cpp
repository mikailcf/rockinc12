
#include "defs.hpp"
#include "item.hpp"

Item::Item()
{
}

Item::Item(float left, float top, float width, float height, string nome)
{
    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
    texture.loadFromFile(nome);
    // cout << "lalala " << nome << endl;
    sprite.setTexture(texture);
}

void Item::draw(sf::RenderWindow *window){
    sprite.setTexture(texture);
    window->draw(sprite);
}

void Item::move(int delta_t){
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