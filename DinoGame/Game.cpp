//
//  Game.cpp
//  DinoGame
//
//  Created by Dafu on 2022/12/13.
//  Copyright © 2022 Dafu. All rights reserved.
//

#include "Game.hpp"


// Constructors Destructors
Game::Game()
{
    this -> initVariables();
    this -> initWindow();
    this -> initObjects();
}
Game::~Game()
{
    delete this->window;
}


// Accessors
const bool Game::running() const
{
    return this -> window -> isOpen();
}

// Setter
void Game::change_song(std::string song_name)
{
    if(!this -> song_buffer.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/"+song_name+".wav"))
    {
        return EXIT_FAILURE;
    }
    this -> song.setBuffer(song_buffer);
    
    // add find song theet
}
void Game::change_skin(std::string skin_name)
{
    if (!this -> dinohead_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/"+skin_name+"Head.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dinohead.setTexture(this -> dinohead_texture);
    if (!this -> dinoneck_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/"+skin_name+"Neck.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dinoneck.setTexture(this -> dinoneck_texture);
    if (!this -> dinobody_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/"+skin_name+"Body.png"))
    {
        return EXIT_FAILURE;
    }
}

// Private functions
void Game::initVariables()
{
    this -> window = nullptr;

}
void Game::initWindow()
{
    this -> videoMode.height = 1500;
    this -> videoMode.width = 1000;
    this -> window = new sf::RenderWindow(this->videoMode, "Like A Dino!");
    this -> window->setFramerateLimit(60);
}
void Game::initObjects()
{
    // load font
    if (!font.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Fonts/ComicGeckoPro.otf")) {
        return EXIT_FAILURE;
    }
    
    // set background color
    this -> background_color = sf::Color(255, 204, 153);
    
    // set text
    this -> scorenum = 0;
    this -> score.setString("Score:"+std::to_string(scorenum));
    this -> score.setFillColor(sf::Color::Black);
    this -> score.setFont(font);
    this -> score.setCharacterSize(46);
    this -> score.setPosition(40, 40);
    this -> lifenum = 2;
    this -> life.setString("X"+std::to_string(lifenum));
    this -> life.setFillColor(sf::Color::Black);
    this -> life.setFont(font);
    this -> life.setCharacterSize(46);
    this -> life.setPosition(900, 40);
    this -> speednum = 1;
    this -> speed.setString("Speed X"+std::to_string(speednum));
    this -> speed.setFillColor(sf::Color::Black);
    this -> speed.setFont(font);
    this -> speed.setCharacterSize(46);
    this -> speed.setPosition(760, 1350);
    this -> temponum = 120;
    this -> tempo.setString("Tempo:"+std::to_string(temponum));
    this -> tempo.setFillColor(sf::Color::Black);
    this -> tempo.setFont(font);
    this -> tempo.setCharacterSize(46);
    this -> tempo.setPosition(760, 1400);
    this -> gamestart.setString("Game Start!");
    this -> gamestart.setFillColor(sf::Color::Black);
    this -> gamestart.setFont(font);
    this -> gamestart.setCharacterSize(46);
    this -> gamestart.setPosition(0, 750);
    
    // set mouseposition
    this -> MousePosWindow = sf::Mouse::getPosition(*this->window);
    
    // set texture
    if (!this -> pausebutton_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/Stop.png"))
    {
        return EXIT_FAILURE;
    }
    this -> pausebutton.setTexture(this -> pausebutton_texture);
    this -> pausebutton.setPosition(50, 1350);
    if (!this -> dinohead_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/DinoYellowHead.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dinohead.setTexture(this -> dinohead_texture);
    if (!this -> dinoneck_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/dinoYellowNeck.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dinoheadpos.x = 200;
    this -> dinoheadpos.y = 1147.5;
    this -> dinohead.setPosition(dinoheadpos);
    this -> dinoneck.setTexture(this -> dinoneck_texture);
    if (!this -> dinobody_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/DinoYellowBody.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dinobody.setTexture(this -> dinobody_texture);
    if (!this -> dottedline_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/dottedline.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dottedline.setTexture(this -> dottedline_texture);
    this -> dottedline.setPosition(200, 900);
    
    // set music
    if(!this -> song_buffer.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Songs/When-I-Was-A-Boy.wav"))
    {
        return EXIT_FAILURE;
    }
    song.setBuffer(song_buffer);
    
    // clear dinoneckvector
    this -> Dinoneck_vector.clear();
    
    // load music sheet
    
}


// Functions
void Game::pollEvents()
{
    while(this -> window -> pollEvent(this->ev))
    {
        switch (this -> ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(ev.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
            default:
                break;
        }
    }
}

void Game::updateMousePositions()
{
    this -> MousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::update()
{
    this -> pollEvents();
    this -> updateMousePositions();
    // head follow cursor
    if(this->MousePosWindow.x < 200)
    {
        this -> dinoheadpos.x = 200;
    }
    else if(this->MousePosWindow.x > 800-125)
    {
        this -> dinoheadpos.x = 800-125;
    }
    else
    {
        dinoheadpos.x = MousePosWindow.x;
    }
    dinohead.setPosition(dinoheadpos);
    
    // get mouse loc on screen
    std::cout << sf::Mouse::getPosition(*this -> window).x << ' ' << sf::Mouse::getPosition(*this -> window).y << std::endl;
}
void Game::render()
{
    this -> window -> clear(background_color);

    // draw game objects
    this -> window -> draw(score);
    this -> window -> draw(life);
    this -> window -> draw(speed);
    this -> window -> draw(tempo);
    this -> window -> draw(pausebutton);
    this -> window -> draw(dottedline);

    this -> dinoneck.setPosition(220, 700);
    this -> window -> draw(dinoneck);
//    this -> window -> draw(dinobody);
    this -> window -> draw(dinohead);

    this -> window -> display();
}
