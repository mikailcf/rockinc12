
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
    gameover = false;
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
                        gameover = true;
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
    vector<string> fnames;
    vector<int> times;

    loadSound("ingame chuva.ogg");
    fnames.push_back(string("1_final.jpg"));
    fnames.push_back(string("2_final.jpg"));
    fnames.push_back(string("3_final.jpg"));
    fnames.push_back(string("4_final.jpg"));
    times.push_back(1);
    times.push_back(1);
    times.push_back(1);
    times.push_back(1);
    slideShow(fnames, times);
    fnames.clear();
    times.clear();

    gameInit();

    while (!gameover && isRunning()) {
        cout << "asdasda" << endl;
        current_t = clock.getElapsedTime().asMilliseconds();
        delta_t = current_t - last_t;
        last_t = current_t;

        world.updateScene(delta_t);
        processEvents();

        // world.updateScene(delta_t);
        draw();
    }
    world.unload();

    loadSound("ingame chuva.ogg");
    fnames.push_back(string("1.jpg"));
    fnames.push_back(string("2.jpg"));
    fnames.push_back(string("3.jpg"));
    fnames.push_back(string("4.jpg"));
    times.push_back(2);
    times.push_back(2);
    times.push_back(2);
    times.push_back(2);
    slideShow(fnames, times);

    delete sound;
}

void Game::slideShow(vector<string> fnames, vector<int> times){
    vector<sf::Texture *> textures;
    sf::Sprite sprite;
    sf::Clock myclock;

    myclock.restart();
    sound->play();

    for (vector<string>::iterator it = fnames.begin(); it != fnames.end(); it++) {
        sf::Texture * texture = new sf::Texture();
        texture->loadFromFile(RES(*it));
        textures.push_back(texture);
    }

    int i = 0;
    for (vector<sf::Texture *>::iterator it = textures.begin(); it != textures.end(); it++) {
        sf::Sprite sprite;
        sf::Texture * t = (*it);
        sprite.setTexture(*t);
        window.setView(window.getDefaultView());
        window.draw(sprite);
        window.display();
        window.clear();

        int s = myclock.getElapsedTime().asSeconds();
        if (times[i] > s) 
            usleep((int)(1.0f*times[i] - 1.0f*s)*1000000);
        cout << times[i] << " " << myclock.getElapsedTime().asSeconds() << endl;
        myclock.restart();
        i++;
    }

    sound->stop();
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

void Game::loadSound(string name)
{
    sound = new sf::Music();
    if (!sound->openFromFile(RES(name)))
        exit(EXIT_FAILURE);
    sound->setLoop(false);
    sound->setVolume(100);
}

