
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

    sf::Sprite bg_sprite;
    sf::Image bg_img;
public:
    World();
    void Load(string);
    void LoadPlayers(FILE*);
    void LoadBlocks(FILE*);
    void LoadItems(FILE*);
    void DrawBackground(sf::RenderWindow&, int);
    void Draw(sf::RenderWindow&, int);
};

#endif

