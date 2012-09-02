
#include "defs.hpp"
#include "game.hpp"
#include "editor.hpp"

int main(int argc, const char * argv[])
{
    if (1 == 0) {
        Editor editor;
        editor.run();
        return EXIT_SUCCESS;
    }

    Game game;
    game.run();
	return EXIT_SUCCESS;
}
