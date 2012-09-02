
#include "defs.hpp"
#include <vector>

#ifndef EDITOR_HPP
#define EDITOR_HPP

class Editor
{
private:
    sf::RenderWindow window;
    sf::View view;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::ConvexShape * rectVect[2];
    int index;
    int n;

public:
    Editor();
    void processEvents();
    void draw();
    bool isRunning();
    void run();
};

#endif

