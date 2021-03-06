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

void World::loadBoxes(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f", &ox, &oy, &sx, &sy);
        boxes.push_back(Box(sf::Vector2f(ox, oy), sf::Vector2f(sx, sy)));
    }
}

void World::loadBlocks(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        char filename[MAX_NAME];
        char animType[MAX_NAME]; //hori, vert, none
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f %s %s", &ox, &oy, &sx, &sy, animType, filename);
        printf( "%f %f %f %f %s %s\n", ox, oy, sx, sy, animType, filename);
        blocks.push_back(Block(sf::Vector2f(ox, oy), sf::Vector2f(sx, sy), animType, RES(string(filename))));
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

void World::loadCheckpoints(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f", &ox, &oy, &sx, &sy);
        checkpoints.push_back(Checkpoint(checkpoints.size(), Box(sf::Vector2f(ox, oy), sf::Vector2f(sx, sy)), false));
    }
}

void World::loadTraps(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        int frames;
        char filename[MAX_NAME];
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f %s %d", &ox, &oy, &sx, &sy, filename, &frames);
        traps.push_back(Trap(Box(sf::Vector2f(ox, oy), sf::Vector2f(sx, sy)), RES(string(filename)), frames));
    }
}

void World::loadTeleports(FILE* file)
{
    int n = 0;
    fscanf(file, "%d", &n);
    while (n--) {
        char filename[MAX_NAME];
        float ox, oy, sx, sy;
        fscanf(file, "%f %f %f %f %s", &ox, &oy, &sx, &sy, filename);
        teleports.push_back(Teleport(Box(sf::Vector2f(ox, oy), sf::Vector2f(sx, sy)), RES(string(filename))));
    }
}

void World::loadPlayers(FILE* file)
{
    for (int i = 0; i < 2; i++) {
        char filename[MAX_NAME];
        float x, y;
        fscanf(file, "%f %f %s", &x, &y, filename);
        player[i] = Player(x, y, RES(string(filename)), this);
        checkpoints.push_back(Checkpoint(checkpoints.size(), Box(sf::Vector2f(x, y), sf::Vector2f(20, 20)), true));
    }
}

void World::load(string filename)
{
    cout << "size"<< sf::Texture::getMaximumSize() << endl;
    FILE *level_file = fopen(filename.c_str(), "r");
    if (level_file == NULL)
        exit(EXIT_FAILURE);

    podeTerminar = false;
    loadBackground(level_file);
    loadSoundtrack(level_file);
    loadPlayers(level_file);
    loadItems(level_file);
    loadBlocks(level_file);
    loadBoxes(level_file);
    loadCheckpoints(level_file);
    loadTraps(level_file);
    loadTeleports(level_file);

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

    /*
    for (vector<sf::Texture>::iterator it = background.begin(); it != background.end(); it++) { 
        sf::Sprite sprite;
        sprite.setTexture(*it);
        window.draw(sprite);
    }
    */
}

void World::draw(sf::RenderWindow &window, int delta_t)
{
    for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++) {
        it->draw(&window);
    }
    for (vector<Box>::iterator it = boxes.begin(); it != boxes.end(); it++) {
        it->draw(&window);
    }
    for (vector<Item>::iterator it = items.begin(); it != items.end(); it++) {
        it->draw(&window);
    }
    for (vector<Teleport>::iterator it = teleports.begin(); it != teleports.end(); it++) {
        it->draw(&window);
    }
    for (vector<Trap>::iterator it = traps.begin(); it != traps.end(); it++) {
        it->animate(delta_t);
        it->draw(&window);
    }
    for (int i = 0; i < 2; i++) {
        player[i].animate(delta_t);
        player[i].draw(&window);    
    }
}

void World::processInput(sf::Keyboard::Key keyCode, bool keyPressed) {
    if (united) {
        for (int i = 0; i < 2; i++)
            player[i].stop();
    }
    else switch (keyCode) {
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
            printf("top 1 %f\n", player[0].top);
            if(player[0].item == NULL && keyPressed){
                printf("top 2 %f\n", player[0].top);
                // printf("nao tinha item\n");
                for (vector<Item>::iterator it = items.begin(); it != items.end(); it++){
                    printf("top 3 %f\n", player[0].top);
                    // printf("1");
                    if(player[0].collide_item(&(*it))){
                        printf("top 4 %f\n", player[0].top);
                        player[0].item = &(*it);
                        printf("top 5 %f\n", player[0].top);
                        // printf("tem um item aqui\n");
                        (*it).move(player[0].left - (*it).left + player[0].width, -20.0);
                        printf("top 6 %f\n", player[0].top);
                        (*it).picked = true;
                    }
                }
                // printf("\n");
            }
            // else player[0].processInput("item", keyPressed);
            break;
        case sf::Keyboard::R:
            // player[0].setPosition(10.0, 10.0);
            // Item *item = player[0].
            (player[0].item)->move(20.0, -5.0);
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

void World::jumping(int delta_t, int player_num){
    if(player[player_num].jumping == 1) player[player_num].jump(delta_t);
}

void World::unload()
{
    for (vector<sf::Music*>::iterator it = score.begin(); score.end() != it; it++)
        (*it)->stop();
    score.clear();
    items.clear();
    blocks.clear();
    boxes.clear();    
    background.clear();
    traps.clear();
    checkpoints.clear();
    teleports.clear();
}

void World::updateScene(int delta_t)
{
    for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++) {
        //(*it).move(0,-1);
        it->moveAnimate();
    }
    for (int i = 0; i < 2; i++) {
        player[i].accel(delta_t, GRAVITY);
        player[i].move(delta_t);

        for (vector<Item>::iterator it = items.begin(); it != items.end(); it++){
            if (!(it->picked)) {
                it->accel(delta_t, GRAVITY);
                it->move(delta_t);

                for (vector<Block>::iterator ito = blocks.begin(); ito != blocks.end(); ito++)
                    ito->collide(&(*it));
                for (vector<Box>::iterator ito = boxes.begin(); ito != boxes.end(); ito++)
                    ito->collide(&(*it));
            }

            // for (vector<Block>::iterator ito = blocks.begin(); ito != blocks.end(); ito++)
            //     ito->collide(&(*it));
            // for (vector<Box>::iterator ito = boxes.begin(); ito != boxes.end(); ito++)
            //     ito->collide(&(*it));
        }
        int collided = 0;
        for (vector<Block>::iterator it = blocks.begin(); it != blocks.end(); it++)
            collided += (*it).collide(&player[i]);
        for (vector<Box>::iterator it = boxes.begin(); it != boxes.end(); it++)
            collided += it->collide(&player[i]);
        if (collided) player[i].unstuck();

        for (vector<Trap>::iterator it = traps.begin(); it != traps.end(); it++)
            it->check(&player[i]);
        podeTerminar = true;
        for (vector<Checkpoint>::iterator it = checkpoints.begin(); it != checkpoints.end(); it++) {
            podeTerminar &= it->getVisited();
            it->check(&player[i]);
        }
        for (vector<Teleport>::iterator it = teleports.begin(); it != teleports.end(); it++) {
            it->check(&player[i]);
        }
    }
}

sf::Vector2f World::getCenter(int i)
{
    return sf::Vector2f(player[i].pos.x, player[i].pos.y);
}

bool World::switch_players()
{
    for (int i = 0; i < 2; i++) {
        if (player[i].teleporting < 2) return false;
        player[i].stop();   
    }
    swap(player[0].pos, player[1].pos);
    for (int i = 0; i < 2; i++) {
        player[i].teleporting = 0;
        for (vector<Teleport>::iterator it = teleports.begin(); it != teleports.end(); it++)
            it->leave();
    }
    return true;
}

