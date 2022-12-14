#include "SkinPage.hpp"

// Constructors Destructors
SkinPage::SkinPage()
{
    this->initVariables();
    this->initWindow();
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
    this->names[0] = "Estel";

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
    if (!font.loadFromFile("/Users/User/source/repos/Dino/Dino/resources/ComicGeckoPro.otf")) {
        throw("ERROR::COULD NOT FIND LOAD FONT");
    }

    // set background color
    this->background_color = sf::Color(255, 204, 153);

    // set text
    names[0] = "Estel";
    this->skinname.setString(names[0]);
    this->skinname.setFillColor(sf::Color::Black);
    this->skinname.setFont(font);
    this->skinname.setCharacterSize(46);
    this->skinname.setPosition(960, 150);

    // set texture
    if (!this->leftbutton_texture.loadFromFile("/Users/User/source/repos/Dino/Dino/resources/left.png"))
        throw("ERROR::EXIT_FAILURE");
    this->leftbutton.setTexture(this->leftbutton_texture);
    this->leftbutton.setPosition(150, 530);
    if (!this->rightbutton_texture.loadFromFile("/Users/User/source/repos/Dino/Dino/resources/right.png"))
        throw("ERROR::EXIT_FAILURE");
    this->rightbutton.setTexture(this->rightbutton_texture);
    this->rightbutton.setPosition(1770, 530);
    if (!this->returnbutton_texture.loadFromFile("/Users/User/source/repos/Dino/Dino/resources/left.png"))
        throw("ERROR::EXIT_FAILURE");
    this->returnbutton.setTexture(this->returnbutton_texture);
    this->returnbutton.setPosition(50, 50);
    if (!this->dinos_texture[0].loadFromFile("/Users/User/source/repos/Dino/Dino/resources/Dino.png"))
        throw("ERROR::EXIT_FAILURE");
    this->dinos[0].setTexture(this->dinos_texture[0]);
    this->dinos[0].setPosition(800, 300);

    // set music
    /*if (!this->when_i_was_a_boy_buffer.loadFromFile("/Users/yl/DinoGame/DinoGame/resources/When-I-Was-A-Boy.wav"))
    {
        return EXIT_FAILURE;
    }
    when_i_was_a_boy_song.setBuffer(when_i_was_a_boy_buffer);*/
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
void SkinPage::update()
{
    this->pollEvents();
    // get mouse loc on screen
//    std::cout << sf::Mouse::getPosition(*this -> window).x << ' ' << sf::Mouse::getPosition(*this -> window).y << std::endl;
}
void SkinPage::render()
{
    this->window->clear(background_color);

    // draw game objects
    this->window->draw(skinname);
    this->window->draw(dinos[0]);
    this->window->draw(leftbutton);
    this->window->draw(rightbutton);
    this->window->draw(returnbutton);

    //    this -> window -> draw(dinoneck);
    //    this -> window -> draw(dinobody);
    //    this -> window -> draw(dinohead);




    this->window->display();
}