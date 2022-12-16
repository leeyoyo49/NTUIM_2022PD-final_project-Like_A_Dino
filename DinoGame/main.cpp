//#include "SkinPage.hpp"
#include "MainPage.hpp"
#include "Game.hpp"


int main(int, char const**)
{
    // Init Game engine 接著為1234
//    MainPage mainpage;
//    SkinPage skinpage;
//    MusicPage musicpage;
    int current_state = 1;
    bool game_still_running = true;
    
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000,1500), "Like A Dino!");
    window -> setFramerateLimit(120);
    Game game(window);
    MainPage mainpage(window);
//    SkinPage skinpage(window);
    
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
                game.gamerun(current_state);
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
    delete window;
    return EXIT_SUCCESS;
}
