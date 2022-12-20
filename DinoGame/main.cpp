#include "SkinPage.hpp"
#include "MusicPage.hpp"
#include "MainPage.hpp"
#include "Game.hpp"
#include "InfoPage.hpp"


using namespace std;

int main(int, char const**)
{
    // 全域變數
    
    int current_state = 1;
    bool game_still_running = true;
    string skin_name = "Yoyo";
    string music_name = "When-I-Was-A-Boy";
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000,1500), "Like A Dino!");
    window -> setFramerateLimit(120);
    
    // Start the game loop
    while (game_still_running)
    {
        switch (current_state) {
            case 1:{
                MainPage mainpage(window, current_state, skin_name, music_name);
                mainpage.runmainpage();
                game_still_running = mainpage.running();
                break;
            }
            case 2:{
                Game game(window, current_state, skin_name, music_name);
                game.gamerun();
                game_still_running = game.running();
                break;
            }
            case 3:{
                SkinPage skinpage(window, current_state, skin_name);
                skinpage.run_skinpage();
                game_still_running = skinpage.running();
                current_state = 1;
                break;
            }
            case 4:{
                MusicPage musicpage(window,current_state, music_name);
                musicpage.run_musicpage();
                game_still_running = musicpage.running();
                current_state = 1;
                break;
            }
            case 5:{
                InfoPage infopage(window,current_state);
                infopage.runinfopage();
                game_still_running = infopage.running();
                current_state = 1;
                break;
            }
            default:
                break;
        }
    }
    delete window;
    return EXIT_SUCCESS;
}
