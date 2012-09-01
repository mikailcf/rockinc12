
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

void World::Load(char *filename)
{
    FILE *level_file = fopen(filename, "r");
    if (level_file == NULL)
        exit(EXIT_FAILURE);
    comment(level_file);
//    fscanf(level_file, "%d %d", &n_blocks, &n_hidden_blocks);
    fclose(level_file);
}

void World::Draw(RenderWindow &window, int playerN)
{

}

