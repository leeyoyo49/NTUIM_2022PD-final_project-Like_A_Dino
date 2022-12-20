//
//  InfoPage.cpp
//  DinoGame
//
//  Created by howard on 2022/12/18.
//  Copyright © 2022 Dafu. All rights reserved.
//

#include "InfoPage.hpp"


// Constructors Destructors
InfoPage::InfoPage(sf::RenderWindow* window, int& current_state) : current_state(current_state)
{
    this -> current_state = current_state;
    this -> window = window;
    this -> initObjects();
}

// Accessors
const bool InfoPage::running() const
{
    return this -> window -> isOpen();
}

// Private functions
void InfoPage::initObjects()
{
    // load font
    if (!font.loadFromFile(resourcePath()+"Resources/Fonts/ComicGeckoPro.otf")) {
        throw("ERROR::EXIT_FAILURE");
    }
    // load photos
    if(!this->team_texture.loadFromFile(resourcePath()+"Resources/Images/picture.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->names_texture.loadFromFile(resourcePath()+"Resources/Images/namesOr.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->info_texture.loadFromFile(resourcePath()+"Resources/Images/infoOr.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->idol_texture.loadFromFile(resourcePath()+"Resources/Images/yoyoLee.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->home_texture.loadFromFile(resourcePath()+"Resources/Images/home.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    // set background color
    this->background_color = sf::Color(255, 204, 153, 255);
    // set text
    
    // set mouseposition
    this->MousePosWindow = sf::Mouse::getPosition(*this -> window);
    
    // set texture
    this->team.setTexture(this->team_texture);
    this->team.setPosition(550, 60);
    this->names.setTexture(this->names_texture);
    this->names.setPosition(50, 460);
    this->info.setTexture(this->info_texture);
    this->info.setPosition(50, 580);
    this->idol.setTexture(this->idol_texture);
    this->idol.setPosition(40, 60);
    this->home.setTexture(this->home_texture);
    this->home.setPosition(700, 1300);
}


// Functions
void InfoPage::pollEvents()
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


void InfoPage::update()
{
    this -> pollEvents();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*this -> window).x > 700 && sf::Mouse::getPosition(*this -> window).x < 820 && sf::Mouse::getPosition(*this -> window).y > 1306 && sf::Mouse::getPosition(*this -> window).y < 1412)
    {
        current_state = 1;
    }
    // get mouse loc on screen
    //std::cout << sf::Mouse::getPosition(*this -> window).x << ' ' << sf::Mouse::getPosition(*this -> window).y << std::endl;
}
void InfoPage::render()
{
    this->window->clear(background_color);
    // draw game objects
    this->window->draw(team);
    this->window->draw(names);
    this->window->draw(info);
    this->window->draw(idol);
    this->window->draw(home);
    this->window->display();
}

void InfoPage::runinfopage()
{
    while (this -> running() && (current_state == 5)) {
        this -> update();
        this -> render();
    }
}
