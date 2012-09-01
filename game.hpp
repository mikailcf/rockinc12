
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "world.hpp"
#include "player.hpp"

#ifndef GAME_HPP
#define GAME_HPP

using namespace std;
using namespace sf;

class Game
{
private:
    RenderWindow window;
    View views[2];
    World world;
    Player *player;
    sf::Texture bg_tex;
    sf::Sprite bg;
public:
    Game();
    void processEvents();
    void draw();
    bool isRunning();
    void run();
};

#endif
