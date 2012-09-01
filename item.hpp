
#include "defs.hpp"

#ifndef ITEM_HPP
#define ITEM_HPP

class Item
{
private:
    string nome;
public:
    Item();
    Item(float left, float top, float width, float height);

    float left, top, width, height;

};

#endif

