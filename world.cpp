
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

void World::Load(string filename)
{
    FILE *level_file = fopen(filename.c_str(), "r");
    if (level_file == NULL)
        exit(EXIT_FAILURE);
//    comment(level_file);
//    fscanf(level_file, "%d %d", &n_blocks, &n_hidden_blocks);
    fclose(level_file);
}

void World::Draw(sf::RenderWindow &window, int playerN)
{

}

