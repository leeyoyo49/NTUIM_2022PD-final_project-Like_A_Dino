//
//  Game.cpp
//  DinoGame
//
//  Created by Dafu on 2022/12/13.
//  Copyright © 2022 Dafu. All rights reserved.
//

// 碰到發出音效
// 找簡單的音樂
// 最高分更新db
// 脖子變長

#include "Game.hpp"

// Constructors Destructors
Game::Game(sf::RenderWindow* window, int& current_state, string skin_name, string music_name)
{
    this -> change_skin(skin_name);
    this -> change_song(music_name);
    current_state = 1;
    this -> window = window;
    this -> initObjects();
}
//Game::~Game()
//{
//    delete this->window;
//}

// Accessors
const bool Game::running() const
{
    return this -> window -> isOpen();
}

// Setter
void Game::change_song(std::string song_name)
{
    if(!this -> song_buffer.loadFromFile(resourcePath()+"Resources/Songs/"+song_name+".wav"))
    {
        return EXIT_FAILURE;
    }
    this -> song.setBuffer(song_buffer);
    
    // add find song theet
}
void Game::change_skin(std::string skin_name)
{
    if (!this -> dinohead_texture.loadFromFile(resourcePath()+"Resources/Images/"+skin_name+"Head.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dinohead.setTexture(this -> dinohead_texture);
    if (!this -> dinoneck_texture.loadFromFile(resourcePath()+"Resources/Images/"+skin_name+"Neck.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dinoneck.setTexture(this -> dinoneck_texture);
    if (!this -> dinobody_texture.loadFromFile(resourcePath()+"Resources/Images/"+skin_name+"Body.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dinoheadpos.x = 200;
    this -> dinoheadpos.y = 1100.5;
    this -> dinohead.setPosition(dinoheadpos);
}

// Private functions
void Game::initObjects()
{
    // read high scores
    fstream in;
    in.open(resourcePath()+"Resources/score.txt");
    int tempnum;
    if(in)
    {
        for(int i = 0; i < 5; i ++)
        {
            in >> tempnum;
            this -> scorearr.push_back(tempnum);
        }
    }
    in.close();
    
    this -> ss.precision(1);
    // load font
    if (!font.loadFromFile(resourcePath()+"Resources/Fonts/ComicGeckoPro.otf")) {
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
    this -> lifenum_text.setPosition(870, 45);
    this -> speednum = 1;
    this -> ss << fixed << speednum;
    string temp = ss.str();
    this -> ss.clear();
    this -> speed.setString("Speed X"+temp);
    this -> speed.setFillColor(sf::Color::Black);
    this -> speed.setFont(font);
    this -> speed.setCharacterSize(46);
    this -> speed.setPosition(740, 1350);
    this -> temponum = 120;
    this -> tempo.setString("Tempo:"+std::to_string(temponum));
    this -> tempo.setFillColor(sf::Color::Black);
    this -> tempo.setFont(font);
    this -> tempo.setCharacterSize(46);
    this -> tempo.setPosition(740, 1400);
    this -> gamestart.setString("Game Start!");
    this -> gamestart.setFillColor(sf::Color::Black);
    this -> gamestart.setFont(font);
    this -> gamestart.setCharacterSize(60);
    this -> gamestart.setPosition(0, 750);
    this -> speedup.setFont(font);
    this -> speedup.setString("Speed Up !");
    this -> speedup.setCharacterSize(50);
    this -> speedup.setPosition(300, 1000);
    this -> speedupnum = 0;
    // 1 sec 200 pixel
    this -> neckspeed = 36*(100.0/60.0)*(this -> temponum * this -> speednum);
    
    // set mouseposition
    this -> MousePosWindow = sf::Mouse::getPosition(*this -> window);
    
    // set texture
//    if (!this -> pausebutton_texture.loadFromFile(resourcePath()+"Resources/Images/Stop.png"))
//    {
//        return EXIT_FAILURE;
//    }
//    this -> pausebutton.setTexture(this -> pausebutton_texture);
//    this -> pausebutton.setPosition(50, 1350);
    
    if (!this -> dottedline_texture.loadFromFile(resourcePath()+"Resources/Images/dottedline.png"))
    {
        return EXIT_FAILURE;
    }
    this -> dottedline.setTexture(this -> dottedline_texture);
    this -> dottedline.setPosition(200, 900);
    
    if(!this -> life_texture.loadFromFile(resourcePath()+"Resources/Images/heart.png"))
    {
        return EXIT_FAILURE;
    }
    this -> life.setTexture(life_texture);
    this -> life.setPosition(777, 48);
    
    if(!this -> red_dino_neck_texture.loadFromFile(resourcePath()+"Resources/Images/dinoRedNeck.png"))
    {
        return EXIT_FAILURE;
    }
    this -> red_dino_neck.setTexture(red_dino_neck_texture);
    
    if(!this -> gameoverscreen_texture.loadFromFile(resourcePath()+"Resources/Images/over.png"))
    {
        return EXIT_FAILURE;
    }
    this -> gameoverscreen.setTexture(gameoverscreen_texture);
    this -> gameoverscreen.setPosition(164, 422);
    
    // set music
    if(!this -> song_buffer.loadFromFile(resourcePath()+"Resources/Songs/vivaldi_autumn.wav"))
    {
        return EXIT_FAILURE;
    }
    song.setBuffer(song_buffer);
    
    // clear dinoneckvector
    this -> Dinoneck_vector.clear();
    
    // load music sheet
    this -> song_pos = 0;
    std::ifstream file_in(resourcePath()+"Resources/SongSheet/When-I-Was-A-Boy.txt");
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
    if(this->MousePosWindow.x < 300)
    {
        this -> dinoheadpos.x = 200;
    }
    else if(this->MousePosWindow.x > 800-100)
    {
        this -> dinoheadpos.x = 800-200;
    }
    else
    {
        dinoheadpos.x = MousePosWindow.x - 100;
    }
    this -> dinohead.setPosition(dinoheadpos);
    
}
// for adding and deleting necks
void Game::update_neck()
{
    // 一小節4個八分音符 所以除以 8
    double time_segemnt = 60.0/(temponum*4);
    // 0.125 is the delay between the track
    if(this -> curr_song_time < (time_segemnt*(this->song_pos)))
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
        neck.move(0, move_dis);
    }
    // touch dino head delete neck
    // reach dotted line delete neck
    if(!Dinoneck_vector.empty())
    {
        int lowestneckx = Dinoneck_vector[0].getPosition().x, lowestnecky = Dinoneck_vector[0].getPosition().y;
        if(lowestnecky >= 1100)
        {
            lifenum--;
            red_dino_neck.setPosition(lowestneckx, 1110);
            if(lifenum < 0)
            {
                this -> game_end = 1;
                return;
            }
            lifenum_text.setString("X"+to_string(lifenum));
            Dinoneck_vector.erase(Dinoneck_vector.begin());
            this -> minus_life_animation();

        }
        else if((lowestnecky+100 >= dinohead.getPosition().y) && (lowestnecky < 1100))
        {
            if((lowestneckx >= dinohead.getPosition().x) && (lowestneckx <= (dinohead.getPosition().x + 200)))
            {
                scorenum += 10;
                score.setString("Score:"+to_string(scorenum));
                Dinoneck_vector.erase(Dinoneck_vector.begin());
                if((scorenum % 200 == 0) && (scorenum != 0))
                {
                    speednum += 0.2;
                    ss.str("");
                    this -> ss << fixed << speednum;
                    string temp = ss.str();
                    speed.setString("Speed X" + temp);
                    this -> speedupnum = 300;
                    this -> neckspeed = 36*(100.0/60.0)*(this -> temponum * this -> speednum);

                }
            }
            else if(((lowestneckx + 80) <= (dinohead.getPosition().x + 200)) && ((lowestneckx + 80) >= dinohead.getPosition().x))
            {
                scorenum += 10;
                score.setString("Score:"+to_string(scorenum));
                Dinoneck_vector.erase(Dinoneck_vector.begin());
                if((scorenum % 200 == 0) && (scorenum != 0))
                {
                    speednum += 0.2;
                    ss.str("");
                    this -> ss << fixed << speednum;
                    string temp = ss.str();
                    speed.setString("Speed X" + temp);
                    ss.clear();
                    this -> speedupnum = 300;
                    this -> neckspeed = 36*(100.0/60.0)*(this -> temponum * this -> speednum);

                }
            }
        }
    }
}
void Game::minus_life_animation()
{
    song.pause();
    this -> Dinoneck_vector.clear();
    sleep(0.5);
    sf::Text how_many_life_left("You have "+to_string(lifenum)+" life left", font, 70);
    how_many_life_left.setPosition(200, 700);
    int i = 300;
    while(i-- && this -> running())
    {
        this -> window -> clear(background_color);
        this -> window -> draw(score);
        this -> window -> draw(lifenum_text);
        this -> window -> draw(life);
        this -> window -> draw(speed);
        this -> window -> draw(tempo);
        this -> window -> draw(pausebutton);
        this -> window -> draw(dottedline);
        this -> window -> draw(red_dino_neck);
        this -> window -> draw(how_many_life_left);
        this -> window -> draw(life);
        this -> window -> draw(dinohead);
        this -> window -> display();
    }
    for(int j = 0; j < 6; j++)
    {
        this -> song_sheet[this -> song_pos - 1 + j] = 0;
    }
    song.play();
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
    if(this -> speedupnum != 0)
    {
        this -> window -> draw(speedup);
        this -> speedupnum--;
    }
    for(auto neck: this -> Dinoneck_vector)
    {
        this -> window -> draw(neck);
    }
    this -> window -> draw(dinohead);

    this -> window -> display();
}

void Game::gameStartpage()
{
    sleep(0.1);
    sf::Text gamestarttext("Let's Start !", this->font, 70);
    gamestarttext.setFillColor(sf::Color::Black);
    gamestarttext.setPosition(1001, 500);
    while((gamestarttext.getPosition().x > -470) && this -> running())
    {
        this -> window -> clear(background_color);
        this -> window -> draw(gamestarttext);
        gamestarttext.move(-5, 0);
        this -> window -> display();
    }
}

void Game::gameover()
{
    // update score
    this -> scorearr.push_back(this -> scorenum);
    sort(scorearr.begin(), scorearr.end());
    ofstream out;
    out.open(resourcePath()+"Resources/score.txt", ios::out | ios::trunc);
    for(int i = 0; i < 5; i ++)
    {
        out << this -> scorearr[i] << '\n';
    }
    
    // end animation
    song.pause();
    this -> Dinoneck_vector.clear();
    sleep(0.3);
    sf::Text how_many_life_left("Game Over QQ", font, 70);
    how_many_life_left.setPosition(200, 700);
    int cnt = 200;
    while(cnt -- && this -> running())
    {
        this -> window -> clear(background_color);
        this -> window -> draw(red_dino_neck);
        this -> window -> draw(life);
        this -> window -> draw(lifenum_text);
        this -> window -> draw(life);
        this -> window -> draw(speed);
        this -> window -> draw(tempo);
        this -> window -> draw(score);
        this -> window -> draw(pausebutton);
        this -> window -> draw(dottedline);
        this -> window -> draw(dinohead);
        this -> window -> draw(how_many_life_left);
        this -> window -> display();
    }
    while (this -> running() && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        this -> window -> clear(background_color);
        this -> window -> draw(gameoverscreen);
        this -> score.setString(to_string(scorenum));
        this -> score.setPosition(350, 844);
        this -> score.setCharacterSize(120);
        this -> window -> draw(score);
        this -> window -> display();
    }
}


int Game::gamerun()
{
    this -> gameStartpage();
    // play song & set song start time
    this -> song_start_time = clock();
    this -> curr_song_time = 0;
    this -> last_frame_time = clock();
    this -> song.play();
    sleep(0.1);
    while(!this -> game_end && this -> running())
    {
        this -> update();
        this -> render();
    }
    this -> gameover();
}


