#include "SFML/Graphics.hpp"

#ifndef TEXT_HPP
#define TEXT_HPP

class Text{
    sf::Text text;
    sf::Text selected_text;
    sf::Text shadow;
    sf::Font font;
    sf::Font shadow_font;

    sf::Vector2f *light;

    bool selected;

public:
    Text(std::string font_file, std::string shadow_font_file, sf::Vector2f *l, int size);

    void setString(std::string string);

    void select();
    void deselect();

    void setPosition(sf::Vector2f pos);
    void draw(sf::RenderWindow *window);
    void castShadow(sf::RenderWindow *window);
    void makeShadow();
};

#endif