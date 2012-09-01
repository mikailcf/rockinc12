
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
    char filename[MAX_NAME];
    fscanf(file, "%s\n", filename);
    bg_img.loadFromFile(RES(string(filename)));
}

void World::loadSoundtrack(FILE* file)
{
    char filename[MAX_NAME];
    fscanf(file, "%s\n", filename);
    if (!sound.openFromFile(RES(string(filename))))
        exit(EXIT_FAILURE);
    sound.setLoop(true);
    sound.setVolume(100);
    sound.play();
}

void World::loadBlocks(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f", &ox, &oy, &sx, &sy);
        blocks.push_back(Block(sf::Vector2f(ox, oy), sf::Vector2f(sx, sy), NULL, NULL, false));
    }
}

void World::loadItems(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f", &ox, &oy, &sx, &sy);
        items.push_back(Item(ox, oy, sx, sy));
    }
}

void World::loadPlayers(FILE* file)
{
    for (int i = 0; i < 2; i++) {
        float x, y;
        fscanf(file, "%f %f", &x, &y);
        player[i] = Player(x, y, RES("sheet.png"));
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
    sf::Texture bg_tex;
    bg_tex.loadFromImage(bg_img);
    bg_sprite.setTexture(bg_tex);
    window.draw(bg_sprite);
}

void World::draw(sf::RenderWindow &window, int delta_t)
{
    for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++) {
            
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
        case sf::Keyboard::K:
            player[0].processInput("jump", keyPressed);
            break;
        case sf::Keyboard::L:
            player[0].processInput("item", keyPressed);
            break;
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
            break;
        default:
            break;
    }
}

void World::unload()
{
    sound.stop();
}

void World::updateScene(int delta_t){
    for(int i = 0; i < 2; i++) {
        player[i].accel(delta_t, GRAVITY);
    }
}

