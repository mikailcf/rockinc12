
#if defined(__APPLE__) || defined(MACOSX)
#include "ResourcePath.hpp"
#endif

#include "defs.hpp"
#include "game.hpp"

Game::Game()
{
    window.create(sf::VideoMode(RES_X, RES_Y), TITLE);
    for (int i = 0; i < 2; i++) {
        views[i].setCenter(400, 300);
        views[i].setSize(RES_X/2, RES_Y);
        views[i].setViewport(sf::FloatRect(i*0.5, 0, 0.5, 1));
    }
    bg_tex.loadFromFile(RES("cute_image.jpg"));
    bg.setTexture(bg_tex);
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
	                    break;
        		}
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

    window.clear();
    for (int i = 0; i < 2; i++) {
        window.setView(views[i]);
        world.Draw(window, i);
    }
    window.draw(bg);
    player->animate(delta_t);
    player->draw(&window);
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
    world.Load(RES(s));
}

