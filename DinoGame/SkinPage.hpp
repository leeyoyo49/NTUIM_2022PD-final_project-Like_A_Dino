#ifndef SkinPage_hpp
#define SkinPage_hpp

#include "ResourcePath.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

const int NUM = 7; // skin num
class SkinPage
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
    std::string names[NUM];
    std::string skinURL[NUM];
    sf::Sprite dinos[NUM];
    sf::Texture dinos_texture[NUM];
    sf::Text skinname;

    int index;
    sf::Texture leftbutton_texture;
    sf::Sprite leftbutton;
    sf::IntRect leftbuttonRect;
    sf::Texture rightbutton_texture;
    sf::Sprite rightbutton;
    sf::IntRect rightbuttonRect;
    sf::Text returnbutton;
    sf::IntRect returnbuttonRect;
    //sf::Sprite returnbutton;

    sf::SoundBuffer when_i_was_a_boy_buffer;
    sf::Sound when_i_was_a_boy_song;

    // Private functions
    void iniNames(std::string *names, std::string *skinURL);
    void initVariables();
    void initWindow();
    void initObjects();



public:
    // Constructors, Destructors
    SkinPage(sf::RenderWindow* window);
//    ~SkinPage();

    // Accessors
    sf::Clock time;
    const bool running() const;
    const bool ifLeftPressed(sf::Vector2i mousePos) const;
    const bool ifRightPressed(sf::Vector2i mousePos) const;
    const bool ifReturnPressed(sf::Vector2i mousePos) const;

    // Functions
    void pollEvents();
    void update();
    void updateSkinname();
    void updateDinos();
    void render();
};

#endif
