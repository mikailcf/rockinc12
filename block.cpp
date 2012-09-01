#include <SFML/OpenGL.hpp>
#include "block.hpp"

Block::Block(sf::Vector2f origin, sf::Vector2f size, bool anim){
    block.setPointCount(4);

    block.setPoint(0, sf::Vector2f(-size.x/2.0, -size.y/2.0));
    block.setPoint(1, sf::Vector2f(size.x/2.0, -size.y/2.0));
    block.setPoint(2, sf::Vector2f(size.x/2.0, size.y/2.0));
    block.setPoint(3, sf::Vector2f(-size.x/2.0, size.y/2.0));

    block.setFillColor(sf::Color(255, 255, 255, 255));

    block.move(origin + sf::Vector2f(size.x/2.0, size.y/2.0));
    initial_center = origin;

    relative_position = 0;

    this->updateCenter();
    attached = NULL;
    animate = anim;

    if(anim){
        animation = new Animation(4);
        animation->setSection(0, 2.0, 1.0, 0.0, sf::Vector2f(500.0, 100.0), 0.2, 0.8);
        animation->setSection(1, 1.4, 1.0, 0.0, sf::Vector2f(100.0, -200.0), 0.2, 0.8);
        animation->setSection(2, 1.4, 1.0, 0.0, sf::Vector2f(-100.0, 200.0), 0.2, 0.8);
        animation->setSection(3, 2.0, 1.0, 0.0, sf::Vector2f(-500.0, -100.0), 0.2, 0.8);
        animation->setLoop(true);
    }
}

void Block::init_animation(float time){
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
        attached = NULL;
        return 0;
    }
    if(bottom < top_player){
        attached = NULL;
        return 0;
    }

    if(right < left_player){
        attached = NULL;
        return 0;
    }
    if(left > right_player){
        attached = NULL;
        return 0;
    }

    max_top = top > top_player ? top : top_player;
    min_bottom = bottom < bottom_player ? bottom : bottom_player;
    max_left = left > left_player ? left : left_player;
    min_right = right < right_player ? right : right_player;

    if(min_right - max_left > min_bottom - max_top){
        printf("veio de ");
        if(top_player < top){                          // veio de cima
            if(player->stuck.y == 0) player->stuck.y = 1;
            player->spd.y = 0.0;
            player->move(0.0, -min_bottom + max_top);
            attached = player;
            player->can_jump = 1;
            player->jumping = 0;

            printf("veio de cima");
        }
        else{                                           // veio de baixo
            if(player->stuck.y == 0) player->stuck.y = -1;
            player->spd.y = 0.0;
            player->move(0.0, min_bottom - max_top + 1);

            printf("veio de baixo");
        }
    }
    else{
        printf("veio de nada");
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

void Block::move(float offsetX, float offsetY){
    if(attached != NULL) attached->move(offsetX, offsetY + 0.1);
    block.move(offsetX, offsetY);
    this->updateCenter();
}

void Block::moveAnimate(float time){
    move(animation->getPosition(time).x + initial_center.x - block.getGlobalBounds().left,
         animation->getPosition(time).y + initial_center.y - block.getGlobalBounds().top);
}

void Block::updateCenter(){
    center.x = block.getGlobalBounds().left + block.getGlobalBounds().width/2.0;
    center.y = block.getGlobalBounds().top + block.getGlobalBounds().height/2.0;
}

void Block::draw(sf::RenderWindow *window){
    window->draw(block);
}

