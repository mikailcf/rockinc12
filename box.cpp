#include "box.hpp"
#include "player.hpp"
#include "item.hpp"

Box::Box(){}

Box::Box(sf::Vector2f origin, sf::Vector2f size){
    box.setPointCount(4);
    box.setPoint(0, sf::Vector2f(-size.x/2.0, -size.y/2.0));
    box.setPoint(1, sf::Vector2f(size.x/2.0, -size.y/2.0));
    box.setPoint(2, sf::Vector2f(size.x/2.0, size.y/2.0));
    box.setPoint(3, sf::Vector2f(-size.x/2.0, size.y/2.0));

    box.move(origin + sf::Vector2f(size.x/2.0, size.y/2.0));

    box.setFillColor(sf::Color::Blue);
}

int Box::intersects(Player *player)
{ 
    float top    = box.getGlobalBounds().top;
    float bottom = box.getGlobalBounds().top + box.getGlobalBounds().height;
    float left   = box.getGlobalBounds().left;
    float right  = box.getGlobalBounds().left + box.getGlobalBounds().width;
    float top_player    = player->top;
    float bottom_player = player->top + player->height;
    float left_player   = player->left;
    float right_player  = player->left + player->width;
    float bottom_item;
    float left_item;
    float right_item;
    if (player->item != NULL) {
        bottom_item = player->item->top + player->item->height;
        left_item   = player->item->left;
        right_item  = player->item->left + player->item->width;
    }

    if(top > bottom_player && (player->item == NULL or top > bottom_item)) return 0;
    if(bottom < top_player && (player->item == NULL or bottom < bottom_item)) return 0;

    if(right < left_player && (player->item == NULL or right < left_item)) return 0;
    if(left > right_player && (player->item == NULL or left > right_item)) return 0;
    
    return 1;
}    
    
int Box::collide(Player *player){
    float top    = box.getGlobalBounds().top;
    float bottom = box.getGlobalBounds().top + box.getGlobalBounds().height;
    float left   = box.getGlobalBounds().left;
    float right  = box.getGlobalBounds().left + box.getGlobalBounds().width;
    float top_player    = player->top;
    float bottom_player = player->top + player->height;
    float left_player   = player->left;
    float right_player  = player->left + player->width;
    float top_item;
    float bottom_item;
    float left_item;
    float right_item;
    float max_top;
    float min_bottom;
    float max_left;
    float min_right;

    if (player->item != NULL) {
        top_item    = player->item->top;
        bottom_item = player->item->top + player->item->height;
        left_item   = player->item->left;
        right_item  = player->item->left + player->item->width;
    }

    if((top > bottom_player) && (player->item == NULL || top > bottom_item)) return 0;
    if((bottom < top_player) && (player->item == NULL || bottom < top_item)) return 0;

    if((right < left_player) && (player->item == NULL || right < left_item)) return 0;
    if((left > right_player) && (player->item == NULL || left > right_item)) return 0;

    // PLAYER
    max_top = top > top_player ? top : top_player;
    min_bottom = bottom < bottom_player ? bottom : bottom_player;
    max_left = left > left_player ? left : left_player;
    min_right = right < right_player ? right : right_player;

    if(min_right - max_left > min_bottom - max_top){
        if(top_player < top){                          // veio de cima
            if(player->stuck.y == 0) player->stuck.y = 1;
            player->spd.y = 0.0;
            player->move(0.0, -min_bottom + max_top);
            player->can_jump = 1;
            player->jumping = 0;

            // printf("player de cima\n");
            return 1;
        }
        else{                                           // veio de baixo
            if(player->stuck.y == 0) player->stuck.y = -1;
            player->spd.y = 0.0;
            // player->move(0.0, min_bottom - max_top + 1);

            printf("player de baixo\n");
            return 1;
        }
    }
    else{
        if(left_player < left){                           // veio da esquerda
            if(player->stuck.x == 0) player->stuck.x = 1;
            player->move(-min_right + max_left, 0.0);

            // printf("player de esq\n");
            return 1;
        }
        else if(player->spd.x < 0.0) {                     // veio da direita
            if(player->stuck.x == 0) player->stuck.x = -1;
            player->move(min_right - max_left, 0.0);

            // printf("player de dir\n");
            return 1;
        }
    }

    printf("top_item %f bottom_item %f left_item %f right_item %f\n", top_item, bottom_item, left_item, right_item);
    printf("top %f bottom %f left %f right %f\n", top, bottom, left, right);

    // ITEM
    // if (player->item != NULL) {
    //     printf("tenho um item\n");

    //     max_top = top > top_item ? top : top_item;
    //     min_bottom = bottom < bottom_item ? bottom : bottom_item;
    //     max_left = left > left_item ? left : left_item;
    //     min_right = right < right_item ? right : right_item;

    //     if(min_right - max_left > min_bottom - max_top){   
    //         if(top_item < top){                          // veio de cima
    //             if(player->stuck.y == 0) player->stuck.y = 1;
    //             player->spd.y = 0.0;
    //             player->move(0.0, -min_bottom + max_top);
    //             player->can_jump = 1;
    //             player->jumping = 0;

    //             printf("de cima\n");
    //         }
    //         else{                                           // veio de baixo
    //             if(player->stuck.y == 0) player->stuck.y = -1;
    //             player->spd.y = 0.0;
    //             player->move(0.0, min_bottom - max_top + 1);
    //             printf("de baixo\n");
    //         }
    //     }
    //     else{
    //         if(left_item < left){                           // veio da esquerda
    //             if(player->stuck.x == 0) player->stuck.x = 1;
    //             player->move(-min_right + max_left, 0.0);
    //             printf("de esquerda\n");
    //         }
    //         else if(player->spd.x < 0.0) {                     // veio da direita
    //             if(player->stuck.x == 0) player->stuck.x = -1;
    //             player->move(min_right - max_left, 0.0);
    //             printf("de direita\n");
    //         }
    //     }
    // }
    // else printf("nao tenho item\n");
    return 1;
}

int Box::collide(Item *item){
    float top    = box.getGlobalBounds().top;
    float bottom = box.getGlobalBounds().top + box.getGlobalBounds().height;
    float left   = box.getGlobalBounds().left;
    float right  = box.getGlobalBounds().left + box.getGlobalBounds().width;
    float top_item    = item->top;
    float bottom_item = item->top + item->height;
    float left_item   = item->left;
    float right_item  = item->left + item->width;

    float max_top;
    float min_bottom;
    float max_left;
    float min_right;

    if(top > bottom_item) return 0;
    if(bottom < bottom_item) return 0;

    if(right < left_item) return 0;
    if(left > right_item) return 0;

    // item
    max_top = top > top_item ? top : top_item;
    min_bottom = bottom < bottom_item ? bottom : bottom_item;
    max_left = left > left_item ? left : left_item;
    min_right = right < right_item ? right : right_item;

    if(min_right - max_left > min_bottom - max_top){
        if(top_item < top){                          // veio de cima
            if(item->stuck.y == 0) item->stuck.y = 1;
            item->spd.y = 0.0;
            item->move(0.0, -min_bottom + max_top);
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

void Box::move(float offsetX, float offsetY){
    // if(attached != NULL) attached->move(offsetX, offsetY + 0.1);
    box.move(offsetX, offsetY);
    // this->updateCenter();
}

void Box::draw(sf::RenderWindow *window){
    // sprite.setTexture(tex);
    window->draw(box);
}

sf::Vector2f Box::getPosition()
{
    float top    = box.getGlobalBounds().top;
    float bottom = box.getGlobalBounds().top + box.getGlobalBounds().height;
    float left   = box.getGlobalBounds().left;
    float right  = box.getGlobalBounds().left + box.getGlobalBounds().width;
    return sf::Vector2f((left + right)/2, (top + bottom)/2);
}

