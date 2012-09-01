
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "player.hpp"
#include "block.hpp"
#include "item.hpp"

#ifndef WORLD_HPP
#define WORLD_HPP

using namespace std;
using namespace sf;

class World
{
private:
    Player player[2];
    vector<Item> items;
    vector<Block> blocks;
public:
    World();
    void Load(string);
    void Draw(RenderWindow&, int);
};

#endif

