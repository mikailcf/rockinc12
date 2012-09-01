#include <stdio.h>

#include "level.hpp"

void comment(FILE *file){
    char c;

    do c = fgetc(file);
    while(c != '\n');

    c = fgetc(file);

    if(c == '#') comment(file);
    else ungetc(c, file);
}

Level::Level(char *filename, sf::Vector2f *light, sf::View *view){
    FILE *level_file;

    level_file = fopen(filename, "r");

    comment(level_file);
    fscanf(level_file, "%d %d", &n_blocks, &n_hidden_blocks);
}