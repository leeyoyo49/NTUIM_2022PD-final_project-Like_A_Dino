//
//  MainPage.cpp
//  DinoGame
//
//  Created by howard on 2022/12/15.
//  Copyright © 2022 Dafu. All rights reserved.
//

#include "MainPage.hpp"


// Constructors Destructors
MainPage::MainPage(sf::RenderWindow* window, std::string skin_name)
{
    
    this -> skin_name = skin_name;
    this -> window = window;
    this -> initObjects();
}

// Accessors
const bool MainPage::running() const
{
    return this -> window -> isOpen();
}

// Private functions
void MainPage::initObjects()
{
    // load font
    if (!font.loadFromFile(resourcePath()+"Resources/Fonts/ComicGeckoPro.otf")) {
        return EXIT_FAILURE;
    }
    // load photos
    if(!this->dino_texture.loadFromFile(resourcePath()+"Resources/Images/"+this -> skin_name+".png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->info_texture.loadFromFile(resourcePath()+"Resources/Images/Information.png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->startbutton_texture.loadFromFile(resourcePath()+"Resources/Images/StartBrown.png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->scoreboard_texture.loadFromFile(resourcePath()+"Resources/Images/scoreboard.png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->skin_texture.loadFromFile(resourcePath()+"Resources/Images/skin.png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->music_texture.loadFromFile(resourcePath()+"Resources/Images/Music.png"))
    {
        return EXIT_FAILURE;
    }
    // set background color
    this->background_color = sf::Color(255, 204, 153, 255);
    this->like_a_dino.setString("Like A Dino!");
    this->song_name.setString("Theme Ku");
    // set text
    
    // set mouseposition
    this->MousePosWindow = sf::Mouse::getPosition(*this -> window);
    
    // set texture
    this->like_a_dino.setPosition(200, 200);
    this->like_a_dino.setFont(font);
    this->like_a_dino.setFillColor(sf::Color::Black);
    this->like_a_dino.setCharacterSize(107);
    this->song_name.setPosition(130, 560);
    this->song_name.setFont(font);
    this->song_name.setFillColor(sf::Color::Black);
    this->song_name.setCharacterSize(50);
    this->info.setTexture(this->info_texture);
    this->info.setPosition(50, 40);
    this->scoreboard.setTexture(this->scoreboard_texture);
    this->scoreboard.setPosition(60, 400);
    this->dino.setTexture(this->dino_texture);
    this->dino.setPosition(540, 450);
    this->startbutton.setTexture(this->startbutton_texture);
    this->startbutton.setPosition(300, 1140);
    this->skin.setTexture(this->skin_texture);
    this->skin.setPosition(50, 1340);
    this->music.setTexture(this->music_texture);
    this->music.setPosition(820, 1340);
}


// Functions
void MainPage::pollEvents()
{
    while(this -> window -> pollEvent(this->event))
    {
        switch (this -> event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
            default:
                break;
        }
    }
}


void MainPage::update(int& current_state, std::string skin_name)
{
    if(skin_name != this -> skin_name)
    {
        this -> skin_name = skin_name;
        if(!this->dino_texture.loadFromFile(resourcePath()+"Resources/Images/"+this -> skin_name+".png"))
        {
            return EXIT_FAILURE;
        }
        this->dino.setTexture(this->dino_texture);
    }
    this -> pollEvents();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*this -> window).x > 312 && sf::Mouse::getPosition(*this -> window).x < 718 && sf::Mouse::getPosition(*this -> window).y > 1150 && sf::Mouse::getPosition(*this -> window).y < 1340)
    {
        current_state = 2;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*this -> window).x > 62 && sf::Mouse::getPosition(*this -> window).x < 168 && sf::Mouse::getPosition(*this -> window).y > 1346 && sf::Mouse::getPosition(*this -> window).y < 1448)
    {
        current_state = 3;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*this -> window).x > 830 && sf::Mouse::getPosition(*this -> window).x < 932 && sf::Mouse::getPosition(*this -> window).y > 1350 && sf::Mouse::getPosition(*this -> window).y < 1446)
    {
        current_state = 4;
    }
    // get mouse loc on screen
    //std::cout << sf::Mouse::getPosition(*this -> window).x << ' ' << sf::Mouse::getPosition(*this -> window).y << std::endl;
}
void MainPage::render()
{
    this->window->clear(background_color);
    // draw game objects
    this->window->draw(dino);
    this->window->draw(info);
    this->window->draw(scoreboard);
    this->window->draw(startbutton);
    this->window->draw(skin);
    this->window->draw(music);
    this->window->draw(like_a_dino);
    this->window->draw(song_name);
    this->window->display();
}
