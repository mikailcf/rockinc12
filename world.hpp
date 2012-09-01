
#include "defs.hpp"
#include "player.hpp"
#include "block.hpp"
 #include "item.hpp"

#ifndef WORLD_HPP
#define WORLD_HPP

class World
{
private:
    Player player[2];
    vector<Item> items;
    vector<Block> blocks;
public:
    World();
    void Load(string);
    void LoadPlayers(FILE*);
    void LoadBlocks(FILE*);
    void LoadItems(FILE*);
    void Draw(sf::RenderWindow&, int);
};

#endif

