#include "SkinPage.hpp"
#include "ResourcePath.hpp"

// Constructors Destructors
SkinPage::SkinPage(sf::RenderWindow *window)
{
    this->window = window;
    this->iniNames(names, skinURL);
    this->initVariables();
    //this->initWindow();
    this->initObjects();
}

SkinPage::~SkinPage()
{
    delete this->window;
}

// Accessors
const bool SkinPage::running() const
{
    return this->window->isOpen();
}

// Private functions
void SkinPage::initVariables()
{
    this->window = nullptr;
    index = 0;
}

void SkinPage::initWindow()
{
    this->videoMode.height = 1080;
    this->videoMode.width = 1920;
    this->window = new sf::RenderWindow(this->videoMode, "Like A Dino!");
    this->window->setFramerateLimit(60);
}

void SkinPage::initObjects()
{
    // load font
    if (!font.loadFromFile(resourcePath()+"Resources/Fonts/ComicGeckoPro.otf")) {
        throw("ERROR::COULD NOT FIND LOAD FONT");
    }

    // set background color
    this->background_color = sf::Color(255, 204, 153);

    // set texture
    if (!this->leftbutton_texture.loadFromFile(resourcePath()+"Resources/Images/left.png"))
        throw("ERROR::EXIT_FAILURE");
    this->leftbutton.setTexture(this->leftbutton_texture);
    this->leftbutton.setPosition(150, 530);
    sf::IntRect leftTmp(leftbutton.getPosition().x, leftbutton.getPosition().y,
        leftbutton.getGlobalBounds().width, leftbutton.getGlobalBounds().height);
    this->leftbuttonRect = leftTmp;

    if (!this->rightbutton_texture.loadFromFile(resourcePath()+"Resources/Images/right.png"))
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

    if (!this->dinos_texture[index].loadFromFile(resourcePath()+"Resources/Images/"+names[index]+".png"))
        throw("ERROR::EXIT_FAILURE");
    this->dinos[index].setTexture(this->dinos_texture[index]);
    this->dinos[index].setPosition(780, 225);

    // set text
    this->skinname.setString(names[index]);
    this->skinname.setFillColor(sf::Color::Black);
    this->skinname.setFont(font);
    this->skinname.setCharacterSize(64);
    this->skinname.setPosition(dinos[0].getPosition().x + dinos[0].getGlobalBounds().width/2
                               - skinname.getGlobalBounds().width/2, 100);

    // set music
    if (!this->music.openFromFile(musicURL[0]))
        throw("ERROR::EXIT_FAILURE");
    music.play();
}

void SkinPage::iniNames(std::string* names, std::string* skinURL)
{
    std::ifstream ifs(resourcePath()+"Rresources/skin.txt");
    if (ifs.is_open()) {
        for(int i = 0; i < SKIN_NUM; i++){
            std::getline(ifs, names[i]);
        }
    }
    ifs.close();
}

// Functions
void SkinPage::pollEvents()
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

void SkinPage::update(int& current_state)
{
    this->pollEvents();
    if (ifLeftPressed(sf::Mouse::getPosition(*this->window))) {
        sf::Time cur = time.getElapsedTime();
        if (cur.asSeconds() > 0.15) {
            index--;
            if (index < 0)
                index = SKIN_NUM - 1;
            time.restart();
        }
    }
    else if(ifRightPressed(sf::Mouse::getPosition(*this->window))){
        sf::Time cur = time.getElapsedTime();
        if (cur.asSeconds() > 0.15) {
            index++;
            if (index == SKIN_NUM)
                index = 0;
            time.restart();
        }
    }
    else if (ifReturnPressed(sf::Mouse::getPosition(*this->window))) {
        // change dino skin for every state
        current_state = 1;
        this->window->close();
    }

    this->updateDinos();
    this->updateSkinname();
}

void SkinPage::render()
{
    this->window->clear(background_color);

    // draw game objects
    this->window->draw(skinname);
    this->window->draw(dinos[index]);
    this->window->draw(leftbutton);
    this->window->draw(rightbutton);
    this->window->draw(returnbutton);

    this->window->display();
}

void SkinPage::updateSkinname()
{
    this->skinname.setString(names[index]);
    this->skinname.setPosition(dinos[index].getPosition().x + dinos[index].getGlobalBounds().width / 2
        - skinname.getGlobalBounds().width / 2, 100);
}

void SkinPage::updateDinos()
{
    this->dinos_texture[index].loadFromFile(resourcePath()+"Resources/Images/"+names[index]+".png");
    this->dinos[index].setTexture(this->dinos_texture[index]);
    this->dinos[index].setPosition(780, 225);
}

const bool SkinPage::ifLeftPressed(sf::Vector2i mousePos) const
{
    if (leftbuttonRect.contains(sf::Mouse::getPosition(*this->window))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
    }
    return false;
}

const bool SkinPage::ifRightPressed(sf::Vector2i mousePos) const
{
    if (rightbuttonRect.contains(sf::Mouse::getPosition(*this->window))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
    }
    return false;
}

const bool SkinPage::ifReturnPressed(sf::Vector2i mousePos) const
{
    if (returnbuttonRect.contains(sf::Mouse::getPosition(*this->window))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return true;
    }
    return false;
}
