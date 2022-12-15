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
    if(!this->info_texture.loadFromFile("/Users/howard/NTUIM_2022PD-final_project-Like_A_Dino/DinoGame/Resources/Images/Information.png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->startbutton_texture.loadFromFile("/Users/howard/NTUIM_2022PD-final_project-Like_A_Dino/DinoGame/Resources/Images/StartBrown.png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->scoreboard_texture.loadFromFile("/Users/howard/NTUIM_2022PD-final_project-Like_A_Dino/DinoGame/Resources/Images/scoreboard.png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->skin_texture.loadFromFile("/Users/howard/NTUIM_2022PD-final_project-Like_A_Dino/DinoGame/Resources/Images/skin.png"))
    {
        return EXIT_FAILURE;
    }
    if(!this->music_texture.loadFromFile("/Users/howard/NTUIM_2022PD-final_project-Like_A_Dino/DinoGame/Resources/Images/Music.png"))
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
    this->like_a_dino.setPosition(200, 200);
    this->like_a_dino.setFont(font);
    this->like_a_dino.setFillColor(sf::Color::Black);
    this->like_a_dino.setCharacterSize(107);
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
    this->window->draw(info);
    this->window->draw(scoreboard);
    this->window->draw(startbutton);
    this->window->draw(skin);
    this->window->draw(music);
    this->window->draw(like_a_dino);
    this->window->display();
}
