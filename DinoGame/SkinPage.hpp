#ifndef SkinPage_hpp
#define SkinPage_hpp

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

const int NUM = 10;
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
    sf::Text skinname;
    sf::Texture leftbutton_texture;
    sf::Sprite leftbutton;
    sf::Texture rightbutton_texture;
    sf::Sprite rightbutton;
    sf::Texture returnbutton_texture;
    sf::Sprite returnbutton;
    sf::Sprite dinos[NUM];
    sf::Texture dinos_texture[NUM];

    sf::SoundBuffer when_i_was_a_boy_buffer;
    sf::Sound when_i_was_a_boy_song;

    // Private functions
    void initVariables();
    void initWindow();
    void initObjects();



public:
    // Constructors, Destructors
    SkinPage();
    ~SkinPage();

    // Accessors
    const bool running() const;

    // Functions
    void pollEvents();
    void update();
    void render();
};

#endif