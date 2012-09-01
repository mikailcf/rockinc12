
#include "defs.hpp"
#include "world.hpp"
#include "player.hpp"

#ifndef GAME_HPP
#define GAME_HPP

class Game
{
private:
    sf::RenderWindow window;
    sf::View views[2];
    World world;
    sf::Texture bg_tex;
    sf::Sprite bg;
    int state, level;
public:
    Game();
    void processEvents();
    void draw();
    bool isRunning();
    void run();
    void newLevel();
};

#endif
