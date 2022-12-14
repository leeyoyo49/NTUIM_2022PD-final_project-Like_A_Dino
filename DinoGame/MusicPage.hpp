#ifndef MusicPage_hpp
#define MusicPage_hpp

#include <string>
#include <iostream>
#include<fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


using namespace std;

const int MUSIC_NUM = 3;
class MusicPage
{
private:
    // Variables
    // window
    sf::Color background_color;
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Game objects
    sf::Font font;
    std::string& curr_music;
    std::string names[MUSIC_NUM];
    std::string musicURL[MUSIC_NUM];
    sf::Sprite cover[MUSIC_NUM];
    sf::Texture cover_texture[MUSIC_NUM];
    sf::Text musicname;

    int curr_state;
    int index = 0;
    int SKIN_NUM;
    sf::Texture leftbutton_texture;
    sf::Sprite leftbutton;
    sf::IntRect leftbuttonRect;
    sf::Texture rightbutton_texture;
    sf::Sprite rightbutton;
    sf::IntRect rightbuttonRect;
    sf::Text returnbutton;
    sf::IntRect returnbuttonRect;

    sf::Music music;

    // Private functions
    void iniNames(std::string* names, std::string* musicURL);
    void initVariables();
    void initWindow();
    void initObjects();



public:
    // Constructors, Destructors
    MusicPage(sf::RenderWindow* window, int& current_state, std::string& music_name);
//~MusicPage()

    // Accessors
    sf::Clock time;
    const bool running() const;
    const bool ifLeftPressed(sf::Vector2i mousePos) const;
    const bool ifRightPressed(sf::Vector2i mousePos) const;
    const bool ifReturnPressed(sf::Vector2i mousePos) const;

    // Functions
    void pollEvents();
    void update();
    void updateMusicname();
    void updateMusic();
    void updateCover();
    void render();
    void run_musicpage();
};

#endif
