//
//  MainPage.cpp
//  DinoGame
//
//  Created by howard on 2022/12/15.
//  Copyright © 2022 Dafu. All rights reserved.
//

#include "MainPage.hpp"


// Constructors Destructors
MainPage::MainPage()
{
    this -> initVariables();
    this -> initWindow();
    this -> initObjects();
}
MainPage::~MainPage()
{
    delete this->window;
}


// Accessors
const bool MainPage::running() const
{
    return this -> window -> isOpen();
}

// Private functions
void MainPage::initVariables()
{

}
void MainPage::initWindow()
{
    this -> videoMode.height = 1500;
    this -> videoMode.width = 1000;
    this -> window = new sf::RenderWindow(this->videoMode, "Like A Dino!");
    this -> window->setFramerateLimit(60);
}
void MainPage::initObjects()
{
    // load font
    if (!font.loadFromFile("/Users/howard/NTUIM_2022PD-final_project-Like_A_Dino/DinoGame/Resources/Fonts/ComicGeckoPro.otf")) {
        return EXIT_FAILURE;
    }
    // load photos
    if(!this->dino_texture.loadFromFile("/Users/howard/NTUIM_2022PD-final_project-Like_A_Dino/DinoGame/Resources/Images/DinoYellow.png"))
    {
        return EXIT_FAILURE;
    }
    // set background color
    this->background_color = sf::Color(255, 204, 153, 255);
    this->like_a_dino.setString("Like A Dino!");
    // set text
    
    // set mouseposition
    this->MousePosWindow = sf::Mouse::getPosition(*this -> window);
    
    // set texture
    this->dino.setTexture(this->dino_texture);
    this->dino.setPosition(450, 500);
    this->like_a_dino.setPosition(200, 200);
    this->like_a_dino.setFont(font);
    this->like_a_dino.setFillColor(sf::Color::Black);
    this->like_a_dino.setCharacterSize(107);
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


void MainPage::update()
{
    this -> pollEvents();

    // get mouse loc on screen
    std::cout << sf::Mouse::getPosition(*this -> window).x << ' ' << sf::Mouse::getPosition(*this -> window).y << std::endl;
}
void MainPage::render()
{
    this->window->clear(background_color);
    // draw game objects
    this->window->draw(dino);
    this->window->draw(like_a_dino);
    this->window->display();
}
