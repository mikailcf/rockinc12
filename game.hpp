
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
    STATE state;
    int level;
    sf::Clock clock;
    int current_t, delta_t, last_t;
    void gameInit();
    void slideShow();
    void loadIntroSound();
public:
    Game();
    void processEvents();
    void draw();
    bool isRunning();
    void run();
    void newLevel();

    sf::Music * introSound;
};

#endif

