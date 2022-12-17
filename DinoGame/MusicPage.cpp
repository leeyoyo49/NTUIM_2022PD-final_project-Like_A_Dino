#include "MusicPage.hpp"
#include "ResourcePath.hpp"

// Constructors Destructors
MusicPage::MusicPage(sf::RenderWindow* window, int& current_state, std::string& curr_music) : curr_music(curr_music)
{
    this->window = window;
    this -> curr_state = current_state;
    current_state = 1;
    this->iniNames(names, musicURL);
    this->initVariables();
    this->initObjects();
}

//MusicPage::~MusicPage()
//{
//    delete this->window;
//}

// Accessors
const bool MusicPage::running() const
{
    return this->window->isOpen();
}

// Private functions
void MusicPage::initVariables()
{
    index = 0;
}

void MusicPage::initObjects()
{
    // load font
    if (!font.loadFromFile(resourcePath()+"Resources/Fonts/ComicGeckoPro.otf"))
    {
        throw("ERROR::COULD NOT FIND LOAD FONT");
    }

    // set background color
    this->background_color = sf::Color(255, 204, 153);

    // set texture
    if (!this->leftbutton_texture.loadFromFile(resourcePath()+"Resources/Images/left.png"))
        throw("ERROR::EXIT_FAILURE");
    this->leftbutton.setTexture(this->leftbutton_texture);
    this->leftbutton.setPosition(50, 750);
    sf::IntRect leftTmp(leftbutton.getPosition().x, leftbutton.getPosition().y,
        leftbutton.getGlobalBounds().width, leftbutton.getGlobalBounds().height);
    this->leftbuttonRect = leftTmp;

    if (!this->rightbutton_texture.loadFromFile(resourcePath()+"Resources/Images/right.png"))
        throw("ERROR::EXIT_FAILURE");
    this->rightbutton.setTexture(this->rightbutton_texture);
    this->rightbutton.setPosition(850, 750);
    sf::IntRect rightTmp(rightbutton.getPosition().x, rightbutton.getPosition().y,
        rightbutton.getGlobalBounds().width, rightbutton.getGlobalBounds().height);
    this->rightbuttonRect = rightTmp;

    this->returnbutton.setString("OK!");
    this->returnbutton.setFillColor(sf::Color::Black);
    this->returnbutton.setFont(font);
    this->returnbutton.setCharacterSize(128);
    this->returnbutton.setPosition(400, 250);
    sf::IntRect returnTmp(returnbutton.getPosition().x, returnbutton.getPosition().y,
        returnbutton.getGlobalBounds().width, returnbutton.getGlobalBounds().height);
    this->returnbuttonRect = returnTmp;

    if (!this->cover_texture[index].loadFromFile(resourcePath()+"Resources/Images/"+musicURL[0]+".png"))
        throw("ERROR::EXIT_FAILURE");
    this->cover[index].setTexture(this->cover_texture[index]);
    this->cover[index].setPosition(250, 500);
    
    // set text
    this->musicname.setString(names[index]);
    this->musicname.setFillColor(sf::Color::Black);
    this->musicname.setFont(font);
    this->musicname.setCharacterSize(64);
    this->musicname.setPosition(cover[0].getPosition().x + cover[0].getGlobalBounds().width / 2
                                - musicname.getGlobalBounds().width / 2, 1200);
    // set music
    if (!this->music.openFromFile(resourcePath()+"Resources/Songs/" + curr_music + ".wav"))
        throw("ERROR::EXIT_FAILURE");
    music.play();
}

void MusicPage::iniNames(std::string* names, std::string* musicURL)
{
    names[0] = "When I Was A Boy";
    names[1] = "Vivaldi Autumn";
    names[2] = "LaLa Land";
    musicURL[0] = "When-I-Was-A-Boy";
    musicURL[1] = "vivaldi_autumn";
    musicURL[2] = "lalaland";
    
}

// Functions
void MusicPage::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        default:
            break;
        }
    }
}

void MusicPage::update()
{
    this->pollEvents();
    if (ifLeftPressed(sf::Mouse::getPosition(*this->window))) {
        sf::Time cur = time.getElapsedTime();
        if (cur.asSeconds() > 0.15) {
            index--;
            if (index < 0)
                index = MUSIC_NUM - 1;
            updateMusic();
            time.restart();
        }
    }
    else if (ifRightPressed(sf::Mouse::getPosition(*this->window))) {
        sf::Time cur = time.getElapsedTime();
        if (cur.asSeconds() > 0.15) {
            index++;
            if (index == MUSIC_NUM)
                index = 0;
            updateMusic();
            time.restart();
        }
    }
    else if (ifReturnPressed(sf::Mouse::getPosition(*this->window))) {
        // change music for every states
        this->curr_state = 1;
    }

    this->updateMusicname();
    this->updateCover();
}

void MusicPage::render()
{
    this->window->clear(background_color);
    this->window->draw(leftbutton);
    this->window->draw(rightbutton);
    this->window->draw(returnbutton);
    // draw game objects
    this->window->draw(musicname);
    this->window->draw(cover[index]);


    this->window->display();
}

void MusicPage::run_musicpage()
{
    while (this->running())
    {
        update();
        render();
        if (this->curr_state != 4)
        {
            break;
        }
    }
}

void MusicPage::updateMusicname()
{
    this->curr_music = musicURL[index];
    this->musicname.setString(names[index]);
    this->musicname.setPosition(cover[index].getPosition().x + cover[index].getGlobalBounds().width / 2
                                - musicname.getGlobalBounds().width / 2, 1200);}

void MusicPage::updateMusic()
{
    music.stop();
    music.openFromFile( resourcePath()+"Resources/Songs/" + musicURL[index] + ".wav");
    music.play();
}

void MusicPage::updateCover()
{
    this->cover_texture[index].loadFromFile(resourcePath()+"Resources/Images/"+musicURL[index]+".png");
    this->cover[index].setTexture(this->cover_texture[index]);
    this->cover[index].setPosition(250, 570);
}

const bool MusicPage::ifLeftPressed(sf::Vector2i mousePos) const
{
    if (leftbuttonRect.contains(sf::Mouse::getPosition(*this->window))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
    }
    return false;
}

const bool MusicPage::ifRightPressed(sf::Vector2i mousePos) const
{
    if (rightbuttonRect.contains(sf::Mouse::getPosition(*this->window))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
    }
    return false;
}

const bool MusicPage::ifReturnPressed(sf::Vector2i mousePos) const
{
    if (returnbuttonRect.contains(sf::Mouse::getPosition(*this->window))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
    }
    return false;
}
