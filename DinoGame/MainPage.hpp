//
//  MainPage.hpp
//  DinoGame
//
//  Created by howard on 2022/12/15.
//  Copyright © 2022 Dafu. All rights reserved.
//

#pragma once

#ifndef MainPage_hpp
#define MainPage_hpp

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include "ResourcePath.hpp"

class MainPage
{
private:
    //Variables / Windows
    sf::VideoMode videoMode;
    sf::Event event;
    
    //Game objects
    sf::Text like_a_dino;
    sf::Text song_name;
    sf::Texture info_texture;
    sf::Sprite info;
    
    sf::Texture scoreboard_texture;
    sf::Sprite scoreboard;
    
    sf::Texture dino_texture;
    sf::Sprite dino;
    
    sf::Texture startbutton_texture;
    sf::Sprite startbutton;
    
    sf::Texture skin_texture;
    sf::Sprite skin;
    
    sf::Texture music_texture;
    sf::Sprite music;
    
    sf::Font font;
    sf::Color background_color;
    sf::Vector2i MousePosWindow;
    // Private functions
    void initObjects();
public:
    //Constructors / Destructors
    sf::RenderWindow* window;
    MainPage(sf::RenderWindow* window);
//    virtual ~MainPage();
    
    //Accessors
    const bool running() const;
    
    //Functions
    void pollEvents();
    void update(int& current_state);
    void render();
};


#endif /* game_hpp */

