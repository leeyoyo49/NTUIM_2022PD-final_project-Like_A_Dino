#include "MusicPage.hpp"

// Constructors Destructors
MusicPage::MusicPage()
{
    this->iniNames(names, musicURL);
    this->initVariables();
    this->initWindow();
    this->initObjects();
}

MusicPage::~MusicPage()
{
    delete this->window;
}

// Accessors
const bool MusicPage::running() const
{
    return this->window->isOpen();
}

// Private functions
void MusicPage::initVariables()
{
    this->window = nullptr;
    index = 0;
}

void MusicPage::initWindow()
{
    this->videoMode.height = 1080;
    this->videoMode.width = 1920;
    this->window = new sf::RenderWindow(this->videoMode, "Like A Dino!");
    this->window->setFramerateLimit(60);
}

void MusicPage::initObjects()
{
    // load font
    if (!font.loadFromFile("/Users/User/source/repos/Dino/Dino/resources/ComicGeckoPro.otf")) {
        throw("ERROR::COULD NOT FIND LOAD FONT");
    }

    // set background color
    this->background_color = sf::Color(255, 204, 153);

    // set text
    this->musicname.setString(names[index]);
    this->musicname.setFillColor(sf::Color::Black);
    this->musicname.setFont(font);
    this->musicname.setCharacterSize(64);
    this->musicname.setPosition(730, 100);

    // set texture
    if (!this->leftbutton_texture.loadFromFile("/Users/User/source/repos/Dino/Dino/resources/left.png"))
        throw("ERROR::EXIT_FAILURE");
    this->leftbutton.setTexture(this->leftbutton_texture);
    this->leftbutton.setPosition(150, 530);
    sf::IntRect leftTmp(leftbutton.getPosition().x, leftbutton.getPosition().y,
        leftbutton.getGlobalBounds().width, leftbutton.getGlobalBounds().height);
    this->leftbuttonRect = leftTmp;

    if (!this->rightbutton_texture.loadFromFile("/Users/User/source/repos/Dino/Dino/resources/right.png"))
        throw("ERROR::EXIT_FAILURE");
    this->rightbutton.setTexture(this->rightbutton_texture);
    this->rightbutton.setPosition(1770, 530);
    sf::IntRect rightTmp(rightbutton.getPosition().x, rightbutton.getPosition().y,
        rightbutton.getGlobalBounds().width, rightbutton.getGlobalBounds().height);
    this->rightbuttonRect = rightTmp;

    this->returnbutton.setString("OK!");
    this->returnbutton.setFillColor(sf::Color::Black);
    this->returnbutton.setFont(font);
    this->returnbutton.setCharacterSize(108);
    this->returnbutton.setPosition(900, 850);
    sf::IntRect returnTmp(returnbutton.getPosition().x, returnbutton.getPosition().y,
        returnbutton.getGlobalBounds().width, returnbutton.getGlobalBounds().height);
    this->returnbuttonRect = returnTmp;

    /*if (!this->cover_texture[index].loadFromFile(coverURL[index]))
        throw("ERROR::EXIT_FAILURE");
    this->cover[index].setTexture(this->cover_texture[index]);
    this->cover[index].setPosition(780, 225);*/

    // set music
    if (!this->music.openFromFile(musicURL[0]))
        throw("ERROR::EXIT_FAILURE");
    music.play();
}

void MusicPage::iniNames(std::string* names, std::string* skinURL)
{
    std::ifstream ifs("resources/music.txt");
    if (ifs.is_open()) {
        for (int i = 0; i < MUSIC_NUM; i++) {
            std::getline(ifs, names[i]);
            std::getline(ifs, musicURL[i]);
        }
    }
    ifs.close();
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
        // jump back to main state
        this->window->close();
    }

    this->updateMusicname();
    //this->updateCover();
}

void MusicPage::render()
{
    this->window->clear(background_color);

    // draw game objects
    this->window->draw(musicname);
    //this->window->draw(cover[index]);
    this->window->draw(leftbutton);
    this->window->draw(rightbutton);
    this->window->draw(returnbutton);

    this->window->display();
}

void MusicPage::updateMusicname()
{
    this->musicname.setString(names[index]);
}

void MusicPage::updateMusic()
{
    music.stop();
    music.openFromFile(musicURL[index]);
    music.play();
}

/*void MusicPage::updateCover()
{
    this->cover_texture[index].loadFromFile(coverURL[index]);
    this->cover[index].setTexture(this->cover_texture[index]);
    this->cover[index].setPosition(780, 225);
}*/

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