#include "defs.hpp"
#include "world.hpp"

void comment(FILE *file){
    char c;

    do c = fgetc(file);
    while(c != '\n');

    c = fgetc(file);

    if(c == '#') comment(file);
    else ungetc(c, file);
}

World::World()
{
}

void World::loadBackground(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    char filename[MAX_NAME];
    while (n--) {
        fscanf(file, "%s", filename);
        sf::Image image;
        image.loadFromFile(RES(string(filename)));
        background.push_back(image);
    }
}

void World::loadSoundtrack(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        char filename[MAX_NAME];
        fscanf(file, "%s\n", filename);
/*        sf::Music *sound = new sf::Music();
        if (!sound->openFromFile(RES(string(filename))))
            exit(EXIT_FAILURE);
        sound->setLoop(true);
        sound->setVolume(100);
        sound->play();
        score.push_back(sound);*/
    }
}

void World::loadBlocks(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        char filename[MAX_NAME];
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f %s", &ox, &oy, &sx, &sy, filename);
        blocks.push_back(Block(sf::Vector2f(ox, oy), sf::Vector2f(sx, sy), false, RES(string(filename))));
    }
}

void World::loadItems(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        char filename[MAX_NAME];
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f %s", &ox, &oy, &sx, &sy, filename);
        items.push_back(Item(ox, oy, sx, sy, RES(string(filename))));
    }
}

void World::loadPlayers(FILE* file)
{
    for (int i = 0; i < 2; i++) {
        char filename[MAX_NAME];
        float x, y;
        fscanf(file, "%f %f %s", &x, &y, filename);
        printf("%f %f %s\n", x, y, filename);
        player[i] = Player(x, y, RES(string(filename)));
    }
}

void World::load(string filename)
{
    FILE *level_file = fopen(filename.c_str(), "r");
    if (level_file == NULL)
        exit(EXIT_FAILURE);

    loadBackground(level_file);
    loadSoundtrack(level_file);
    loadPlayers(level_file);
    loadItems(level_file);
    loadBlocks(level_file);

    fclose(level_file);
}

void World::drawBackground(sf::RenderWindow &window, int delta_t)
{
    for (vector<sf::Image>::iterator it = background.begin(); it != background.end(); it++) { 
        sf::Texture texture;
        texture.loadFromImage(*it);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        window.draw(sprite);
    }
}

void World::draw(sf::RenderWindow &window, int delta_t)
{
    for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++) {
        it->draw(&window);
    }
    for (vector<Item>::iterator it = items.begin(); it != items.end(); it++) {
            
    }
    for (int i = 0; i < 2; i++) {
        player[i].animate(delta_t);
        player[i].draw(&window);    
    }
}

void World::processInput(sf::Keyboard::Key keyCode, bool keyPressed) {
    switch (keyCode) {
        case sf::Keyboard::W:
            player[0].processInput("up", keyPressed);
            break;
        case sf::Keyboard::S:
            player[0].processInput("down", keyPressed);
            break;
        case sf::Keyboard::A:
            player[0].processInput("left", keyPressed);
            break;
        case sf::Keyboard::D:
            player[0].processInput("right", keyPressed);
            break;
        case sf::Keyboard::Space:
            player[0].processInput("jump", keyPressed);
            break;
        case sf::Keyboard::Return:
            player[0].processInput("item", keyPressed);
            break;
        case sf::Keyboard::R:
            player[0].setPosition(10.0, 10.0);
/*
        case sf::Keyboard::T:
            player[1].processInput("up", keyPressed);
            break;
        case sf::Keyboard::Y:
            player[1].processInput("down", keyPressed);
            break;
        case sf::Keyboard::U:
            player[1].processInput("left", keyPressed);
            break;
        case sf::Keyboard::I:
            player[1].processInput("right", keyPressed);
            break;
        case sf::Keyboard::V:
            player[1].processInput("jump", keyPressed);
            break;
        case sf::Keyboard::Z:
            player[1].processInput("item", keyPressed);
            break;*/
        default:
            break;
    }
}

void World::unload()
{
    for (vector<sf::Music*>::iterator it = score.begin(); score.end() != it; it++)
        (*it)->stop();
    score.clear();
    items.clear();
    blocks.clear();
    background.clear();
}

void World::updateScene(int delta_t)
{
    for (int i = 0; i < 2; i++) {
        player[i].accel(delta_t, GRAVITY);
        player[i].move(delta_t);
    }
    for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++) {
        int col = it->collide(&player[0]);
    }
}

