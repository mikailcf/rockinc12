
#if defined(__APPLE__) || defined(MACOSX)
#include "ResourcePath.hpp"
#endif

#include "defs.hpp"
#include "game.hpp"
#include "box.hpp"
#include <iostream>
#include <unistd.h>

Game::Game()
{
    window.create(sf::VideoMode(RES_X, RES_Y), TITLE);
    window.setKeyRepeatEnabled(false);
    for (int i = 0; i < 2; i++) {
        views[i].setSize(RES_X/2, RES_Y);
        views[i].setViewport(sf::FloatRect(0.501*i, 0, 0.499, 1));
    }
    window.setVerticalSyncEnabled(true);
}

void Game::gameInit() {
    level = 0;
    last_t = 0;
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
	                case sf::Keyboard::Tab:
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) world.jumping(delta_t, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) world.jumping(delta_t, 1);
}

void Game::draw()
{
    // current_t = clock.getElapsedTime().asMilliseconds();
    // delta_t = current_t - last_t;
    // last_t = current_t;

    // world.updateScene(delta_t);

    window.clear();
    int dx = abs((int)(world.getCenter(0).x - world.getCenter(1).x));
    int dy = abs((int)(world.getCenter(0).y - world.getCenter(1).y));
    if (world.united || (dx < RES_X/2 && world.podeTerminar && dy < RES_Y)) {
        world.united = true;
        sf::View view = window.getDefaultView();
        view.setCenter(sf::Vector2f(min(world.getCenter(0).x, world.getCenter(1).x) + dx/2, RES_Y/2));
        window.setView(view);
        world.drawBackground(window, delta_t);    
        world.draw(window, delta_t);
    }
    else
        for (int i = 0; i < 2; i++) {
            views[i].setCenter(world.getCenter(i));
            window.setView(views[i]);
            world.drawBackground(window, delta_t);
            world.draw(window, delta_t);
        }
    window.display();
}

bool Game::isRunning()
{
    return window.isOpen();
}

void Game::run()
{
    loadIntroSound();
    slideShow();
    introSound->stop();
    delete introSound;
    gameInit();

    while (isRunning()) {
        current_t = clock.getElapsedTime().asMilliseconds();
        delta_t = current_t - last_t;
        last_t = current_t;

        world.updateScene(delta_t);
        processEvents();

        // world.updateScene(delta_t);
        draw();
    }
}

void Game::slideShow(){
    vector<sf::Texture *> textures;
    vector<string> fnames;
    sf::Sprite sprite;

    fnames.push_back(string("1_final.jpg"));
    fnames.push_back(string("2_final.jpg"));
    fnames.push_back(string("3_final.jpg"));
    fnames.push_back(string("4_final.jpg"));
    
    int n = 4;
    int sleepTime = 1000000;
    for(int i = 0; i < n; i++) {
        sf::Texture * texture = new sf::Texture();
        texture->loadFromFile(RES(fnames[i]));
        textures.push_back(texture);
    }

    for (vector<sf::Texture *>::iterator it = textures.begin(); it != textures.end(); it++) {
        sf::Sprite sprite;
        sf::Texture * t = (*it);
        sprite.setTexture(*t);
        window.draw(sprite);
        window.display();
        window.clear();
        usleep(sleepTime);
    }
}

void Game::newLevel()
{
    clock.restart();
    world.united = false;
    if (level++ > 0)
        world.unload();
    string s("level0.dat");
    s[5] = '0' + level;
    world.load(RES(s));
}

void Game::loadIntroSound()
{
    introSound = new sf::Music();
    if (!introSound->openFromFile(RES("ingame chuva.ogg")))
        exit(EXIT_FAILURE);
    introSound->setLoop(false);
    introSound->setVolume(100);
    introSound->play();
}

