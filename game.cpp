
#if defined(__APPLE__) || defined(MACOSX)
#include "ResourcePath.hpp"
#endif

#include "defs.hpp"
#include "game.hpp"

Game::Game()
{
    window.create(sf::VideoMode(RES_X, RES_Y), TITLE);
    window.setKeyRepeatEnabled(false);
    for (int i = 0; i < 2; i++) {
        views[i].setCenter((RES_X*i)/2 + RES_X/4, RES_Y/2);
        views[i].setSize(RES_X/2, RES_Y);
        views[i].setViewport(sf::FloatRect(i*0.5, 0, 0.5, 1));
    }
    window.setVerticalSyncEnabled(true);
    state = GAME;
    level = 0;
    newLevel();
}

void Game::processEvents()
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
	                case sf::Keyboard::Space:
                        newLevel();
	                    break;
	                default:
                        world.processInput(event.key.code, true);
	                    break;
        		}
                break;
            case sf::Event::KeyReleased:
                world.processInput(event.key.code, false);
                break;
            default:
                break;
        }
    }
}

void Game::draw()
{
    current_t = clock.getElapsedTime().asMilliseconds();
    delta_t = current_t - last_t;
    last_t = current_t;

    world.updateScene(delta_t);

    window.clear();
    window.setView(window.getDefaultView());
    world.drawBackground(window, delta_t);
    for (int i = 0; i < 2; i++) {
        window.setView(views[i]);
        world.draw(window, i);
    }
    window.display();
}

bool Game::isRunning()
{
    return window.isOpen();
}

void Game::run()
{
    while (isRunning()) {
        processEvents();
        draw();
    }
}

void Game::newLevel()
{
    level++;
    string s("level0.dat");
    s[5] = '0' + level;
    world.load(RES(s));
}

