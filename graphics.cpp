#include "graphics.h"
#include "gui.h"

int Graphics::screenCnt = 0;

//window
sf::RenderWindow* Graphics::window = new sf::RenderWindow(sf::VideoMode(Graphics::WinSizeX, Graphics::WinSizeY), "My Game", sf::Style::Close|sf::Style::Titlebar);

//font
sf::Font* Graphics::font = new sf::Font;
sf::Text* Graphics::text = new sf::Text;

//textures
std::vector<sf::Sprite*> Containers::sResources;
std::vector<sf::Sprite*> Containers::sHeroes;
std::vector<sf::Sprite*> Containers::sInteractions;
std::vector<sf::Sprite*> Containers::sSmall;
std::vector<sf::Sprite*> Containers::sColor;

Graphics::Graphics(){

    sLevel = new sf::Sprite;
    Containers::sResources.push_back(Graphics::sLevel);
    sWeapon = new sf::Sprite;
    Containers::sResources.push_back(Graphics::sWeapon);
    sRune = new sf::Sprite;
    Containers::sResources.push_back(Graphics::sRune);
    sPotion = new sf::Sprite;
    Containers::sResources.push_back(Graphics::sPotion);
    sGold = new sf::Sprite;
    Containers::sResources.push_back(Graphics::sGold);

    sWarrior = new sf::Sprite;
    Containers::sHeroes.push_back(Graphics::sWarrior);
    sWizard = new sf::Sprite;
    Containers::sHeroes.push_back(Graphics::sWizard);
    sAssassin = new sf::Sprite;
    Containers::sHeroes.push_back(Graphics::sAssassin);

    sMatrix = new sf::Sprite;
    Containers::sInteractions.push_back(Graphics::sMatrix);
    sAttack = new sf::Sprite;
    Containers::sInteractions.push_back(Graphics::sAttack);
    sWin = new sf::Sprite;
    Containers::sInteractions.push_back(Graphics::sWin);
    sLose = new sf::Sprite;
    Containers::sInteractions.push_back(Graphics::sLose);
    sTie = new sf::Sprite;
    Containers::sInteractions.push_back(sTie);
    sInfo = new sf::Sprite;
    Containers::sInteractions.push_back(Graphics::sInfo);

    sWeapon2 = new sf::Sprite;
    Containers::sColor.push_back(Graphics::sWeapon2);
    sRune2 = new sf::Sprite;
    Containers::sColor.push_back(Graphics::sRune2);
    sPotion2 = new sf::Sprite;
    Containers::sColor.push_back(Graphics::sPotion2);

    sSLevel = new sf::Sprite;
    Containers::sSmall.push_back(Graphics::sSLevel);
    sSWeapon = new sf::Sprite;
    Containers::sSmall.push_back(Graphics::sSWeapon);
    sSRune = new sf::Sprite;
    Containers::sSmall.push_back(Graphics::sSRune);
    sSPotion = new sf::Sprite;
    Containers::sSmall.push_back(Graphics::sSPotion);
    sSGold = new sf::Sprite;
    Containers::sSmall.push_back(Graphics::sSGold);

    Graphics::window->setKeyRepeatEnabled(false);
    if(!font->loadFromFile("fonts/kingthings.ttf"))
        std::cout << "Font error" << std::endl;
    text->setFont(*font);
    text->setCharacterSize(30);
    text->setFillColor(sf::Color::White);
    text->setOrigin(ImgSizeX/2, ImgSizeY/2);
    createSprite(sWeapon, "textures/big/weapon.png");
    createSprite(sPotion, "textures/big/potion_ii.png");
    createSprite(sRune, "textures/big/rune_i.png");
    createSprite(sGold, "textures/big/coin.png");
    createSprite(sLevel, "textures/big/level.png");
    createSprite(sAssassin, "textures/big/assassin_trap.png");
    createSprite(sWizard, "textures/big/wizard_staff.png");
    createSprite(sWarrior, "textures/big/warrior.png");
    createSprite(sMatrix, "textures/big/matrix_i.png");
    createSprite(sAttack, "textures/big/attack_i.png");
    createSprite(sWin, "textures/big/win.png");
    createSprite(sLose, "textures/big/lose_i.png");
    createSprite(sTie, "textures/big/shrug.png");
    createSprite(sInfo, "textures/big/info.png");
    createSprite(sWeapon2, "textures/big/gweapon.png");
    createSprite(sPotion2, "textures/big/gpotion.png");
    createSprite(sRune2, "textures/big/grune.png");
    createSprite(sSWeapon, "textures/small/weapon.png");
    createSprite(sSPotion, "textures/small/potion_ii.png");
    createSprite(sSRune, "textures/small/rune_i.png");
    createSprite(sSGold, "textures/small/coin.png");
    createSprite(sSLevel, "textures/small/level.png");

    printf("Graphics created!\n");
}

Graphics::~Graphics(){
        delete window;
        delete font;
        delete text;
        deleteSprite(Containers::sResources);
        deleteSprite(Containers::sHeroes);
        deleteSprite(Containers::sInteractions);
        deleteSprite(Containers::sSmall);
        deleteSprite(Containers::sColor);
        printf("Graphics deleted!\n");
}

void Graphics::createSprite(sf::Sprite* sp, std::string img){
    sf::Texture* tImg = new sf::Texture;
        if (!tImg->loadFromFile(img)){
            std::cerr<< "Texture error!"<< std::endl;
        }
    sp->setTexture(*tImg);
    sp->setPosition(Graphics::WinSizeX/2, Graphics::WinSizeY/2);
}

void Graphics::deleteSprite(std::vector<sf::Sprite*> &s){
    for(size_t i = 0; i < s.size(); i++){
        delete s[i];
    }
}

bool Graphics::mousePressedOnSprite(sf::Vector2f sPos){        //a vizsgálandó kép + a bal felső sarka
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Graphics::window);
    return mousePressedOnSprite(sPos, mousePos);
}

bool Graphics::mousePressedOnSprite(sf::Vector2f& sPos, sf::Vector2i& mousePos){
    bool place = (mousePos.x >= sPos.x && mousePos.x <= (sPos.x+ImgSizeX))
              && (mousePos.y >= sPos.y && mousePos.y <= (sPos.y+ImgSizeY));
    if(place && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return true;
    return false;
}

void Graphics::drawElement(std::vector<sf::Sprite*> &s, Graphics::Position& pos, sf::RenderWindow& w){
    for(size_t i = 0; i < s.size(); i++){
        s[i]->setPosition(pos.x, pos.y);
        w.draw(*s[i]);
        pos.y+=pos.gap;
    }
}

void Graphics::drawString(std::vector<std::string> &s, Graphics::Position& pos, sf::RenderWindow& w){
    for(size_t i = 0; i < s.size(); i++){
        Graphics::text->setString(s[i]);
        Graphics::text->setPosition(pos.x, pos.y);
        Graphics::window->draw(*Graphics::text);
        pos.y+=pos.gap;
    }
}

void Graphics::drawString(std::vector<std::string> &s, Graphics::Position& pos, sf::RenderWindow& w, size_t n){
    for(size_t i = 0; i < n; i++){
        Graphics::text->setString(s[i]);
        Graphics::text->setPosition(pos.x, pos.y);
        Graphics::window->draw(*Graphics::text);
        pos.y+=pos.gap;
    }
}

void Graphics::drawHeroMenu(std::vector<std::string> &sh){

    Graphics::Position psprite(0, 0, Graphics::WinSizeY/5);
    Graphics::Position psprite2((WinSizeX/3)*2, WinSizeY/4, Graphics::ImgSizeY*2);
    Graphics::Position ptext(ImgSizeX*2, (Graphics::WinSizeY/5)-10, Graphics::WinSizeY/5);
    Graphics::Position ptext2(ImgSizeX*4.15, Graphics::ImgSizeY*2+(Graphics::WinSizeY/5)-10, Graphics::ImgSizeY*2);
    Graphics::window->clear(sf::Color::Black);

    drawElement(Containers::sResources, psprite, *Graphics::window);
    drawString(sh, ptext, *Graphics::window);

    Graphics::sAttack->setPosition(psprite2.x, psprite2.y);
    Graphics::window->draw(*Graphics::sAttack);
    psprite2.y+=psprite2.gap;

    Graphics::sMatrix->setPosition(psprite2.x, psprite2.y);
    Graphics::window->draw(*Graphics::sMatrix);

    Graphics::sInfo->setPosition(WinSizeX-30, WinSizeY-30);
    Graphics::window->draw(*Graphics::sInfo);

    Graphics::text->setString(sh[sh.size()-1]); //név
    Graphics::text->setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    Graphics::text->setPosition(ImgSizeX*4, (Graphics::WinSizeY/5)-10);
    Graphics::window->draw(*Graphics::text);

    Graphics::text->setString("Fight");
    Graphics::text->setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    Graphics::text->setPosition(ptext2.x, ptext2.y);
    Graphics::window->draw(*Graphics::text);
    ptext2.y+=ptext2.gap;

    Graphics::text->setString("Play");
    Graphics::text->setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    Graphics::text->setPosition(ptext2.x, ptext2.y);
    Graphics::window->draw(*Graphics::text);

    Graphics::window->display();
}

void Graphics::drawNewHero(){
    Graphics::Position sp((Graphics::WinSizeX/6)*3.5, ImgSizeY*0.75, Graphics::ImgSizeX*1.5);
    Graphics::Position text((Graphics::WinSizeX/6)*2, ImgSizeY*1.5, Graphics::ImgSizeX*1.5);
    Graphics::window->clear(sf::Color::Black);

    Graphics::text->setString("Choose your hero!");
    Graphics::text->setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    Graphics::text->setPosition((Graphics::WinSizeX/5)*2, ImgSizeY*0.7);
    Graphics::window->draw(*Graphics::text);

    std::vector<std::string> str;
    str.push_back("Warrior");
    str.push_back("Wizard");
    str.push_back("Assassin");

    drawElement(Containers::sHeroes, sp, *Graphics::window);
    drawString(str, text, *Graphics::window);

    Graphics::window->display();
}

void Graphics::drawFight(sf::Sprite& s1, sf::Sprite& s2){
    Graphics::window->clear(sf::Color::Black);

    s1.setPosition(Graphics::ImgSizeX, Graphics::ImgSizeY);
    Graphics::window->draw(s1);

    s2.setPosition(Graphics::ImgSizeX*3, Graphics::ImgSizeY);
    Graphics::window->draw(s2);

    Graphics::text->setString("vs.");
    Graphics::text->setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    Graphics::text->setPosition(Graphics::ImgSizeX*3, Graphics::WinSizeY/3);
    Graphics::window->draw(*Graphics::text);
}

void Graphics::drawResult(short r){
    sf::Sprite s;
    switch(r){
    case(0):
        s = *Graphics::sTie;
        Graphics::text->setString("Tie!");
        break;
    case(1):
        s = *Graphics::sWin;
        Graphics::text->setString("You won!");
        break;
    case(2):
        s = *Graphics::sLose;
        Graphics::text->setString("You are defeated!");
        break;
    }

    Graphics::text->setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    Graphics::text->setPosition(Graphics::WinSizeX/2, (Graphics::WinSizeY/7)*6);
    Graphics::window->draw(*Graphics::text);

    s.setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    s.setPosition(Graphics::WinSizeX/2, (Graphics::WinSizeY/5)*3);
    Graphics::window->draw(s);
    Graphics::window->display();
}

void Graphics::drawMatrix(Matrix& m){
    Graphics::window->clear(sf::Color::Black);
    Position p(22, 22, 22);
    Gui::getInstance().getS2().getPos().clear();            //positions kiürítése
    for( int i = 0; i < m.getN(); i++ ){
        for( int j = i * m.getN(); j < i * m.getN() + m.getN(); j++ ){
            switch(m.getM()[j]){
                case (ResCodes::RES_WEAPON):
                    Graphics::sWeapon->setPosition(p.x, p.y);
                    Graphics::window->draw(*Graphics::sWeapon);
                    Gui::getInstance().getS2().setPos(sWeapon->getPosition());
                    break;
                case(ResCodes::RES_RUNE):
                    Graphics::sRune->setPosition(p.x, p.y);
                    Graphics::window->draw(*Graphics::sRune);
                    Gui::getInstance().getS2().setPos(sRune->getPosition());
                    break;
                case(ResCodes::RES_POTION):
                    Graphics::sPotion->setPosition(p.x, p.y);
                    Graphics::window->draw(*Graphics::sPotion);
                    Gui::getInstance().getS2().setPos(sPotion->getPosition());
                    break;
            }
            p.x += Graphics::ImgSizeX + p.gap;
        }
        p.y += Graphics::ImgSizeY + p.gap;
        p.x = p.gap;
    }
    Graphics::window->display();
}

void Graphics::drawMatrix(){
    Graphics::window->clear(sf::Color::Black);
    int n = Gui::getInstance().getS2().getMx()->getN();
    bool found;
    for( int j = 0; j < n * n; j++ ){
        found = false;
        for( size_t k = 0; k < Gui::getInstance().getS2().getClicked().size(); k++ )
            if( Gui::getInstance().getS2().getClicked()[k] == j )
                found = true;

        if(found){
            switch(Gui::getInstance().getS2().getMx()->getM()[j]){
                case (ResCodes::RES_WEAPON):
                    Graphics::getWeapon2()->setPosition(Gui::getInstance().getS2().getPos()[j]);
                    Graphics::window->draw(*Graphics::sWeapon2);
                    break;
                case(ResCodes::RES_RUNE):
                        Graphics::getRune2()->setPosition(Gui::getInstance().getS2().getPos()[j]);
                        Graphics::window->draw(*Graphics::sRune2);
                    break;
                case(ResCodes::RES_POTION):
                        Graphics::getPotion2()->setPosition(Gui::getInstance().getS2().getPos()[j]);
                        Graphics::window->draw(*Graphics::sPotion2);
                    break;
            }
        }

        else{
            switch(Gui::getInstance().getS2().getMx()->getM()[j]){
                case (ResCodes::RES_WEAPON):
                    Graphics::sWeapon->setPosition(Gui::getInstance().getS2().getPos()[j]);
                    Graphics::window->draw(*Graphics::sWeapon);
                    break;
                case(ResCodes::RES_RUNE):
                    Graphics::sRune->setPosition(Gui::getInstance().getS2().getPos()[j]);
                    Graphics::window->draw(*Graphics::sRune);
                    break;
                case(ResCodes::RES_POTION):
                    Graphics::sPotion->setPosition(Gui::getInstance().getS2().getPos()[j]);
                    Graphics::window->draw(*Graphics::sPotion);
                    break;
            }
        }
    }
    Graphics::window->display();
}

void Graphics::drawInfo(){
    Graphics::window->clear(sf::Color::Black);
    Position sp(Graphics::ImgSizeX*0.5, Graphics::ImgSizeY, Graphics::ImgSizeY/5*3);
    Position text(Graphics::ImgSizeX*2, Graphics::ImgSizeY*1.5, Graphics::ImgSizeY/5*3);

    std::vector<std::string> desc;
    desc.push_back("Level:   win 3 fights to increase");
    desc.push_back("Weapon:   amount of attacks");
    desc.push_back("Rune:   strength of an attack");
    desc.push_back("Potion:   amount of life points");
    desc.push_back("Gold:   collect by winning fights");
    desc.push_back("Esc:   Back to Main");

    drawElement(Containers::sSmall, sp, *Graphics::window);
    drawString(desc, text, *Graphics::window);

    Graphics::text->setString("Info page");
    Graphics::text->setOrigin(Graphics::ImgSizeX*0.5, Graphics::ImgSizeY*0.5);
    Graphics::text->setPosition(Graphics::WinSizeX*0.5, Graphics::ImgSizeY*0.8);
    Graphics::window->draw(*Graphics::text);

    Graphics::window->display();
}

void Graphics::drawFightInfo(std::vector<std::string> &sh1, std::vector<std::string> &sh2){
    Graphics::window->clear(sf::Color::Black);

    Graphics::Position psprite(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2*1.5, Graphics::WinSizeY/7);
    Graphics::Position ptext(ImgSizeX*2.3, Graphics::ImgSizeY*1.2, Graphics::WinSizeY/7);
    Graphics::Position ptext2(ImgSizeX*3.7, Graphics::ImgSizeY*1.2, Graphics::WinSizeY/7);
    Graphics::window->clear(sf::Color::Black);

    Graphics::text->setString("Your opponent is ");
    Graphics::text->setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    Graphics::text->setPosition(Graphics::WinSizeX/3, Graphics::ImgSizeY/2);
    Graphics::window->draw(*Graphics::text);

    drawString(sh1, ptext, *Graphics::window, sh1.size()-1);
    drawElement(Containers::sSmall, psprite, *Graphics::window);

    text->setFillColor(sf::Color(128,223,30,255));
    Graphics::text->setString(sh2[sh2.size()-1]);
    Graphics::text->setPosition((Graphics::WinSizeX/3)*2, Graphics::ImgSizeY/2);
    Graphics::window->draw(*Graphics::text);

    drawString(sh2, ptext2, *Graphics::window, sh2.size()-1);
    text->setFillColor(sf::Color::White);

    Graphics::text->setString("Press Enter");
    Graphics::text->setOrigin(Graphics::ImgSizeX/2, Graphics::ImgSizeY/2);
    Graphics::text->setPosition(Graphics::WinSizeX/2, Graphics::WinSizeY-Graphics::ImgSizeY/4);
    Graphics::window->draw(*Graphics::text);

    Graphics::window->display();
}
