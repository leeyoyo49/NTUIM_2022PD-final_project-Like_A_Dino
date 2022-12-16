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
    this -> window-> setFramerateLimit(120);
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
    this -> score.setCharacterSize(60);
    this -> score.setPosition(40, 40);
    this -> lifenum = 2;
    this -> lifenum_text.setString("X"+std::to_string(lifenum));
    this -> lifenum_text.setFillColor(sf::Color::Black);
    this -> lifenum_text.setFont(font);
    this -> lifenum_text.setCharacterSize(60);
    this -> lifenum_text.setPosition(880, 45);
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
    this -> gamestart.setCharacterSize(60);
    this -> gamestart.setPosition(0, 750);
    // 1 sec 200 pixel
    this -> neckspeed = 24*(100.0/60.0)*(this -> temponum * this -> speednum);
    
    // set mouseposition
    this -> MousePosWindow = sf::Mouse::getPosition(*this -> window);
    
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
    this -> dinoheadpos.x = 200;
    this -> dinoheadpos.y = 1147.5;
    this -> dinohead.setPosition(dinoheadpos);
    
    if (!this -> dinoneck_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Images/dinoYellowNeck.png"))
    {
        return EXIT_FAILURE;
    }
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
    
    if(!this -> life_texture.loadFromFile("/Users/yl/DinoGame/DinoGame/Resources/Images/heart.png"))
    {
        return EXIT_FAILURE;
    }
    this -> life.setTexture(life_texture);
    this -> life.setPosition(787, 48);
    
    // set music
    if(!this -> song_buffer.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/Songs/When-I-Was-A-Boy.wav"))
    {
        return EXIT_FAILURE;
    }
    song.setBuffer(song_buffer);
    
    // clear dinoneckvector
    this -> Dinoneck_vector.clear();
    
    // load music sheet
    this -> song_pos = 0;
    std::ifstream file_in("/Users/yl/DinoGame/DinoGame/Resources/SongSheet/When-I-Was-A-Boy.txt");
    if(!file_in) {
        return EXIT_FAILURE;
    }
    std::string line;
    std::getline(file_in, line);
    while(!line.empty())
    {
        song_sheet.push_back(int(line[0]-48));
        line.erase(0,1);
    }
    
    // play song & set song start time
    this -> song_start_time = clock();
    this -> curr_song_time = 0;
    this -> last_frame_time = clock();
    
    this -> song.play();
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
void Game::update_time()
{
    clock_t currtime = clock();
    this -> time_since_last_update = (double(currtime) - double(last_frame_time))/CLOCKS_PER_SEC;
    this -> curr_song_time = (double(currtime) - double(this -> song_start_time))/CLOCKS_PER_SEC;
    this -> last_frame_time = clock();
}

void Game::update_head()
{
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
    this -> dinohead.setPosition(dinoheadpos);
    
}
// for adding and deleting necks
void Game::update_neck()
{
    
    double time_segemnt = 60.0/temponum;
    if(this -> curr_song_time < time_segemnt*(this->song_pos))
    {
        return;
    }
    std::cout << curr_song_time << std::endl;
    // add new neck
    int added_note = this -> song_sheet[this -> song_pos];
    switch (added_note)
    {
        case 0:
            this -> song_pos ++;
            break;
        case 1:
            this -> dinoneck.setPosition(220, -100);
            this -> Dinoneck_vector.push_back(this -> dinoneck);
            this -> song_pos ++;
            break;
        case 2:
            this -> dinoneck.setPosition(460, -100);
            this -> Dinoneck_vector.push_back(this -> dinoneck);
            this -> song_pos ++;
            break;
        case 3:
            this -> dinoneck.setPosition(700, -100);
            this -> Dinoneck_vector.push_back(this -> dinoneck);
            this -> song_pos ++;
            break;
        default:
            break;
    }
}

// for updating neck movment
void Game::move_neck()
{
    
    // neck fall & del if hit dotted line
    for(auto &neck: this -> Dinoneck_vector)
    {
        double temponum = this -> temponum;
        double move_dis = ((this -> neckspeed)*(this->time_since_last_update));
//        std::cout << (((100)*(temponum)*(this->speednum))/60);
//        std::cout << " ";
//        std::cout << (this->time_since_last_update) << std::endl;
        neck.move(0, move_dis);
    }
    // reach dotted line delete neck
    if(!Dinoneck_vector.empty())
    {
        if(Dinoneck_vector[0].getPosition().y >= 1100)
        {
            Dinoneck_vector.erase(Dinoneck_vector.begin());
        }
    }
}

void Game::update()
{
    this -> pollEvents();
    this -> updateMousePositions();
    this -> update_head();
    this -> update_time();
    this -> update_neck();
    this -> move_neck();
    // get mouse loc on screen
//    std::cout << sf::Mouse::getPosition(*this -> window).x << ' ' << sf::Mouse::getPosition(*this -> window).y << std::endl;
}
void Game::render()
{
    this -> window -> clear(background_color);
    // draw game objects
    this -> window -> draw(score);
    this -> window -> draw(lifenum_text);
    this -> window -> draw(life);
    this -> window -> draw(speed);
    this -> window -> draw(tempo);
    this -> window -> draw(pausebutton);
    this -> window -> draw(dottedline);

    for(auto neck: this -> Dinoneck_vector)
    {
        this -> window -> draw(neck);
    }
    this -> window -> draw(dinohead);

    this -> window -> display();
}
