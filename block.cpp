#include <SFML/OpenGL.hpp>

#include "defs.hpp"
#include "block.hpp"

Block::Block(sf::Vector2f origin, sf::Vector2f size, sf::Color color, sf::View *v, sf::Vector2f *l, bool anim){
    block.setPointCount(4);

    block.setPoint(0, sf::Vector2f(-size.x/2.0, -size.y/2.0));
    block.setPoint(1, sf::Vector2f(size.x/2.0, -size.y/2.0));
    block.setPoint(2, sf::Vector2f(size.x/2.0, size.y/2.0));
    block.setPoint(3, sf::Vector2f(-size.x/2.0, size.y/2.0));

    block.move(origin + sf::Vector2f(size.x/2.0, size.y/2.0));
    initial_center = origin;

    block.setFillColor(color);

    shadow.setPointCount(4);
    shadow.setFillColor(sf::Color(0, 0, 0, 255 * SHADOW_ALPHA));

    relative_position = 0;

    this->updateCenter();
    attached = NULL;
    view = v;
    light = l;
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

void Block::draw(sf::RenderWindow *window, sf::RenderStates render_states){
    window->draw(block, render_states);
}

void Block::castShadow(sf::RenderWindow *window){
    window->draw(shadow);
}

void Block::makeShadow(){
    int relative_position = 0;

    // encontrar posicao relativa ao block
    if(light->x < block.getPosition().x + block.getLocalBounds().left) relative_position += 10;
    else if(light->x < block.getPosition().x + block.getLocalBounds().left + block.getGlobalBounds().width) relative_position += 20;
    else relative_position += 30;

    if(light->y < block.getPosition().y + block.getLocalBounds().top) relative_position += 1;
    else if(light->y < block.getPosition().y + block.getLocalBounds().top + block.getGlobalBounds().height) relative_position += 2;
    else relative_position += 3;


    // escolher o segundo e o terceiro ponto da sombra
    if(relative_position == 21 || relative_position == 31) shadow.setPoint(1, block.getPosition() + block.getPoint(0));
    else if(relative_position == 32 || relative_position == 33) shadow.setPoint(1, block.getPosition() + block.getPoint(1));
    else if(relative_position == 23 || relative_position == 13) shadow.setPoint(1, block.getPosition() + block.getPoint(2));
    else if(relative_position == 12 || relative_position == 11) shadow.setPoint(1, block.getPosition() + block.getPoint(3));

    if(relative_position == 11 || relative_position == 21) shadow.setPoint(2, block.getPosition() + block.getPoint(1));
    else if(relative_position == 31 || relative_position == 32) shadow.setPoint(2, block.getPosition() + block.getPoint(2));
    else if(relative_position == 33 || relative_position == 23) shadow.setPoint(2, block.getPosition() + block.getPoint(3));
    else if(relative_position == 13 || relative_position == 12) shadow.setPoint(2, block.getPosition() + block.getPoint(0));


    // escolher pontos da projecao da sombra
    float aux, k, top, left, right, bottom;
    sf::Vector2f temp, viewPoint[4];
    int done = 0, case0, case1; // 0: em cima; 1: direita; 2: embaixo; 3: esquerda

    viewPoint[0].x = view->getCenter().x - view->getSize().x/2.0;
    viewPoint[0].y = view->getCenter().y - view->getSize().y/2.0;

    viewPoint[1].x = view->getCenter().x + view->getSize().x/2.0;
    viewPoint[1].y = view->getCenter().y - view->getSize().y/2.0;

    viewPoint[2].x = view->getCenter().x + view->getSize().x/2.0;
    viewPoint[2].y = view->getCenter().y + view->getSize().y/2.0;

    viewPoint[3].x = view->getCenter().x - view->getSize().x/2.0;
    viewPoint[3].y = view->getCenter().y + view->getSize().y/2.0;

    left = viewPoint[0].x;
    top = viewPoint[0].y;
    right = viewPoint[2].x;
    bottom = viewPoint[2].y;


    // primeiro ponto (projecao do segundo ponto)

    // primeiro caso (y = top)
    k = (top - light->y)/(shadow.getPoint(1).y - light->y);
    aux = light->x + (shadow.getPoint(1).x - light->x) * k;

    if(k > 0.0)
        if(aux > left && aux < right){
            done = 1;
            temp.x = aux;
            temp.y = top;

            case0 = 0;
        }

    if(!done){
        // segundo caso (x = right)
        k = (right - light->x)/(shadow.getPoint(1).x - light->x);
        aux = light->y + (shadow.getPoint(1).y - light->y) * k;

        if(k > 0.0)
            if(aux > top && aux < bottom){
                done = 1;
                temp.y = aux;
                temp.x = right;

                case0 = 1;
            }
    }

    if(!done){
        // terceiro caso (y = bottom)
        k = (bottom - light->y)/(shadow.getPoint(1).y - light->y);
        aux = light->x + (shadow.getPoint(1).x - light->x) * k;

        if(k > 0.0)
            if(aux > left && aux < right){
                done = 1;
                temp.x = aux;
                temp.y = bottom;

                case0 = 2;
            }
    }

    if(!done){
        // quarto caso (x = left)
        k = (left - light->x)/(shadow.getPoint(1).x - light->x);
        aux = light->y + (shadow.getPoint(1).y - light->y) * k;

        if(k > 0.0)
            if(aux > top && aux < bottom){
                done = 1;
                temp.y = aux;
                temp.x = left;

                case0 = 3;
            }
    }

    // marca o primeiro ponto
    shadow.setPoint(0, temp);


    done = 0;
    // quarto ponto (projecao do terceiro ponto)

    // primeiro caso (y = 0)
    k = (top - light->y)/(shadow.getPoint(2).y - light->y);
    aux = light->x + (shadow.getPoint(2).x - light->x) * k;

    if(k > 0.0)
        if(aux > left && aux < right){
            done = 1;
            temp.x = aux;
            temp.y = top;

            case1 = 0;
        }

    if(!done){
        // segundo caso (x = right)
        k = (right - light->x)/(shadow.getPoint(2).x - light->x);
        aux = light->y + (shadow.getPoint(2).y - light->y) * k;

        if(k > 0.0)
            if(aux > top && aux < bottom){
                done = 1;
                temp.y = aux;
                temp.x = right;

                case1 = 1;
            }
    }

    if(!done){
        // terceiro caso (y = bottom)
        k = (bottom - light->y)/(shadow.getPoint(2).y - light->y);
        aux = light->x + (shadow.getPoint(2).x - light->x) * k;

        if(k > 0.0)
            if(aux > left && aux < right){
                done = 1;
                temp.x = aux;
                temp.y = bottom;

                case1 = 2;
            }
    }

    if(!done){
        // quarto caso (x = left)
        k = (left - light->x)/(shadow.getPoint(2).x - light->x);
        aux = light->y + (shadow.getPoint(2).y - light->y) * k;

        if(k > 0.0)
            if(aux > top && aux < bottom){
                done = 1;
                temp.y = aux;
                temp.x = left;

                case1 = 3;
            }
    }

    // marca o quarto ponto
    shadow.setPoint(3, temp);

    if(case1 != case0){
        if(case1 == 0){
            if(case0 == 1){
                shadow.setPointCount(5);
                shadow.setPoint(4, viewPoint[1]);
            }
            if(case0 == 2){
                shadow.setPointCount(6);
                shadow.setPoint(4, viewPoint[1]);
                shadow.setPoint(5, viewPoint[2]);
            }
        }
        else if(case1 == 1){
            if(case0 == 2){
                shadow.setPointCount(5);
                shadow.setPoint(4, viewPoint[2]);
            }
            if(case0 == 3){
                shadow.setPointCount(6);
                shadow.setPoint(4, viewPoint[2]);
                shadow.setPoint(5, viewPoint[3]);
            }
        }
        else if(case1 == 2){
            if(case0 == 3){
                shadow.setPointCount(5);
                shadow.setPoint(4, viewPoint[3]);
            }
            if(case0 == 0){
                shadow.setPointCount(6);
                shadow.setPoint(4, viewPoint[3]);
                shadow.setPoint(5, viewPoint[0]);
            }
        }
        else if(case1 == 3){
            if(case0 == 0){
                shadow.setPointCount(5);
                shadow.setPoint(4, viewPoint[0]);
            }
            if(case0 == 1){
                shadow.setPointCount(6);
                shadow.setPoint(4, viewPoint[0]);
                shadow.setPoint(5, viewPoint[1]);
            }
        }
    }
    else shadow.setPointCount(4);
}