
#include "defs.hpp"
#include "world.hpp"

void comment(FILE *file){
    char c;

    do c = fgetc(file);
    while(c != '\n');

    c = fgetc(file);

    if(c == '#') comment(file);
    else ungetc(c, file);
}

World::World()
{
}

void World::LoadBlocks(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f", &ox, &oy, &sx, &sy);
        blocks.push_back(Block(sf::Vector2f(ox, oy), sf::Vector2f(sx, sy), NULL, NULL, false));
    }
}

void World::LoadItems(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f", &ox, &oy, &sx, &sy);
        items.push_back(Item(ox, oy, sx, sy));
    }
}

void World::LoadPlayers(FILE* file)
{
    for (int i = 0; i < 2; i++) {
        float x, y;
        fscanf(file, "%f %f", &x, &y);
        player[i] = Player(x, y);
    }
}

void World::Load(string filename)
{
    FILE *level_file = fopen(filename.c_str(), "r");
    if (level_file == NULL)
        exit(EXIT_FAILURE);
    
    LoadPlayers(level_file);
    LoadItems(level_file);
    LoadBlocks(level_file);

    fclose(level_file);
}

void World::Draw(sf::RenderWindow &window, int playerN)
{
//    DrawBackground(window, playerN);

    for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++) {
            
    }
    
    for (vector<Item>::iterator it = items.begin(); it != items.end(); it++) {
            
    }
    
    for (int i = 0; i < 2; i++) {
    
    }
}

