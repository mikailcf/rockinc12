#include "text.hpp"
#include "defs.hpp"

Text::Text(std::string font_file, std::string shadow_font_file, sf::Vector2f *l, int size){
    font.loadFromFile(font_file);
    shadow_font.loadFromFile(shadow_font_file);

    text.setFont(font);
    text.setColor(sf::Color(150, 150, 150, 255));
    text.setCharacterSize(size);

    selected_text.setFont(font);
    selected_text.setColor(sf::Color(255, 255, 255, 255));
    selected_text.setCharacterSize(size);

    shadow.setFont(shadow_font);
    shadow.setColor(sf::Color(0, 0, 0, 80));
    shadow.setCharacterSize((int) size);

    light = l;
    selected = false;
}

void Text::setString(std::string string){
    text.setString(string);
    selected_text.setString(string);
    shadow.setString(string);
}

void Text::select(){
    selected = true;
}

void Text::deselect(){
    selected = false;
}

void Text::setPosition(sf::Vector2f pos){
    text.setPosition(pos);
    selected_text.setPosition(pos);
    shadow.setPosition(pos);
}

void Text::draw(sf::RenderWindow *window){
    if(selected) window->draw(selected_text);
    else window->draw(text);
}

void Text::castShadow(sf::RenderWindow *window){
    window->draw(shadow);
}

void Text::makeShadow(){
    float projection_left, projection_top, projection_right, projection_bottom;
    float left, top, right, bottom;

    left = text.getGlobalBounds().left;
    projection_left = left - light->x;
    projection_left *= TEXT_TO_WALL/LIGHT_TO_TEXT;
    projection_left += left;

    right = text.getGlobalBounds().left + text.getGlobalBounds().width;
    projection_right = right - light->x;
    projection_right *= TEXT_TO_WALL/LIGHT_TO_TEXT;
    projection_right += right;

    top = text.getGlobalBounds().top;
    projection_top = top - light->y;
    projection_top *= TEXT_TO_WALL/LIGHT_TO_TEXT;
    projection_top += top;

    bottom = text.getGlobalBounds().top + text.getGlobalBounds().height;
    projection_bottom = bottom - light->y;
    projection_bottom *= TEXT_TO_WALL/LIGHT_TO_TEXT;
    projection_bottom += bottom;

    shadow.scale((float) (projection_right - projection_left)/shadow.getGlobalBounds().width, (float) (projection_bottom - projection_top)/shadow.getGlobalBounds().height);
    shadow.move(projection_left - shadow.getGlobalBounds().left, projection_top - shadow.getGlobalBounds().top);
}