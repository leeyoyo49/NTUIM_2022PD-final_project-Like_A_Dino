#include "Game.hpp"

int main(int, char const**)
{
    // Init Game engine
    Game game;

    // Start the game loop
    while (game.running())
    {
        // update
        game.update();
        
        // render
        game.render();
        
    }

    return EXIT_SUCCESS;
}
