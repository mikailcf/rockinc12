#include <SFML/OpenGL.hpp>
#include "block.hpp"

Block::Block(sf::Vector2f origin, sf::Vector2f size, sf::View *v, sf::Vector2f *l, bool anim){
    block.setPointCount(4);

    block.setPoint(0, sf::Vector2f(-size.x/2.0, -size.y/2.0));
    block.setPoint(1, sf::Vector2f(size.x/2.0, -size.y/2.0));
    block.setPoint(2, sf::Vector2f(size.x/2.0, size.y/2.0));
    block.setPoint(3, sf::Vector2f(-size.x/2.0, size.y/2.0));

    block.move(origin + sf::Vector2f(size.x/2.0, size.y/2.0));
    initial_center = origin;

    relative_position = 0;

    this->updateCenter();
    attached = NULL;
    view = v;
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

int Block::collide(Player *tri){
    float top    = block.getGlobalBounds().top;
    float bottom = block.getGlobalBounds().top + block.getGlobalBounds().height;
    float left   = block.getGlobalBounds().left;
    float right  = block.getGlobalBounds().left + block.getGlobalBounds().width;
    float top_tri    = tri->top;
    float bottom_tri = tri->top + tri->height;
    float left_tri   = tri->left;
    float right_tri  = tri->left + tri->width;
    float max_top;
    float min_bottom;
    float max_left;
    float min_right;

    if(top > bottom_tri){
        attached = NULL;
        return 0;
    }
    if(bottom < top_tri){
        attached = NULL;
        return 0;
    }

    if(right < left_tri){
        attached = NULL;
        return 0;
    }
    if(left > right_tri){
        attached = NULL;
        return 0;
    }

    max_top = top > top_tri ? top : top_tri;
    min_bottom = bottom < bottom_tri ? bottom : bottom_tri;
    max_left = left > left_tri ? left : left_tri;
    min_right = right < right_tri ? right : right_tri;

    if(min_right - max_left > min_bottom - max_top){
        if(top_tri < top){                          // veio de cima
            if(tri->stuck.y == 0) tri->stuck.y = 1;
            tri->spd.y = 0.0;
            tri->move(0.0, -min_bottom + max_top);
            attached = tri;
            tri->can_jump = 1;
            tri->jumping = 0;
        }
        else{                                           // veio de baixo
            if(tri->stuck.y == 0) tri->stuck.y = -1;
            tri->spd.y = 0.0;
            tri->move(0.0, min_bottom - max_top + 1);
        }
    }
    else{
        if(left_tri < left){                           // veio da esquerda
            if(tri->stuck.x == 0) tri->stuck.x = 1;
            tri->move(-min_right + max_left, 0.0);
        }
        else if(tri->spd.x < 0.0) {                     // veio da direita
            if(tri->stuck.x == 0) tri->stuck.x = -1;
            tri->move(min_right - max_left, 0.0);
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

