
#include "defs.hpp"
#include "item.hpp"

Item::Item()
{
}

Item::Item(float left, float top, float width, float height, string nome)
{
    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
    this->nome = nome;
}

