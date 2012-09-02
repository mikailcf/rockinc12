#include <SFML/OpenGL.hpp>
#include "block.hpp"

Block::Block(sf::Vector2f origin, sf::Vector2f size, std::string animType, std::string filename){
    block.setPointCount(4);

    block.setPoint(0, sf::Vector2f(-size.x/2.0, -size.y/2.0));
    block.setPoint(1, sf::Vector2f(size.x/2.0, -size.y/2.0));
    block.setPoint(2, sf::Vector2f(size.x/2.0, size.y/2.0));
    block.setPoint(3, sf::Vector2f(-size.x/2.0, size.y/2.0));

    tex.loadFromFile(filename);
    sprite.setTexture(tex);
   
    sprite.move(origin);
    block.move(origin + sf::Vector2f(size.x/2.0, size.y/2.0));
    initial_center = origin;

    relative_position = 0;

    this->updateCenter();
    attached_player = NULL;
    attached_item = NULL;

    float dist = 400;

    if(animType == "hori") {
        animate = true;
        animation = new Animation(2);
        animation->setSection(0, 2.0, 1.0, 0.0, sf::Vector2f(dist, 0.0), 0.2, 0.8);
        animation->setSection(1, 2.0, 1.0, 0.0, sf::Vector2f(-dist, 0.0), 0.2, 0.8);
        animation->setLoop(true);
        init_animation();
    }
    else if (animType == "vert") {
        animate = true;
        animation = new Animation(2);
        animation->setSection(0, 2.0, 1.0, 0.0, sf::Vector2f(0.0, dist), 0.2, 0.8);
        animation->setSection(1, 2.0, 1.0, 0.0, sf::Vector2f(0.0, -dist), 0.2, 0.8);
        animation->setLoop(true);
        init_animation();
    }
}

void Block::init_animation(){
    float time = clock.getElapsedTime().asSeconds();
    animation->start(time);
}

int Block::collide(Player *player){
    float top    = block.getGlobalBounds().top;
    float bottom = block.getGlobalBounds().top + block.getGlobalBounds().height;
    float left   = block.getGlobalBounds().left;
    float right  = block.getGlobalBounds().left + block.getGlobalBounds().width;
    float top_player    = player->top;
    float bottom_player = player->top + player->height;
    float left_player   = player->left;
    float right_player  = player->left + player->width;
    float max_top;
    float min_bottom;
    float max_left;
    float min_right;

    if(top > bottom_player){
        attached_player = NULL;
        return 0;
    }
    if(bottom < top_player){
        attached_player = NULL;
        return 0;
    }

    if(right < left_player){
        attached_player = NULL;
        return 0;
    }
    if(left > right_player){
        attached_player = NULL;
        return 0;
    }

    max_top = top > top_player ? top : top_player;
    min_bottom = bottom < bottom_player ? bottom : bottom_player;
    max_left = left > left_player ? left : left_player;
    min_right = right < right_player ? right : right_player;

    if(min_right - max_left > min_bottom - max_top){
        if(top_player < top){                          // veio de cima
            if(player->stuck.y == 0) player->stuck.y = 1;
            player->spd.y = 0.0;
            player->move(0.0, -min_bottom + max_top);
            attached_player = player;
            player->can_jump = 1;
            player->jumping = 0;

        }
        else{                                           // veio de baixo
            if(player->stuck.y == 0) player->stuck.y = -1;
            player->spd.y = 0.0;
            player->move(0.0, min_bottom - max_top + 1);

        }
    }
    else{
        if(left_player < left){                           // veio da esquerda
            if(player->stuck.x == 0) player->stuck.x = 1;
            player->move(-min_right + max_left, 0.0);
        }
        else if(player->spd.x < 0.0) {                     // veio da direita
            if(player->stuck.x == 0) player->stuck.x = -1;
            player->move(min_right - max_left, 0.0);
        }
    }

    return 1;
}

int Block::collide(Item *item){
    float top    = block.getGlobalBounds().top;
    float bottom = block.getGlobalBounds().top + block.getGlobalBounds().height;
    float left   = block.getGlobalBounds().left;
    float right  = block.getGlobalBounds().left + block.getGlobalBounds().width;
    float top_item    = item->top;
    float bottom_item = item->top + item->height;
    float left_item   = item->left;
    float right_item  = item->left + item->width;
    float max_top;
    float min_bottom;
    float max_left;
    float min_right;

    if(top > bottom_item){
        attached_item = NULL;
        return 0;
    }
    if(bottom < top_item){
        attached_item = NULL;
        return 0;
    }

    if(right < left_item){
        attached_item = NULL;
        return 0;
    }
    if(left > right_item){
        attached_item = NULL;
        return 0;
    }

    max_top = top > top_item ? top : top_item;
    min_bottom = bottom < bottom_item ? bottom : bottom_item;
    max_left = left > left_item ? left : left_item;
    min_right = right < right_item ? right : right_item;

    if(min_right - max_left > min_bottom - max_top){
        if(top_item < top){                          // veio de cima
            if(item->stuck.y == 0) item->stuck.y = 1;
            item->spd.y = 0.0;
            item->spd.x = 0.0;
            item->move(0.0, -min_bottom + max_top);
            attached_item = item;
        }
        else{                                           // veio de baixo
            if(item->stuck.y == 0) item->stuck.y = -1;
            item->spd.y = 0.0;
            item->move(0.0, min_bottom - max_top + 1);
        }
    }
    else{
        if(left_item < left){                           // veio da esquerda
            if(item->stuck.x == 0) item->stuck.x = 1;
            item->move(-min_right + max_left, 0.0);
        }
        else if(item->spd.x < 0.0) {                     // veio da direita
            if(item->stuck.x == 0) item->stuck.x = -1;
            item->move(min_right - max_left, 0.0);
        }
    }

    return 1;
}

void Block::move(float offsetX, float offsetY){
    if(attached_player != NULL) attached_player->move(offsetX, offsetY + 0.1);
    if(attached_item != NULL) attached_item->move(offsetX, offsetY + 0.1);
    block.move(offsetX, offsetY);
    this->updateCenter();
    sprite.move(offsetX, offsetY);
}

void Block::moveAnimate(){
    float time = clock.getElapsedTime().asSeconds();
    //cout << time << endl;
    //cout << animation->getPosition(time).x << " " << initial_center.x - block.getGlobalBounds().left << " " << animation->getPosition(time).y << " " << initial_center.y - block.getGlobalBounds().top << endl;
    move(animation->getPosition(time).x + initial_center.x - block.getGlobalBounds().left,
         animation->getPosition(time).y + initial_center.y - block.getGlobalBounds().top);
}

void Block::updateCenter(){
    center.x = block.getGlobalBounds().left + block.getGlobalBounds().width/2.0;
    center.y = block.getGlobalBounds().top + block.getGlobalBounds().height/2.0;
}

void Block::draw(sf::RenderWindow *window){
    this->updateCenter();
    sprite.setTexture(tex);
    //sprite.setOrigin(block.getGlobalBounds().left, block.getGlobalBounds().top);
    //cout << sprite.getGlobalBounds().left << " " << sprite.getGlobalBounds().top  << endl;
    window->draw(sprite);
}

