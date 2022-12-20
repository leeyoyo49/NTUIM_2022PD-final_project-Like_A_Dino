//
//  MainPage.cpp
//  DinoGame
//
//  Created by howard on 2022/12/15.
//  Copyright © 2022 Dafu. All rights reserved.
//

#include "MainPage.hpp"


// Constructors Destructors
MainPage::MainPage(sf::RenderWindow* window, int& current_state, std::string skin_name, std::string music_name) : current_state(current_state)
{
    this -> music_name = music_name;
    this -> current_state = current_state;
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
        throw("ERROR::EXIT_FAILURE");
    }
    // load photos
    if(!this->dino_texture.loadFromFile(resourcePath()+"Resources/Images/"+this -> skin_name+".png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->info_texture.loadFromFile(resourcePath()+"Resources/Images/Information.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->startbutton_texture.loadFromFile(resourcePath()+"Resources/Images/StartBrown.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->scoreboard_texture.loadFromFile(resourcePath()+"Resources/Images/scoreboard.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->skin_texture.loadFromFile(resourcePath()+"Resources/Images/skin.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    if(!this->music_texture.loadFromFile(resourcePath()+"Resources/Images/Music.png"))
    {
        throw("ERROR::EXIT_FAILURE");
    }
    // set background color
    this->background_color = sf::Color(255, 204, 153, 255);
    this->like_a_dino.setString("Like A Dino!");
    this->song_name.setString(this->music_name);
    this->character_name.setString(this->skin_name);
    // set text
    fstream in;
    vector <string> scorearr;
    in.open(resourcePath()+"Resources/score.txt");
    string tempnum;
    if(in)
    {
        for(int i = 0; i < 5; i ++)
        {
            in >> tempnum;
            cout << tempnum << ' ';
            scorearr.push_back(tempnum);
        }
    }
    in.close();
    this->scoreone.setString((scorearr[0]));
    this->scoretwo.setString((scorearr[1]));
    this->scorethree.setString((scorearr[2]));
    this->scorefour.setString((scorearr[3]));
    this->scorefive.setString((scorearr[4]));
    
    // set mouseposition
    this->MousePosWindow = sf::Mouse::getPosition(*this -> window);
    
    // set texture
    this->like_a_dino.setPosition(200, 200);
    this->like_a_dino.setFont(font);
    this->like_a_dino.setFillColor(sf::Color::Black);
    this->like_a_dino.setCharacterSize(107);
    this->song_name.setPosition(140, 580);
    this->song_name.setFont(font);
    this->song_name.setFillColor(sf::Color::Black);
    this->song_name.setCharacterSize(30);
    this->scoreone.setPosition(180, 700);
    this->scoreone.setFont(font);
    this->scoreone.setFillColor(sf::Color::Black);
    this->scoreone.setCharacterSize(30);
    this->scoretwo.setPosition(180, 767);
    this->scoretwo.setFont(font);
    this->scoretwo.setFillColor(sf::Color::Black);
    this->scoretwo.setCharacterSize(30);
    this->scorethree.setPosition(180, 835);
    this->scorethree.setFont(font);
    this->scorethree.setFillColor(sf::Color::Black);
    this->scorethree.setCharacterSize(30);
    this->scorefour.setPosition(180, 905);
    this->scorefour.setFont(font);
    this->scorefour.setFillColor(sf::Color::Black);
    this->scorefour.setCharacterSize(30);
    this->scorefive.setPosition(180, 980);
    this->scorefive.setFont(font);
    this->scorefive.setFillColor(sf::Color::Black);
    this->scorefive.setCharacterSize(30);
    this->character_name.setPosition(650, 1040);
    this->character_name.setFont(font);
    this->character_name.setFillColor(sf::Color::Black);
    this->character_name.setCharacterSize(60);
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*this -> window).x > 48 && sf::Mouse::getPosition(*this -> window).x < 162 && sf::Mouse::getPosition(*this -> window).y > 40 && sf::Mouse::getPosition(*this -> window).y < 140)
    {
        current_state = 5;
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
    this->window->draw(character_name);
    this->window->draw(scoreone);
    this->window->draw(scoretwo);
    this->window->draw(scorethree);
    this->window->draw(scorefour);
    this->window->draw(scorefive);
    this->window->display();
}

void MainPage::runmainpage()
{
    while (this -> running() && (current_state == 1)) {
        this -> update();
        this -> render();
    }
}
