#include "SkinPage.hpp"
#include "MusicPage.hpp"
#include "MainPage.hpp"
#include "Game.hpp"


int main(int, char const**)
{
    // 全域變數
    int current_state = 1;
    bool game_still_running = true;
    string skin_name = "Yoyo";
    string music_name = "When-I-Was-A-Boy";
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000,1500), "Like A Dino!");
    window -> setFramerateLimit(120);
    
    // 視窗們
    MainPage mainpage(window, skin_name);
    MusicPage musicpage(window, music_name);
    
    // Start the game loop
    while (game_still_running)
    {
        
        switch (current_state) {
            case 1:{
                mainpage.update(current_state, skin_name);
                mainpage.render();
                game_still_running = mainpage.running();
                break;
            }
            case 2:{
                Game game(window, current_state, skin_name, music_name);
                game.gamerun();
                break;
            }
            case 3:{
                SkinPage skinpage(window, current_state, skin_name);
                skinpage.run_skinpage();
                break;
            }
            case 4:{
                musicpage.update(current_state);
                musicpage.render();
                game_still_running = musicpage.running();
                break;
            }
//
//            default:
//                break;
        }
    }
    delete window;
    return EXIT_SUCCESS;
}
