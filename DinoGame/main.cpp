//#include "Game.hpp"
//#include "SkinPage.hpp"
#include "MainPage.hpp"
#include "Game.hpp"
int main(int, char const**)
{
    // Init Game engine 接著為1234
    MainPage mainpage;
    Game game;
//    SkinPage skinpage;
//    MusicPage musicpage;
    int current_state = 1;
    bool game_still_running = true;
    
    // Start the game loop
    while (game_still_running)
    {
        
        switch (current_state) {
            case 1:
                mainpage.update(current_state);
                mainpage.render();
                game_still_running = mainpage.running();
                break;
            case 2:
                game.update();
                game.render();
                game_still_running = game.running();
                break;
            case 3:
//                skinpage.update();
//                skinpage.render();
//                game_still_running = skinpage.running();
            case 4:
//                musicpage.update();
//                musicpage.render();
//                game_still_running = musicpage.running();
                
            default:
                break;
        }
    }
    return EXIT_SUCCESS;
}
