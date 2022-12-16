//
//  Game.hpp
//  DinoGame
//
//  Created by Dafu on 2022/12/13.
//  Copyright © 2022 Dafu. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <queue>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"

#endif /* Game_hpp */

class Game
{
private:
    // Variables
    // window
    sf::Color background_color;
    sf::VideoMode videoMode;
    sf::Event ev;
    
    // Game objects
    sf::Font font;
    
    int scorenum;
    sf::Text score;
    int lifenum;
    sf::Text lifenum_text;
    int speednum;
    sf::Text speed;
    int temponum;
    sf::Text tempo;
    double neckspeed;
    
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
    sf::Texture life_texture;
    sf::Sprite life;
    
    std::vector<sf::Sprite> Dinoneck_vector;
    std::vector<int> song_sheet;
    int song_pos;
    double curr_song_time;
    clock_t song_start_time;
    double last_frame_time;
    double time_since_last_update;
    
    sf::SoundBuffer song_buffer;
    sf::Sound song;
    
    sf::Vector2i MousePosWindow;
    
    // Private functions
    void initObjects();

    

public:
    sf::RenderWindow* window;
    // Constructors, Destructors
    Game(sf::RenderWindow* window);
//    ~Game();
    
    // Accessors
    const bool running() const;
    
    // Setter
    void change_song(std::string song_name);
    void change_skin(std::string skin_name);
    
    // Functions
    void updateMousePositions();
    void pollEvents();
    void update_time();
    void update_head();
    void update_neck();
    void move_neck();
    void update();
    void render();
};
