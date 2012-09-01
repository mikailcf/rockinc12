#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "game.hpp"

#if defined(__APPLE__) || defined(MACOSX)
#include "ResourcePath.hpp"
#endif

using namespace std;
using namespace sf;

Game::Game()
{
    window.create(VideoMode(RES_X, RES_Y), TITLE);
    for (int i = 0; i < 2; i++) {
        views[i].setCenter(400, 300);
        views[i].setSize(RES_X/2, RES_Y);
        views[i].setViewport(FloatRect(i*0.5, 0, 0.5, 1));
    }
    player = new Player(RES("sheet.png"));
    bg_tex.loadFromFile(RES("cute_image.jpg"));
    bg.setTexture(bg_tex);
}

void Game::processEvents()
{
    Event event;
    while (window.pollEvent(event)) {
	    // Close window : exit
	    if (event.type == Event::Closed)
		    window.close();
        
	    // Escape pressed : exit
	    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		    window.close();
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

