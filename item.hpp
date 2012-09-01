
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "defs.hpp"

#ifndef ITEM_HPP
#define ITEM_HPP

using namespace std;
using namespace sf;

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

