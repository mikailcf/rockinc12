
#if defined(__APPLE__) || defined(MACOSX)
#include "ResourcePath.hpp"
#endif

#include "defs.hpp"
#include "editor.hpp"

#include <iostream>
#include <vector>

#define STEP 10

Editor::Editor()
{
    //int x = 6046;
    //int y = 1823;
    window.create(sf::VideoMode(960, 680), TITLE);
    window.setVerticalSyncEnabled(true);

    //texture.create(x, y);
    texture.loadFromFile(RES("cenario_tmp.png"));
    sprite.setTexture(texture);

    view.reset(sf::FloatRect(0, 0, 960, 680));
    view.zoom(0.9);

    for(int i = 0; i < 2; i++) {
        rectVect[i] = new sf::ConvexShape();
        rectVect[i]->setPointCount(4);
        rectVect[i]->setPoint(0, sf::Vector2f(0.0, 0.0));
        rectVect[i]->setPoint(1, sf::Vector2f(10.0, 0.0));
        rectVect[i]->setPoint(2, sf::Vector2f(10.0, 10.0));
        rectVect[i]->setPoint(3, sf::Vector2f(0.0, 10.0));
        rectVect[i]->setFillColor(sf::Color(0,(i==0)?255:0,(i==0)?0:255,255));
    }

    n = 0;
}

void Editor::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
	    switch (event.type) {
	        case sf::Event::Closed:
    		    window.close();
                break;
	        case sf::Event::KeyPressed:
	            switch (event.key.code) {
	                case sf::Keyboard::Escape:
            		    window.close();
            		    break;
	                case sf::Keyboard::W:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            rectVect[index]->move(0,-1);
                        else
                            rectVect[index]->move(0,-STEP);
	                    break;
	                case sf::Keyboard::S:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            rectVect[index]->move(0,1);
                        else
                            rectVect[index]->move(0,STEP);
	                    break;
                    case sf::Keyboard::A:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            rectVect[index]->move(-1,0);
                        else
                            rectVect[index]->move(-STEP,0);
	                    break;
	                case sf::Keyboard::D:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            rectVect[index]->move(1,0);
                        else
                            rectVect[index]->move(STEP,0);
	                    break;
                    case sf::Keyboard::Left:
                        index = (index+1)%2;
                        break;
                    case sf::Keyboard::Right:
                        index = (index+1)%2;
                        break;
	                case sf::Keyboard::Space:
                        index = (index+1)%2;
                        n++;
                        cout << rectVect[0]->getGlobalBounds().left << " " << rectVect[0]->getGlobalBounds().top << " "
                            << rectVect[1]->getGlobalBounds().left - rectVect[0]->getGlobalBounds().left << " "
                            << rectVect[1]->getGlobalBounds().top - rectVect[0]->getGlobalBounds().top <<  endl;
	                    break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}

void Editor::draw()
{
    window.clear();
    view.setCenter(0,0);
    view.move(rectVect[index]->getGlobalBounds().left, rectVect[index]->getGlobalBounds().top);
    window.setView(view);
    window.draw(sprite);
    for(int i = 1; i >= 0; i--)
        window.draw(*rectVect[i]);

    window.display();
}

bool Editor::isRunning()
{
    return window.isOpen();
}

void Editor::run()
{
    while (isRunning()) {
        processEvents();
        draw();
    }
    cout << n << endl;
}
