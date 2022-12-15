//
//  Game.hpp
//  DinoGame
//
//  Created by Dafu on 2022/12/13.
//  Copyright © 2022 Dafu. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <filesystem>
#include <string>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#endif /* Game_hpp */

class Game
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
    
    int scorenum;
    sf::Text score;
    int lifenum;
    sf::Text life;
    int speednum;
    sf::Text speed;
    int temponum;
    sf::Text tempo;
    
    sf::Text gamestart;
    sf::Texture pausebutton_texture;
    sf::Sprite pausebutton;
    sf::Texture dinohead_texture;
    sf::Sprite dinohead;
    sf::Vector2f dinoheadpos;
    sf::Texture dinoneck_texture;
    sf::Sprite dinoneck;
    sf::Texture dinobody_texture;
    sf::Sprite dinobody;
    sf::Texture dottedline_texture;
    sf::Sprite dottedline;
    
    std::vector<sf::Sprite> Dinoneck_vector;
    std::vector<int> song_sheet;
    
    sf::SoundBuffer song_buffer;
    sf::Sound song;
    
    sf::Vector2i MousePosWindow;
    
    // Private functions
    void initVariables();
    void initWindow();
    void initObjects();

    

public:
    // Constructors, Destructors
    Game();
    ~Game();
    
    // Accessors
    const bool running() const;
    
    // Setter
    void change_song(std::string song_name);
    void change_skin(std::string skin_name);
    
    // Functions
    void updateMousePositions();
    void pollEvents();
    void update();
    void render();
};
