
#include "defs.hpp"
#include "player.hpp"
#include "block.hpp"
#include "item.hpp"
#include "checkpoint.hpp"
#include "trap.hpp"

#include "box.hpp"

#ifndef WORLD_HPP
#define WORLD_HPP

class World
{
private:
    Player player[2];
    vector<Item> items;
    vector<Block> blocks;
    vector<Box> boxes;
    vector<sf::Music*> score;
    vector<sf::Image> background;
    vector<Checkpoint> checkpoints;
    vector<Trap> traps;

public:
    bool podeTerminar;
    bool united;
    World();
    void load(string);
    void loadSoundtrack(FILE*);
    void loadBackground(FILE*);
    void loadPlayers(FILE*);
    void loadBlocks(FILE*);
    void loadBoxes(FILE*);
    void loadItems(FILE*);
    void loadCheckpoints(FILE*);
    void loadTraps(FILE*);
    void unload();
    void processInput(sf::Keyboard::Key keyCode, bool keyPressed);
    void jumping(int delta_t, int player_num);
    void updateScene(int delta_t);
    void drawBackground(sf::RenderWindow&, int);
    void draw(sf::RenderWindow&, int);
    sf::Vector2f getCenter(int i);
};

#endif

