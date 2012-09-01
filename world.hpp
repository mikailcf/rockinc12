
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
    void load(string);
    void loadPlayers(FILE*);
    void loadBlocks(FILE*);
    void loadItems(FILE*);
    void drawBackground(sf::RenderWindow&, int);
    void draw(sf::RenderWindow&, int);
    void processInput(sf::Keyboard::Key keyCode, bool keyPressed);
};

#endif

