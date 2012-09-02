
#include "defs.hpp"
#include "player.hpp"
#include "block.hpp"
#include "item.hpp"

#include "box.hpp"

#ifndef WORLD_HPP
#define WORLD_HPP

class World
{
private:
    Player player[2];
    vector<Item> items;
    vector<Block> blocks;
    vector<sf::Music*> score;
    vector<sf::Image> background;

public:
    World();
    void load(string);
    void loadSoundtrack(FILE*);
    void loadBackground(FILE*);
    void loadPlayers(FILE*);
    void loadBlocks(FILE*);
    void loadItems(FILE*);
    void unload();
    void processInput(sf::Keyboard::Key keyCode, bool keyPressed);
    void updateScene(int delta_t);
    void drawBackground(sf::RenderWindow&, int);
    void draw(sf::RenderWindow&, int);
};

#endif

