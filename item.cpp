
#include "defs.hpp"
#include "item.hpp"

Item::Item()
{
}

Item::Item(float left, float top, float width, float height)
{
    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
}

