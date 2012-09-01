#include "block.hpp"

#ifndef LEVEL_HPP
#define LEVEL_HPP

class Level{
    int n_hidden_blocks, n_blocks;
public:
    Level(char *filename, sf::Vector2f *light, sf::View *view);
};

#endif