
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
    void slideShow(vector<string> fnames, vector<int> times);
    void loadSound(const string name);
public:
    Game();
    void processEvents();
    void draw();
    bool isRunning();
    void run();
    void newLevel();
    bool gameover;

    sf::Music * sound;
};

#endif

