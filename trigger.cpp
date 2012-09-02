
#include "trigger.hpp"

Trigger::Trigger()
{
    animation_t = 0;
}

Trigger::Trigger(Box box)
{
    this->box = box;
}

Trigger::Trigger(Box box, std::string filename)
{
    this->box = box;
    texture.loadFromFile(filename);
}

Trigger::Trigger(Box box, std::string filename, int frames)
{
    this->box = box;
    this->frames = frames;
    texture.loadFromFile(filename);
}

void Trigger::check(Player *player)
{
    if (box.intersects(player)) {
        action(player);
    }
}

void Trigger::actionAlternate(Player *player)
{

}

void Trigger::animate(int elapsed_t)
{
    int total_time = FPS*frames;
    animation_t += elapsed_t;
    animation_t %= total_time;
    int i = ((int)animation_t*(total_time/frames)) % frames;
    sf::Vector2u size = texture.getSize();
    int offsetX = (size.x/frames);
    sprite.setTextureRect(sf::IntRect(i*offsetX, 0, (i + 1)*offsetX, size.y));
}

void Trigger::draw(sf::RenderWindow *window)
{
    sprite.setTexture(texture);
    window->draw(sprite);
}

