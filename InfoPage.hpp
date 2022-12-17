//
//  InfoPage.hpp
//  DinoGame
//
//  Created by howard on 2022/12/18.
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
#include <string>
#include "ResourcePath.hpp"

using namespace std;

class InfoPage
{
private:
    //Variables / Windows
    sf::VideoMode videoMode;
    sf::Event event;
    
    //Game objects
    sf::Texture home_texture;
    sf::Sprite home;
    
    sf::Texture team_texture;
    sf::Sprite team;
    
    sf::Texture names_texture;
    sf::Sprite names;
    
    sf::Texture info_texture;
    sf::Sprite info;
    
    sf::Texture idol_texture;
    sf::Sprite idol;
    
    sf::Font font;
    sf::Color background_color;
    sf::Vector2i MousePosWindow;
    
    // Private functions
    void initObjects();
public:
    //Constructors / Destructors
    sf::RenderWindow* window;
    InfoPage(sf::RenderWindow* window, int& current_state);
//    virtual ~MainPage();
    int& current_state;
    //Accessors
    const bool running() const;
    
    //Functions
    void pollEvents();
    void update();
    void render();
    void runinfopage();
};


#endif /* game_hpp */

